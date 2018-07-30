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
 * File:   HTTPUploadClient.cpp
 * Author: Matus Bodorik
 *
 * Created on December 19, 2017, 11:15 AM
 */

#include "HTTPUploadClient.h"
#include "TMUtility.h"
#include <curl/curl.h>
#include <FleXdLogger.h>
#include <FleXdIPCCommon.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <memory>

namespace flexd {
    namespace rsm {
        namespace conn {
            namespace http {

                HTTPUploadClient::HTTPUploadClient(const iTransferRequest &request, flexd::icl::ipc::FleXdEpoll& poller)
                : HTTPTransferClient(poller)
                {
                    m_request = request;
                }

                HTTPUploadClient::~HTTPUploadClient()
                {
                }

                void HTTPUploadClient::doTransfer()
                {

                    if (m_request.getTransferType() == TransferType::HTTPUpload)
                    {
                        m_status = TransferStatus::Running;
                         if (m_event.init() && !m_thread)
                        {
                            m_thread = std::make_unique<std::thread>(&HTTPUploadClient::uploadFile, this, m_request.getURL(), m_request.getPath());
                        }
                    }
                }

                void HTTPUploadClient::abortTransfer()
                {
                    if (m_request.getTransferType() == TransferType::HTTPUpload)
                    {
                        m_abort = true;
                        FLEX_LOG_TRACE("HTTPUploadClient::abortTransfer() -> Abort HTTP Upload transfer!");
                    }
                }

                void HTTPUploadClient::getTransferStatus()
                {
                    if (m_request.getTransferType() == TransferType::HTTPUpload)
                    {
                        FLEX_LOG_TRACE("HTTPUploadClient::getTransferStatus() -> HTTP Upload transfer status: ");
                        switch (m_status)
                        {
                            case TransferStatus::Pending:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Pending!");
                                break;
                            case TransferStatus::Idle:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Idle!");
                                break;
                            case TransferStatus::Queued:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Queued!");
                                break;
                            case TransferStatus::Running:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Running!");
                                break;
                            case TransferStatus::Finished:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Finished!");
                                break;
                            case TransferStatus::Aborted:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Aborted!");
                                break;
                            case TransferStatus::Failed:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Failed!");
                                break;
                            case TransferStatus::Paused:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Paused!");
                                break;
                            case TransferStatus::Frozen:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Frozen!");
                                break;
                            case TransferStatus::Enum::Undefined:
                            default:
                                FLEX_LOG_INFO("HTTPUploadClient::getTransferStatus() -> Transfer is: Undefined!");
                                break;
                        }
                        FLEX_LOG_INFO("FTPDownloadClient::getTransferStatus() -> Transfered size: ", m_transferSize, " B ,Elapsed time: ", m_elapsedTime / 1000, " s.");
                    }
                }

                void HTTPUploadClient::uploadFile(const std::string& url, const std::string& path)
                {
                    if (flexd::icl::ipc::checkIfFileExist(path))
                    {
                        FLEX_LOG_TRACE("HTTPUploadClient::uploadFile() -> HTTP Upload transfer start");
                        double speedUpload, totalTime;
                        FILE * file;
                        file = fopen(path.c_str(), "rb");
                        long size = getFileSize(path);
                        if (file && (size != 0))
                        {
                            FLEX_LOG_TRACE("HTTPUploadClient::uploadFile() -> Local file size: ", CURL_FORMAT_CURL_OFF_T, size);
                            clock_t begin = clock();
                            curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
                            curl_easy_setopt(m_curl, CURLOPT_UPLOAD, 1L);
                            curl_easy_setopt(m_curl, CURLOPT_READDATA, file);
                            curl_easy_setopt(m_curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t) size);
                            //curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
                            curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 0L);
                            curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, (void *) this);
                            curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, flexd::rsm::conn::progressUploadFunction);
                            CURLcode res = curl_easy_perform(m_curl);
                            clock_t end = clock();
                            m_elapsedTime = double(end - begin);
                            if (res == CURLE_OK)
                            {
                                curl_easy_getinfo(m_curl, CURLINFO_SPEED_UPLOAD, &speedUpload);
                                curl_easy_getinfo(m_curl, CURLINFO_TOTAL_TIME, &totalTime);
                                curl_easy_getinfo(m_curl, CURLINFO_SIZE_UPLOAD, &m_transferSize);
                                FLEX_LOG_TRACE("HTTPUploadClient::uploadFile() -> Speed: ", speedUpload, " bytes/sec during ", totalTime, " seconds.");
                                m_event.trigger(TransferReturn::Success);
                            } else if (res == CURLE_ABORTED_BY_CALLBACK)
                            {
                                FLEX_LOG_TRACE("HTTPUploadClient::uploadFile() -> Curl failed: ", curl_easy_strerror(res));
                                m_event.trigger(TransferReturn::Abort);
                            } else {
                                FLEX_LOG_ERROR("HTTPUploadClient::uploadFile() -> Curl failed: ", curl_easy_strerror(res));
                                m_event.trigger(TransferReturn::Fail);
                            }
                            fclose(file);
                        } else {
                            FLEX_LOG_ERROR("HTTPUploadClient::uploadFile() ->Error: Problem with File!");
                            m_event.trigger(TransferReturn::UndefinedError);
                        }
                    }
                }


                long HTTPUploadClient::getFileSize(std::string filename)
                {
                    struct stat stat_buf;
                    return stat(filename.c_str(), &stat_buf) == 0 ? stat_buf.st_size : -1;
                }

            } //namespace http
        } //namespace conn
    } //namespace rsm
} //namespace flexd
