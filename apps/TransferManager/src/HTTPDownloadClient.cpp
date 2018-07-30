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
 * File:   HTTPDownloadClient.cpp
 *
 * Author: Matus Bodorik
 *
 * Created on December 19, 2017, 11:16 AM
 */

#include "HTTPDownloadClient.h"
#include "TMUtility.h"
#include <FleXdEpoll.h>
#include <FleXdLogger.h>
#include <curl/curl.h>
#include <sys/eventfd.h>
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
            namespace http {

                HTTPDownloadClient::HTTPDownloadClient(const iTransferRequest &request, flexd::icl::ipc::FleXdEpoll& poller)
                : HTTPTransferClient(poller)
                {
                    m_request = request;
                }

                HTTPDownloadClient::~HTTPDownloadClient()
                {
                }

                void HTTPDownloadClient::doTransfer()
                {
                    if (m_request.getTransferType() == TransferType::Enum::HTTPDownload)
                    {
                        m_status = TransferStatus::Running;
                        if (m_event.init() && !m_thread)
                        {
                            m_thread = std::make_unique<std::thread>(&HTTPDownloadClient::downloadFromURLtoFile, this, m_request.getURL(), m_request.getPath());
                        }
                    }
                }


                void HTTPDownloadClient::abortTransfer()
                {
                    if (m_request.getTransferType() == TransferType::Enum::HTTPDownload)
                    {
                            m_abort = true;
                            FLEX_LOG_TRACE("HTTPDownloadClient::abortTransfer() -> Abort HTTP Download transfer!");
                    }
                }

                void HTTPDownloadClient::getTransferStatus()
                {
                    if (m_request.getTransferType() == TransferType::Enum::HTTPDownload)
                    {
                        if (checkURL(m_request.getURL()) == FLEXD_TC_URL_SUCCESS_200_CODE)
                        {
                            FLEX_LOG_TRACE("HTTPDownloadClient::getTransferStatus() -> HTTP Download transfer status: ");
                            switch (m_status)
                            {
                                case TransferStatus::Enum::Pending:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Pending!");
                                    break;
                                case TransferStatus::Enum::Idle:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Idle!");
                                    break;
                                case TransferStatus::Enum::Queued:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Queued!");
                                    break;
                                case TransferStatus::Enum::Running:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Running!");
                                    break;
                                case TransferStatus::Enum::Finished:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Finished!");
                                    break;
                                case TransferStatus::Enum::Aborted:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Aborted!");
                                    break;
                                case TransferStatus::Enum::Failed:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Failed!");
                                    break;
                                case TransferStatus::Enum::Paused:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Paused!");
                                    break;
                                case TransferStatus::Enum::Frozen:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Frozen!");
                                    break;
                                case TransferStatus::Enum::Undefined:
                                default:
                                    FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfer is: Undefined!");
                                    break;
                            }
                            FLEX_LOG_INFO("HTTPDownloadClient::getTransferStatus() -> Transfered size: ", m_transferSize, " B ,Elapsed time: ", m_elapsedTime / 1000, " s.");
                        }
                    }
                }

                void HTTPDownloadClient::downloadFromURLtoFile(const std::string& url, const std::string& path)
                {
                    if (checkURL(url) == FLEXD_TC_URL_SUCCESS_200_CODE)
                    {
                        double speed_download, total_time;
                        FILE *file;
                        file = fopen(path.c_str(), "wb");
                        if (file)
                        {
                            FLEX_LOG_TRACE("HTTPDownloadClient::downloadFromURLtoFile() -> HTTP Download transfer to file start.");
                            clock_t begin = clock();
                            curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
                            curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
                            curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
                            curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
                            curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, flexd::rsm::conn::writeCallback);
                            curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, file);
                            curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 0L);
                            curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, (void *) this);
                            curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, flexd::rsm::conn::progressDownloadFunction);
                            //curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
                            CURLcode res = curl_easy_perform(m_curl);
                            clock_t end = clock();
                            curl_easy_getinfo(m_curl, CURLINFO_SIZE_DOWNLOAD, &m_transferSize);
                            m_elapsedTime = double(end - begin);
                            if (res == CURLE_OK)
                            {
                                curl_easy_getinfo(m_curl, CURLINFO_SPEED_DOWNLOAD, &speed_download);
                                curl_easy_getinfo(m_curl, CURLINFO_TOTAL_TIME, &total_time);
                                FLEX_LOG_TRACE("HTTPDownloadClient::downloadFromURLtoFile() -> Speed: ", speed_download, " bytes/sec during ", total_time, " seconds.");
                                m_event.trigger(TransferReturn::Success);
                            } else if(res == CURLE_ABORTED_BY_CALLBACK)
                            {
                                FLEX_LOG_TRACE("HTTPDownloadClient::downloadFromURLtoFile() -> Curl failed: ", curl_easy_strerror(res));
                                m_event.trigger(TransferReturn::Abort);
                            } else
                            {
                                FLEX_LOG_ERROR("HTTPDownloadClient::downloadFromURLtoFile() ->  Curl failed: ", curl_easy_strerror(res));
                                m_event.trigger(TransferReturn::Fail);
                            }
                            fclose(file);
                        } else
                        {
                            FLEX_LOG_ERROR("HTTPDownloadClient::downloadFromURLtoFile() -> Error: Problem with file!");
                            m_event.trigger(TransferReturn::UndefinedError);
                        }
                    }
                }

                std::string HTTPDownloadClient::downloadFromURLtoBuf(const std::string& url)
                {
                    std::stringstream out;
                    double speedDownload, totalTime;
                    if (checkURL(url) == 0)
                    {
                        FLEX_LOG_TRACE("HTTPDownloadClient::downloadFromURLtoBuf() -> HTTP Download transfer to buffer start.");
                        clock_t begin = clock();
                        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
                        curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
                        curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, (void *) this);
                        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, flexd::rsm::conn::writeDataToBuf);
                        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &out);
                        curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 0L);
                        curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, flexd::rsm::conn::progressDownloadFunction);
                        //curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
                        CURLcode res = curl_easy_perform(m_curl);
                        clock_t end = clock();
                        m_elapsedTime = double(end - begin);
                        if (res != CURLE_OK)
                        {
                            FLEX_LOG_ERROR("HTTPDownloadClient::downloadFromURLtoBuf() -> Curl failed: ", curl_easy_strerror(res));
                        } else
                        {
                            curl_easy_getinfo(m_curl, CURLINFO_SPEED_UPLOAD, &speedDownload);
                            curl_easy_getinfo(m_curl, CURLINFO_TOTAL_TIME, &totalTime);
                            curl_easy_getinfo(m_curl, CURLINFO_SIZE_DOWNLOAD, &m_transferSize);
                            FLEX_LOG_INFO("FTPDownloadClient::downloadFromURLtoBuf() -> Speed: ", speedDownload, " bytes/sec during ", totalTime, " seconds.");
                        }
                    }
                    return out.str();
                }

                bool HTTPDownloadClient::writeToFile(const std::string& content, const std::string& path)
                {
                    std::ofstream file(path.c_str(), std::ios::out | std::ios::binary);
                    if (file)
                    {
                        file << content;
                        file.close();
                        return true;
                    }
                    return false;
                }

                long HTTPDownloadClient::checkURL(const std::string& url)
                {
                    long response_code = 0;
                    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
                    if (curl_easy_perform(m_curl) == CURLE_OK)
                    {
                        curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &response_code);
                        if (response_code != FLEXD_TC_URL_SUCCESS_200_CODE)
                        {
                            FLEX_LOG_ERROR("HTTPDownloadClient::checkURL() -> Check URL Error: ", response_code);
                            return response_code;
                        } else
                        {
                            FLEX_LOG_TRACE("HTTPDownloadClient::checkURL() -> Check URL Success: ", response_code);
                            return response_code;
                        }
                    }
                    return response_code;
                }

            } //namespace http
        } //namespace conn
    } //namespace rsm
} //namespace flexd
