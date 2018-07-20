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
 * File:   MCRequest.cpp
 * Author: Matus Bodorik
 *
 * Created on January 19, 2018, 9:23 AM
 */

#include "MCNewClientRequest.h"
#include "GenericClient.h"


namespace rsm {
    namespace msq {
        namespace com {

            MCNewClientRequest::MCNewClientRequest(std::function<void(uint32_t, const std::string&)> onMessage, uint32_t ID,
                                 const std::string& externID, const std::string& requester, const std::string& ipAddress,
                                 const std::string& topic, const DirectionType::Enum direction, bool cleanSession, int port, int qos, int keepAlive)
            : m_onMessage(onMessage),
              m_onGenMessage(nullptr),
              m_clientID(ID, externID, requester, topic),
              m_direction(direction),
              m_settings(ipAddress, port, qos, keepAlive, cleanSession)
            {
            }
            
            MCNewClientRequest::MCNewClientRequest(std::function<void(std::shared_ptr<flexd::gen::GenericClient::Header> , uint32_t, const std::string&)> onMessage, uint32_t ID,
                          const std::string& externID, const std::string& requester, const std::string& ipAddress,
                          const std::string& topic, const DirectionType::Enum direction, bool cleanSession,
                          int port, int qos, int keepAlive)
            : m_onMessage(nullptr),
              m_onGenMessage(onMessage),
              m_clientID(ID, externID, requester, topic),
              m_direction(direction),
              m_settings(ipAddress, port, qos, keepAlive, cleanSession)
            {
                
            }

            MCNewClientRequest::~MCNewClientRequest()
            {
            }

            bool MCNewClientRequest::setSettings(const std::string& ipAddress,const int port,
                                        const int qos, const int keepAlive, const bool cleanSession)
            {
                m_settings.setIpAddress(ipAddress);
                m_settings.setPort(port);
                m_settings.setQOS(qos);
                m_settings.setKeepAlive(keepAlive);
                m_settings.setCleanSession(cleanSession);
                return true;
            }

            bool MCNewClientRequest::setDirection(const DirectionType::Enum type)
            {
                m_direction = type;
                return true;
            }

            const rsm::conn::mqtt::MosquittoSetting& MCNewClientRequest::getSettings() const
            {
                return m_settings;
            }

            const DirectionType::Enum MCNewClientRequest::getDirection() const
            {
                return m_direction;
            }

            const MCClientID& MCNewClientRequest::getClientID() const
            {
                return m_clientID;
            }

            std::function<void(uint32_t, const std::string&)> MCNewClientRequest::getOnMessage() const
            {
                return m_onMessage;
            }
            
            std::function<void(std::shared_ptr<flexd::gen::GenericClient::Header>, uint32_t, const std::string&)> MCNewClientRequest::getOnGenMessage() const
            {
                return m_onGenMessage;
            }
            
            
        }
    }
}
