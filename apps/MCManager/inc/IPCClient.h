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
 * File:   IPCClient.h
 * Author: Matus Bodorik
 *
 * Created on January 25, 2018, 9:41 AM
 */

#ifndef IPCCLIENT_H
#define IPCCLIENT_H

#include "MCManager.h"
#include "MCOperationRequest.h"
#include "MqttMessage.h"
#include "IPCInterface.h"

namespace rsm {
    namespace msq {
        namespace com {

            class IPCClient : public flexd::gen::IPCInterface { //inheritate from IPC
            public:
                IPCClient(flexd::icl::ipc::FleXdEpoll& poller);
                virtual ~IPCClient();

                MCRequestAck addClient(const MCNewClientRequest& request);
                MCRequestAck sendRequest(const MCOperationRequest& request);
                MCRequestAck publish(const MCMessage& message);

                virtual void receiveCreateClientMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& ExternID, const std::string& Requester, const std::string& IPAddress, const std::string& Topic, uint8_t Direction, bool CleanSession, int Port, int QOS, int KeepAlive) override;
                virtual void receiveOperationMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& Requester, uint8_t Operation) override;
                virtual void receivePublishMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& Topic, const std::string& Requester, const std::string& PayloadMsg) override;
                
                virtual void receiveCreateClientMsg(uint32_t ID, const std::string& ExternID, const std::string& Requester, const std::string& IPAddress, const std::string& Topic, uint8_t Direction, bool CleanSession, int Port, int QOS, int KeepAlive) override;
                virtual void receiveOperationMsg(uint32_t ID, const std::string& Requester, uint8_t Operation) override;
                virtual void receivePublishMsg(uint32_t ID, const std::string& Topic, const std::string& Requester, const std::string& PayloadMsg) override;
            
                virtual void onConnectPeer(uint32_t ID, bool genericPeer) override {}
                IPCClient(const IPCClient& orig) = delete;
                IPCClient& operator= (const IPCClient& orig) = delete;
            private:
                MCManager m_manager;
            };
        }
    }
}
#endif /* IPCCLIENT_H */

