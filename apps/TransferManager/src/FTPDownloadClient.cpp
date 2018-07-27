/*
Copyright (c) 2017, Globallogic s.r.o.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
 * Neither the name of the Globallogic s.r.o. nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC S.R.O. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * File:   FTPDownloadClient.cpp
 * Author: Matus Bodorik
 * 
 * Created on January 4, 2018, 12:06 PM
 */

#include "FTPDownloadClient.h"
#include "curl/curl.h"
#include "TMUtility.h"
#include "FleXdLogger.h"
#include "string"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <ctime>
#include <unistd.h>
#include <memory>

namespace flexd {
    namespace rsm {
        namespace conn {
            namespace ftp {

                FTPDownloadClient::FTPDownloadClient(const iTransferRequest& request, flexd::icl::ipc::FleXdEpoll& poller)
                : FTPTransferClient(poller)
                {
                    m_request = request;
                }

                FTPDownloadClient::~FTPDownloadClient()
                {
                }

                void FTPDownloadClient::abortTransfer()
                {
                    if (m_request.getTransferType() == TransferType::Enum::FTPDownload)
                    {
                        FLEX_LOG_TRACE("FTPDownloadClient::abortTransfer() -> Abort FTP Download transfer!");
                        m_abort = true;
                    }
                }

                void FTPDownloadClient::doTransfer()
                {
                    if (m_request.getTransferType() == TransferType::Enum::FTPDownload)
                    {
                        m_status = TransferStatus::Running;
                        if (m_event.init() && !m_thread)
                        {
                            m_thread = std::make_unique<std::thread>(&FTPDownloadClient::downloadFromFTPtoFile, this, m_request.getURL(), m_request.getPath());
                        }
                    }
                }

                void FTPDownloadClient::getTransferStatus()
                {
                    if (m_request.getTransferType() == TransferType::Enum::FTPDownload)
                    {
                        if (checkURL(m_request.getURL()) == 200)
                        {
                            FLEX_LOG_TRACE("FTPDownloadClient::getTransferStatus() -> FTP Download transfer status: ");
                            switch (m_status)
                            {
                                case TransferStatus::Enum::Pending:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Pending!");
                                    break;
                                case TransferStatus::Enum::Idle:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Idle!");
                                    break;
                                case TransferStatus::Enum::Queued:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Queued!");
                                    break;
                                case TransferStatus::Enum::Running:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Running!");
                                    break;
                                case TransferStatus::Enum::Finished:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Finished!");
                                    break;
                                case TransferStatus::Enum::Aborted:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Aborted!");
                                    break;
                                case TransferStatus::Enum::Failed:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Failed!");
                                    break;
                                case TransferStatus::Enum::Paused:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Paused!");
                                    break;
                                case TransferStatus::Enum::Frozen:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Frozen!");
                                    break;
                                case TransferStatus::Enum::Undefined:
                                default:
                                    FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfer is: Undefined!");
                                    break;
                            }
                            FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfered size: ", m_transferSize, " B ,Elapsed time: ", m_elapsedTime / 1000, " s.");
                        }
                    }
                }

                void FTPDownloadClient::downloadFromFTPtoFile(const std::string& url, const std::string& path)
                {
                    if (checkURL(url) == 200 && m_request.getTransferType() == TransferType::Enum::FTPDownload)
                    {
                        FLEX_LOG_TRACE("FTPDownloadClient::downloadFromFTPtoFile() -> FTP Download transfer start");
                        double speedDownload, totalTime;
                        FILE * ftpFile;
                        ftpFile = fopen(path.c_str(), "wb");
                        if (ftpFile)
                        {
                            clock_t begin = clock();
                            curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
                            curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, flexd::rsm::conn::writeCallback);
                            curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, ftpFile);
                            curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 0L);
                            curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, (void *)this);
                            curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, flexd::rsm::conn::progressDownloadFunction);
                        //  curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L); 
                            CURLcode res = curl_easy_perform(m_curl);
                            clock_t end = clock();
                            curl_easy_getinfo(m_curl, CURLINFO_SIZE_DOWNLOAD, &m_transferSize);
                            m_elapsedTime = double(end - begin);
                            if (res == CURLE_OK)
                            {
                                curl_easy_getinfo(m_curl, CURLINFO_SPEED_DOWNLOAD, &speedDownload);
                                curl_easy_getinfo(m_curl, CURLINFO_TOTAL_TIME, &totalTime);
                                FLEX_LOG_TRACE("FTPDownloadClient::downloadFromFTPtoFile() -> Speed: ", speedDownload, " bytes/sec during ", totalTime, " seconds.");
                                m_event.trigger(TransferReturn::Success);
                            } else if(res == CURLE_ABORTED_BY_CALLBACK)
                            {
                                FLEX_LOG_TRACE("FTPDownloadClient::downloadFromFTPtoFile() -> Curl failed: ", curl_easy_strerror(res));
                                m_event.trigger(TransferReturn::Abort);
                            }else
                            {
                                FLEX_LOG_ERROR("FTPDownloadClient::downloadFromFTPtoFile() -> Curl failed: ", curl_easy_strerror(res));
                                m_event.trigger(TransferReturn::Fail);
                            }
                            fclose(ftpFile);
                        } else
                        {
                            FLEX_LOG_ERROR("FTPDownloadClient::downloadFromFTPtoFile() -> Undefined Error!");
                            m_event.trigger(TransferReturn::UndefinedError);
                        }
                    }
                }

                long FTPDownloadClient::checkURL(const std::string& url)
                {
                    long response_code = 0;
                    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
                    CURLcode res = curl_easy_perform(m_curl);
                    if (res == CURLE_OK)
                    {
                        curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &response_code);
                        if (response_code == 200)
                        {
                            FLEX_LOG_TRACE("FTPDownloadClient::checkURL() -> Check URL Success: ", response_code);
                            return response_code;
                        } else
                        {
                            FLEX_LOG_ERROR("FTPDownloadClient::checkURL() -> Check URL Error: ", response_code);
                            return response_code;
                        }
                    }
                    return response_code;
                }
                
            } //namespace ftp
        } //namespace conn
    } //namespace rsm
} //namespace flexd
