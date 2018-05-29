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
 * File:   MCManager.h
 * Author: Matus Bodorik
 *
 * Created on January 19, 2018, 9:25 AM
 */

#ifndef MCMANAGER_H
#define MCMANAGER_H

#include <map>
#include "MCRequestAck.h"
#include "MCOperationRequest.h"
#include "MCMessage.h"
#include "MCClient.h"
#include <memory>


namespace rsm {
    namespace msq {
        namespace com {

            class MCManager {
            public:
                MCManager();
                virtual ~MCManager();
                
                MCRequestAck addClient(const MCNewClientRequest& request);
                MCRequestAck runClient(const MCOperationRequest& request);
                MCRequestAck publish(const MCMessage& message);
                
                MCManager(const MCManager& orig) = delete;
                MCManager& operator= (const MCManager& orig) = delete;
                
            private:
                std::map <std::string , std::shared_ptr<MCClient>> m_clientMap; // TODO replace std::string key with MCClientID
            };
        }
    }
}
#endif /* MCMANAGER_H */

