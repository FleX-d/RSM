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
            }

            MCRequestAck MCManager::addClient(const MCNewClientRequest& request)
            {
                auto it = m_clientMap.find(request.getClientID().getUniqueID());
                MCRequestAck ack;

                if (it == m_clientMap.end())
                {
                    std::shared_ptr<MCClient> client = m_factory.createClient(request);
                    m_clientMap.insert(std::pair<std::string, std::shared_ptr < MCClient >> (client->getClientID().getUniqueID(), client));
                    ack.setAck(Success);
                    ack.setID(client->getClientID().getID());
                    return ack;
                }
                ack.setAck(ClientExist);
                ack.setID(request.getClientID().getID());
                return ack;
            }

            MCRequestAck MCManager::runClient(const MCOperationRequest& request)
            {
                MCRequestAck ack;
                std::string unique = request.getID() + request.getRequester();
                auto it = m_clientMap.find(unique);
                
                if (it != m_clientMap.end())
                {
                    if (request.getOperationRequest() == Subscribe)
                    {
                        if(it->second->subscribe())
                        {
                            ack.setAck(Success);
                            ack.setID(it->second->getClientID().getID());
                            return ack;
                        }
                    } else if (request.getOperationRequest() == Unsubscribe)
                    {
                        if(it->second->unsubscribe())
                        {
                            ack.setAck(Success);
                            ack.setID(it->second->getClientID().getID());
                            return ack;
                        }
                    }
                }
                ack.setAck(Fail);
                ack.setID(it->second->getClientID().getID());
                return ack;
            }


            MCRequestAck MCManager::clientPublish(const MCMessage& message)
            {
                MCRequestAck ack;
                std::string unique = message.getID() + message.getRequester();
                auto it = m_clientMap.find(unique);
                
                if (it != m_clientMap.end())
                {
                    if(it->second->send(message))
                    {
                        ack.setAck(Success);
                        ack.setID(it->second->getClientID().getID());
                        return ack;
                    }
                }
                ack.setAck(Fail);
                ack.setID(it->second->getClientID().getID());
                return ack;
            }
        }
    }
}