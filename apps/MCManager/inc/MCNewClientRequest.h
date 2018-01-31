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
 * File:   MCRequest.h
 * Author: Matus Bodorik
 *
 * Created on January 19, 2018, 9:23 AM
 */

#ifndef MCREQUEST_H
#define MCREQUEST_H

#include <string>
#include <functional>
#include "MCClientID.h"
#include "MCTypes.h"
#include "MosquittoSetting.h"


namespace rsm {
    namespace msq {
        namespace com {
         
            class MCNewClientRequest { //TODO ID -uint16_t
            public:
                /**
                 * Constructor for create request
                 * @param id -Hash code ID for Client 
                 * @param externID - external name for CLient
                 * @param requester - internal name of application which request for mqtt communication
                 * @param ipAddress - ip address for set communication
                 * @param topic - name of topic where client want to be connect
                 * @param direction - direction of communication |IN|OUT|BOTH|
                 * @param cleanSession  -|TRUE|FALSE|, true = default
                 * @param port - port for set communication, 1883 = default   
                 * @param qos - Quality of service, 0 = default 
                 * @param keepAlive - Keep Alive, 60 = default 
                 */
                MCNewClientRequest(std::function<void(const std::string&)> onMessage, const std::string& id,
                          const std::string& externID, const std::string& requester, const std::string& ipAddress,
                          const std::string& topic, const DirectionType direction, bool cleanSession = true,
                          int port = 1883, int qos = 0, int keepAlive = 60);
                virtual ~MCNewClientRequest();

                bool setSettings(const std::string& ipAddress, const int port, const int qos, const int keepAlive, const bool cleanSession);
                bool setDirection(const DirectionType type);
                const rsm::conn::mqtt::MosquittoSetting& getSettings() const;
                const DirectionType getDirection() const;
                const MCClientID& getClientID() const;
                
                std::function<void(const std::string&)> getOnMessage() const ;
 
                MCNewClientRequest(const MCNewClientRequest& orig) = delete;
                MCNewClientRequest& operator= (const MCNewClientRequest& orig) = delete;
                
            private:
                std::function<void(const std::string&)> m_onMessage;
                MCClientID m_clientID;
                DirectionType m_direction;
                rsm::conn::mqtt::MosquittoSetting m_settings;
                


            };
        }
    }
}
#endif /* MCREQUEST_H */

