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
 * File:   TMFactory.cpp
 * Author: Matus Bodorik
 * 
 * Created on December 19, 2017, 10:49 AM
 */

#include "TMFactory.h"
#include "TransferTypes.h"
#include "HTTPDownloadClient.h"
#include "HTTPUploadClient.h"
#include "FTPUploadClient.h"
#include "FTPDownloadClient.h"
#include <FleXdLogger.h>

namespace flexd {
    namespace rsm {
        namespace conn {

            namespace TMFactory{
            
                std::shared_ptr<iTransferClient> createInstance(const iTransferRequest& request, flexd::icl::ipc::FleXdEpoll& poller)
                {
                    switch (request.getTransferType())
                    {
                        case TransferType::HTTPDownload:
                            FLEX_LOG_TRACE("TMFactory::createInstance() -> TransferType::HTTPDownload");
                            return std::make_shared<http::HTTPDownloadClient>(request, poller);
                        case TransferType::HTTPUpload:
                            FLEX_LOG_TRACE("TMFactory::createInstance() -> TransferType::HTTPUpload");
                            return std::make_shared<http::HTTPUploadClient>(request, poller);
                        case TransferType::FTPUpload:
                            FLEX_LOG_TRACE("TMFactory::createInstance() -> TransferType::FTPUpload");
                            return std::make_shared<ftp::FTPUploadClient>(request, poller);
                        case TransferType::FTPDownload:
                            FLEX_LOG_TRACE("TMFactory::createInstance() -> TransferType::FTPDownload");
                            return std::make_shared<ftp::FTPDownloadClient>(request, poller);
                        default:
                            break;
                    }
                    return nullptr;
                }
            }//namespace TMFactory
        } //namespace conn
    } //namespace rsm
} //namespace flexd
