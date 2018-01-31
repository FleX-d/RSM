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
 * File:   MCClient.cpp
 * Author: Matus Bodorik
 * 
 * Created on January 19, 2018, 9:30 AM
 */

#include <iostream>
#include "MCClient.h"
#include "MqttTypes.h"


namespace rsm {
    namespace msq {
        namespace com {

            MCClient::MCClient(const MCNewClientRequest& request)
            : rsm::conn::mqtt::iMosquittoClient(request.getClientID().getExternalID(), request.getSettings()),
            m_clientID(request.getClientID().getID(), 
                       request.getClientID().getExternalID(), 
                       request.getClientID().getRequester(), 
                       request.getClientID().getTopic(), 
                       request.getClientID().getUniqueID()), 
            m_onMessage(request.getOnMessage())
            {
            }

            MCClient::~MCClient()
            {
            }

            bool MCClient::send(const MCMessage& message)
            {
                std::cout << "Sending Message..." <<std::endl;
                int temp = this->publishMessage(rsm::conn::mqtt::MqttMessage(m_clientID.getTopic() , message.getPayload()));
                if(temp == 0)
                {
                    return true;
                }
                return false;
            }

            bool MCClient::subscribe()
            {
                std::cout << "Subscribing...."<< std::endl;
                int temp = this->subscribeTopic(m_clientID.getTopic());
                if(temp == 0)
                {
                    return true;
                }
                return false;
            }

            bool MCClient::unsubscribe()
            {
                std::cout << "Unsubscribing...."<< std::endl;
                int temp = this->unsubscribeTopic(m_clientID.getTopic());
                if(temp == 0)
                {
                    return true;
                }
                return false;
            }

            void MCClient::onMessage(const rsm::conn::mqtt::MqttMessage& msg)
            {
                m_onMessage(msg.getMessage());
            }

            const MCClientID& MCClient::getClientID() const
            {
                return m_clientID;
            }

        }
    }
}