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
 * File:   FTPDownloadClient.h
 * Author: Matus Bodorik
 *
 * Created on January 4, 2018, 12:06 PM
 */

#ifndef FTPDOWNLOADCLIENT_H
#define FTPDOWNLOADCLIENT_H

#include <string>
#include "FTPTransferClient.h"

namespace flexd {
    namespace rsm {
        namespace conn {
            namespace ftp {

                class FTPDownloadClient : public FTPTransferClient {
                public:
                    FTPDownloadClient(const iTransferRequest& request, flexd::icl::ipc::FleXdEpoll& poller);
                    virtual ~FTPDownloadClient();

                    void doTransfer() override;
                    void abortTransfer() override;
                    void getTransferStatus() override;

                private:
                    void downloadFromFTPtoFile(const std::string& url, const std::string& path);
                    long checkURL(const std::string& url);
                    
                };
            } //namespace ftp
        } //namespace conn
    } //namespace rsm
} //namespace flexd
#endif /* FTPDOWNLOADCLIENT_H */

