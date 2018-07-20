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
#include "GenericClient.h"
#include <memory>


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
                 * @param ipAddress - ip address for communication
                 * @param topic - name of topic where client want to be connect
                 * @param direction - direction of communication |IN|OUT|BOTH|
                 * @param cleanSession  -|TRUE|FALSE|, true = default
                 * @param port - port for communication, 1883 = default
                 * @param qos - Quality of service, 0 = default
                 * @param keepAlive - Keep Alive, 60 = default
                 */
                MCNewClientRequest(std::function<void(uint32_t, const std::string&)> onMessage, uint32_t ID,
                          const std::string& externID, const std::string& requester, const std::string& ipAddress,
                          const std::string& topic, const DirectionType::Enum direction, bool cleanSession = true,
                          int port = 1883, int qos = 0, int keepAlive = 60);
                
                MCNewClientRequest(std::function<void(std::shared_ptr<flexd::gen::GenericClient::Header> , uint32_t, const std::string&)> onMessage, uint32_t ID,
                          const std::string& externID, const std::string& requester, const std::string& ipAddress,
                          const std::string& topic, const DirectionType::Enum direction, bool cleanSession = true,
                          int port = 1883, int qos = 0, int keepAlive = 60);
                virtual ~MCNewClientRequest();
                /**
                 * Function to set parameters to Mosquitto settings
                 * @param ipAddress -Ip address for communication
                 * @param port -  port for communication, 1883 = default
                 * @param qos - Quality of service, 0 = default
                 * @param keepAlive - Keep Alive, 60 = default
                 * @param cleanSession - |TRUE|FALSE|, true = default
                 * @return true if set parameters
                 */
                bool setSettings(const std::string& ipAddress, const int port, const int qos, const int keepAlive, const bool cleanSession);
                /**
                 * Function to set direction of communication
                 * @param type - type of direction |IN|OUT|BOTH|
                 * @return true if set direction
                 */
                bool setDirection(const DirectionType::Enum type);
                /**
                 * Function return const reference to Mosquitto settings
                 * @return const reference to Mosquitto settings
                 */
                const rsm::conn::mqtt::MosquittoSetting& getSettings() const;
                /**
                 * Function return type of direction
                 * @return type of direction |IN|OUT|BOTH|
                 */
                const DirectionType::Enum getDirection() const;
                /**
                 * Function return client identifiers
                 * @return reference to MCClientID which contains topic, id, requester and externalID
                 */
                const MCClientID& getClientID() const;
                /**
                 * Function return lambda function onMessage
                 * @return return lambda function onMessage
                 */
                std::function<void(uint32_t, const std::string&)> getOnMessage() const ;
                
                std::function<void(std::shared_ptr<flexd::gen::GenericClient::Header>, uint32_t, const std::string&)> getOnGenMessage() const ;

                MCNewClientRequest(const MCNewClientRequest& orig) = delete;
                MCNewClientRequest& operator= (const MCNewClientRequest& orig) = delete;

            private:
                std::function<void(uint32_t, const std::string&)> m_onMessage;
                std::function<void(std::shared_ptr<flexd::gen::GenericClient::Header>, uint32_t, const std::string&)> m_onGenMessage;
                MCClientID m_clientID;
                DirectionType::Enum m_direction;
                rsm::conn::mqtt::MosquittoSetting m_settings;
            };
        }
    }
}
#endif /* MCREQUEST_H */

