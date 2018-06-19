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
 * File:   MCClient.h
 * Author: Matus Bodorik
 *
 * Created on January 19, 2018, 9:30 AM
 */

#ifndef MCCLIENT_H
#define MCCLIENT_H

#include "MCNewClientRequest.h"
#include "MCClientID.h"
#include "iMosquittoClient.h"
#include "MqttMessage.h"
#include "MCMessage.h"
#include "MCRequestAck.h"

namespace rsm {
    namespace msq {
        namespace com {

            class MCClient : public rsm::conn::mqtt::iMosquittoClient {
            public:
                explicit MCClient(const MCNewClientRequest& request);
                virtual ~MCClient();
                
                bool send(const MCMessage& message);
                bool subscribe();
                bool unsubscribe();
                
                const MCClientID& getClientID() const;
                
                MCClient(const MCClient& orig) = delete;
                MCClient& operator= (const MCClient& orig) = delete;
                
            protected:
                virtual void onMessage(const rsm::conn::mqtt::MqttMessage& msg) override;
                virtual void onRecon() override;


            private:
                MCClientID m_clientID;
                std::function<void(const std::string&)> m_onMessage;

            };
        }
    }
}
#endif /* MCCLIENT_H */

