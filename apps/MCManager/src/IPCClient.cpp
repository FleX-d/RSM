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
 * File:   IPCClient.cpp
 * Author: Matus Bodorik
 *
 * Created on January 25, 2018, 9:41 AM
 */

#include <iostream>
#include <limits>
#include "IPCClient.h"
#include "JsonObj.h"
#include "FleXdIPCMsgTypes.h"
#include "GenericClient.h"

namespace rsm {
    namespace msq {
        namespace com {

            IPCClient::IPCClient(flexd::icl::ipc::FleXdEpoll& poller)
            : IPCInterface(poller)
            {
            }

            IPCClient::~IPCClient()
            {
            }

            MCRequestAck IPCClient::addClient(const MCNewClientRequest& request)
            {
                return m_manager.addClient(request);
            }

            MCRequestAck IPCClient::sendRequest(const MCOperationRequest& request)
            {
                return m_manager.runClient(request);
            }

            MCRequestAck IPCClient::publish(const MCMessage& message)
            {
                return m_manager.publish(message);
            }

            void IPCClient::receiveCreateClientMsg(uint32_t ID, const std::string& ExternID, const std::string& Requester, const std::string& IPAddress, const std::string& Topic, uint8_t Direction, bool CleanSession, int Port, int QOS, int KeepAlive)
            {
                DirectionType::Enum direction;
                if(Direction == DirectionType::BOTH)
                {
                    direction = DirectionType::BOTH;
                } else if (Direction == DirectionType::IN)
                {
                    direction = DirectionType::IN;
                } else {
                    direction = DirectionType::OUT;
                }
                rsm::msq::com::MCNewClientRequest request([this](uint32_t id, const std::string& m){this->sendBackMsg(id,m);}, ID, ExternID, Requester, IPAddress, Topic, direction, CleanSession, Port, KeepAlive);
                MCRequestAck ack = this->addClient(request);
                if (ack.getAck() == RequestAckType::Success)
                {
                    sendRequestAckMsg(ID, 1);
                } else if (ack.getAck() == RequestAckType::Fail)
                {
                    sendRequestAckMsg(ID, 0);
                } else if (ack.getAck() == RequestAckType::ClientExist){
                    sendRequestAckMsg(ID, 2);
                }
            }

            void IPCClient::receiveOperationMsg(uint32_t ID, const std::string& Requester, uint8_t Operation)
            {
                if(Operation == OperationRequestType::Subscribe)
                {
                    MCOperationRequest request(ID, Requester, OperationRequestType::Subscribe);
                    MCRequestAck ack = this->sendRequest(request);
                    if(ack.getAck() == RequestAckType::Success)
                    {
                        sendRequestAckMsg(ID, 1);
                    } else
                    {
                        sendRequestAckMsg(ID, 0);
                    }
                } else if (Operation == OperationRequestType::Unsubscribe)
                {
                    MCOperationRequest request(ID, Requester, OperationRequestType::Unsubscribe);
                    MCRequestAck ack = this->sendRequest(request);
                    if(ack.getAck() == RequestAckType::Success)
                    {
                        sendRequestAckMsg(ID, 1);
                    } else
                    {
                        sendRequestAckMsg(ID, 0);
                    }
                }
            }

            void IPCClient::receivePublishMsg(uint32_t ID, const std::string& Topic, const std::string& Requester, const std::string& PayloadMsg)
            {
                if(!Topic.empty() && !Requester.empty())
                {
                    MCMessage m(ID, Topic, Requester, PayloadMsg);
                    MCRequestAck ack = this->publish(m);
                    if(ack.getAck() ==  RequestAckType::Success)
                    {
                        sendRequestAckMsg(ID, 1);
                    } else
                    {
                        sendRequestAckMsg(ID, 0);
                    }
                }
            }
            
            void IPCClient::receiveCreateClientMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& ExternID, const std::string& Requester, const std::string& IPAddress, const std::string& Topic, uint8_t Direction, bool CleanSession, int Port, int QOS, int KeepAlive)
            {
                DirectionType::Enum direction;
                if(Direction == DirectionType::BOTH)
                {
                    direction = DirectionType::BOTH;
                } else if (Direction == DirectionType::IN)
                {
                    direction = DirectionType::IN;
                } else {
                    direction = DirectionType::OUT;
                }
                rsm::msq::com::MCNewClientRequest request([this](std::shared_ptr<GenericClient::Header> header, uint32_t id, const std::string& m){this->sendBackMsg(header,id,m);}, ID, ExternID, Requester, IPAddress, Topic, direction, CleanSession, Port, KeepAlive);
                
                MCRequestAck ack = this->addClient(request);
                std::shared_ptr<flexd::gen::GenericClient::Header> headerToSend = std::make_shared<flexd::gen::GenericClient::Header>();
                headerToSend->from = getMyID();
                headerToSend->to = header->from;
                
                if (ack.getAck() == RequestAckType::Success)
                {
                    sendRequestAckMsg(std::move(headerToSend), header->from, 1);
                } else if (ack.getAck() == RequestAckType::Fail)
                {
                    sendRequestAckMsg(std::move(headerToSend), header->from, 0);
                } else if (ack.getAck() == RequestAckType::ClientExist){
                    sendRequestAckMsg(std::move(headerToSend), header->from, 2);
                }
            }
            
            void IPCClient::receiveOperationMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& Requester, uint8_t Operation)
            {
                std::shared_ptr<flexd::gen::GenericClient::Header> headerToSend = std::make_shared<flexd::gen::GenericClient::Header>();
                headerToSend->from = getMyID();
                headerToSend->to = header->from;
                if(Operation == OperationRequestType::Subscribe)
                {
                    MCOperationRequest request(header->from, Requester, OperationRequestType::Subscribe);
                    MCRequestAck ack = this->sendRequest(request);
                    if(ack.getAck() == RequestAckType::Success)
                    {
                        sendRequestAckMsg(std::move(headerToSend), header->from, 1);
                    } else
                    {
                        sendRequestAckMsg(std::move(headerToSend), header->from, 0);
                    }
                } else if (Operation == OperationRequestType::Unsubscribe)
                {
                    MCOperationRequest request(header->from, Requester, OperationRequestType::Unsubscribe);
                    MCRequestAck ack = this->sendRequest(request);
                    if(ack.getAck() == RequestAckType::Success)
                    {
                        sendRequestAckMsg(std::move(headerToSend), header->from, 1);
                    } else
                    {
                        sendRequestAckMsg(std::move(headerToSend), header->from, 0);
                    }
                }
            }
            
            void IPCClient::receivePublishMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& Topic, const std::string& Requester, const std::string& PayloadMsg)
            {
                std::shared_ptr<flexd::gen::GenericClient::Header> headerToSend = std::make_shared<flexd::gen::GenericClient::Header>();
                headerToSend->from = getMyID();
                headerToSend->to = header->from;
                if(!Topic.empty() && !Requester.empty())
                {
                    MCMessage m(header->from, Topic, Requester, PayloadMsg);
                    MCRequestAck ack = this->publish(m);
                    if(ack.getAck() ==  RequestAckType::Success)
                    {
                        sendRequestAckMsg(std::move(headerToSend), header->from, 1);
                    } else
                    {
                        sendRequestAckMsg(std::move(headerToSend), header->from, 0);
                    }
                }
            }
        }
    }
}
