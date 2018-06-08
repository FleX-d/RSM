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
 * File:   MCManager.cpp
 * Author: Matus Bodorik
 * 
 * Created on January 19, 2018, 9:25 AM
 */

#include <memory>
#include "FleXdLogger.h"
#include "MCTypes.h"
#include "MCManager.h"

namespace rsm {
    namespace msq {
        namespace com {

            MCManager::MCManager()
            {
            }

            MCManager::~MCManager()
            {
                FLEX_LOG_TRACE("MCManager::~MCManager() -> Destroyed");
            }

            MCRequestAck MCManager::addClient(const MCNewClientRequest& request)
            {
                auto it = m_clientMap.find(request.getClientID().getUniqueID());
                MCRequestAck ack;
                ack.setID(request.getClientID().getID());
                if (it == m_clientMap.end())
                {
                    std::shared_ptr<MCClient> client = std::make_shared<MCClient>(request);
                    if(client)
                    {
                        m_clientMap.insert(std::pair<std::string, std::shared_ptr < MCClient >> (client->getClientID().getUniqueID(), client));
                        ack.setAck(RequestAckType::Success);
                        FLEX_LOG_TRACE("MCManager::addClient() -> Client: ", client->getClientID().getID() ," create Success!");
                    } else {
                        ack.setAck(RequestAckType::Fail);
                        FLEX_LOG_WARN("MCFactory::createClient() -> Client : ", client->getClientID().getID() ," create Fail!");
                    }
                } else {
                    ack.setAck(RequestAckType::ClientExist);
                    FLEX_LOG_WARN("MCManager::addClient() -> Client is already exist");
                }
                return std::move(ack);
            }

            MCRequestAck MCManager::runClient(const MCOperationRequest& request)
            {
                std::string uniqueID = request.getID() + request.getRequester();
                auto it = m_clientMap.find(uniqueID);
                MCRequestAck ack;
                if (it != m_clientMap.end())
                {
                    ack.setID(it->second->getClientID().getID());
                    if (request.getOperationRequestType() == OperationRequestType::Subscribe)
                    {
                        if(it->second->subscribe())
                        {
                            ack.setAck(RequestAckType::Success);
                            FLEX_LOG_TRACE("MCManager::runClient() -> Client Subscribe Success!");
                        } else {
                            ack.setAck(RequestAckType::Fail);
                            FLEX_LOG_ERROR("MCManager::runClient() -> Client Subscribe Fail!");
                        }
                    } else if (request.getOperationRequestType() == OperationRequestType::Unsubscribe)
                    {
                        if(it->second->unsubscribe())
                        {
                            ack.setAck(RequestAckType::Success);
                            FLEX_LOG_TRACE("MCManager::runClient() -> Client Unsubscribe Success!");
                        } else {
                            ack.setAck(RequestAckType::Fail);
                            FLEX_LOG_ERROR("MCManager::runClient() -> Client Unsubscribe Fail!");
                        }
                    }
                } else {
                    ack.setAck(RequestAckType::ClientNotExist);
                    FLEX_LOG_WARN("MCManager::runClient() -> Client with ID is not exist");
                }
                return std::move(ack);
            }


            MCRequestAck MCManager::publish(const MCMessage& message)
            {
                MCRequestAck ack;
                std::string uniqueID = message.getID() + message.getRequester();
                auto it = m_clientMap.find(uniqueID);
                
                if (it != m_clientMap.end())
                {
                    ack.setID(it->second->getClientID().getID());
                    if(it->second->send(message))
                    {
                        ack.setAck(RequestAckType::Success);
                        FLEX_LOG_TRACE("MCManager::clientPublish() -> Client Publish Success!");
                    } else {
                        ack.setAck(RequestAckType::Fail);
                        FLEX_LOG_ERROR("MCManager::clientPublish() -> Client Publish Fail!");
                    }
                } else 
                {
                    ack.setAck(RequestAckType::ClientNotExist);
                    FLEX_LOG_WARN("MCManager::clientPublish() -> Client with ID is not exist");
                }
                return std::move(ack);
            }
            
        }
    }
}
