
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
  *  Autogenerated output, do not edit!
  */

#include "IPCInterface.h"
#include <JsonObj.h>
#include <FleXdIPCConnector.h>
#include <FleXdEpoll.h>
#include <FleXdIPCMsg.h>
#include <FleXdIPCMsgTypes.h>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdint>

namespace flexd {
    namespace gen {

        IPCInterface::IPCInterface (flexd::icl::ipc::FleXdEpoll& poller)
        : IPCConnector(00000, poller, true),
          m_counter(0)
        {
        }

        IPCInterface::~IPCInterface()
        {
        }


        void IPCInterface::sendRequestAckMsg(uint32_t ID, uint8_t RequestAck)
        {
            flexd::icl::JsonObj json;

            json.add<int>("/id", 4);
            json.add<uint32_t>("/payload/ID", ID);
            json.add<uint8_t>("/payload/RequestAck", RequestAck);

            send(msgWrap(json.getJson(), ID), ID);
        }

        void IPCInterface::sendBackMsg(uint32_t ID, const std::string& PayloadMsg)
        {
            flexd::icl::JsonObj json;

            json.add<int>("/id", 5);
            json.add<std::string>("/payload/PayloadMsg", PayloadMsg);

            send(msgWrap(json.getJson(), ID), ID);
        }

        void IPCInterface::receiveMsg(flexd::icl::ipc::pSharedFleXdIPCMsg msg)
        {
            try{
                if(!msg) {
                    return;
                }

                flexd::icl::JsonObj json(msgUnwrap(msg));
                if(json.exist("/id"))
                {
                    int id;
                    json.get<int>("/id", id);
                    switch(id)
                    {
                        case 1: {
                            uint32_t ID;
                            std::string ExternID;
                            std::string Requester;
                            std::string IPAddress;
                            std::string Topic;
                            uint8_t Direction;
                            bool CleanSession;
                            int Port;
                            int QOS;
                            int KeepAlive;
                            bool tmp = true;

                            if(json.exist("/payload/ID")){
                                json.get<uint32_t>("/payload/ID", ID);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/ExternID")){
                                json.get<std::string>("/payload/ExternID", ExternID);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/Requester")){
                                json.get<std::string>("/payload/Requester", Requester);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/IPAddress")){
                                json.get<std::string>("/payload/IPAddress", IPAddress);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/Topic")){
                                json.get<std::string>("/payload/Topic", Topic);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/Direction")){
                                json.get<uint8_t>("/payload/Direction", Direction);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/CleanSession")){
                                json.get<bool>("/payload/CleanSession", CleanSession);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/Port")){
                                json.get<int>("/payload/Port", Port);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/QOS")){
                                json.get<int>("/payload/QOS", QOS);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/KeepAlive")){
                                json.get<int>("/payload/KeepAlive", KeepAlive);
                            } else {
                                tmp = false;
                            }

                            if(tmp){
                                receiveCreateClientMsg(ID, ExternID, Requester, IPAddress, Topic, Direction, CleanSession, Port, QOS, KeepAlive);
                            }
                            break;
                        }

                        case 2: {
                            uint32_t ID;
                            std::string Requester;
                            uint8_t Operation;
                            bool tmp = true;

                            if(json.exist("/payload/ID")){
                                json.get<uint32_t>("/payload/ID", ID);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/Requester")){
                                json.get<std::string>("/payload/Requester", Requester);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/Operation")){
                                json.get<uint8_t>("/payload/Operation", Operation);
                            } else {
                                tmp = false;
                            }

                            if(tmp){
                                receiveOperationMsg(ID, Requester, Operation);
                            }
                            break;
                        }

                        case 3: {
                            uint32_t ID;
                            std::string Topic;
                            std::string Requester;
                            std::string PayloadMsg;
                            bool tmp = true;

                            if(json.exist("/payload/ID")){
                                json.get<uint32_t>("/payload/ID", ID);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/Topic")){
                                json.get<std::string>("/payload/Topic", Topic);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/Requester")){
                                json.get<std::string>("/payload/Requester", Requester);
                            } else {
                                tmp = false;
                            }

                            if(json.exist("/payload/PayloadMsg")){
                                json.get<std::string>("/payload/PayloadMsg", PayloadMsg);
                            } else {
                                tmp = false;
                            }

                            if(tmp){
                                receivePublishMsg(ID, Topic, Requester, PayloadMsg);
                            }
                            break;
                        }
                    }
                }
            } catch(...){
                return;
            }
        }

        void IPCInterface::send(std::shared_ptr<flexd::icl::ipc::FleXdIPCMsg> Msg, uint32_t ID)
        {
            if(sendMsg(Msg, ID))
            {
                m_counter++;
            }
        }

        std::shared_ptr<flexd::icl::ipc::FleXdIPCMsg> IPCInterface::msgWrap(const std::string& payload, uint32_t ID)
        {
            flexd::icl::JsonObj json;

            json.add<uint8_t>(MCM_JSON_MSG_TYPE, 1);
            json.add<uint8_t>(MCM_JSON_MSG_COUNTER, m_counter);
            json.add<uint16_t>(MCM_JSON_PAYLOAD_CRC, flexd::icl::ipc::FleXdIPCMsg::calcCRC16(&payload[0] , payload.size()));
            json.add<uint32_t>(MCM_JSON_TIME_STAMP, getTimestamp());
            json.add<uint32_t>(MCM_JSON_FROM, getMyID());
            json.add<uint32_t>(MCM_JSON_TO, ID);
            json.add<std::string>(MCM_JSON_PAYLOAD, payload);

            std::string strJson(json.getJson());
            std::vector<uint8_t> msgPayload(strJson.begin(), strJson.end());
            return std::make_shared<flexd::icl::ipc::FleXdIPCMsg>(IPC_MSG_HEADER_PARAM_TYPE_MSG_TYPE, IPC_MSG_HEADER_IN_PAYLOAD_FLAG, std::move(msgPayload));
        }

        std::string IPCInterface::msgUnwrap(const std::shared_ptr<flexd::icl::ipc::FleXdIPCMsg>& msg)
        {
            //TODO returns only payload, should return whole message
            if(msg->getHeaderParamType() == IPC_MSG_HEADER_PARAM_TYPE_MSG_TYPE && msg->getHeaderParam() == IPC_MSG_HEADER_IN_PAYLOAD_FLAG) {
                std::string strJson(msg->getPayload().begin(), msg->getPayload().end());
                flexd::icl::JsonObj json(strJson);
                std::string payload;
                if(json.exist(MCM_JSON_PAYLOAD)) {
                    json.get<std::string>(MCM_JSON_PAYLOAD, payload);
                }
                return payload;
            }
            return std::string(msg->getPayload().begin(), msg->getPayload().end());
        }

        uint32_t IPCInterface::getTimestamp()
        {
            std::chrono::time_point<std::chrono::system_clock> p;
            p = std::chrono::system_clock::now();
            std::time_t time = std::chrono::duration_cast<std::chrono::milliseconds>(p.time_since_epoch()).count();
            return static_cast<uint32_t> (time);
        }

    }
}
