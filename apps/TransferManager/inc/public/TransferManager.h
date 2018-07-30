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
 * File:   TransferManager.h
 * Author: Matus Bodorik
 *
 * Created on December 21, 2017, 9:20 AM
 */

#ifndef TRANSFERMANAGER_H
#define TRANSFERMANAGER_H

#include "iTransferRequest.h"
#include "iTransferClient.h"
#include "TMFactory.h"
#include <queue>
#include <vector>
#include <memory>

namespace flexd {
    namespace rsm {
        namespace conn {

            class TransferManager {
            public:
                TransferManager(flexd::icl::ipc::FleXdEpoll& poller);
                TransferManager(const TransferManager& orig) = delete;
                virtual ~TransferManager();

                bool addTransfer(const iTransferRequest& request);
                bool runTransfer();
                bool abortTransfer();
                bool getTransferInfo();

            private:
                std::queue<std::shared_ptr<iTransferClient>> m_list;
                flexd::icl::ipc::FleXdEpoll& m_poller;
            };
        } //namespace conn
    } //namespace rsm
} //namespace flexd

#endif /* TRANSFERMANAGER_H */

