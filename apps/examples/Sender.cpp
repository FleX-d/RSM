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
 * File:   Monitor.cpp
 * 
 * Author: Matus Bodorik
 * 
 * Created on July 18, 2018, 15:07 
 */

#include "IPCInterface.h"
#include "FleXdEpoll.h"
#include "FleXdTimer.h"
#include <thread>
#include "unistd.h"
#include "iostream"

namespace flexd {
    namespace test{
        
    class Sender : public IPCInterface{
        public:
            uint16_t m_periodTime;
            flexd::icl::ipc::FleXdTimer m_Timer;
            
            Sender(flexd::icl::ipc::FleXdEpoll& poller) 
            :IPCInterface(00100, poller),
            m_periodTime(5),
            m_Timer(poller, m_periodTime, 0, true, [this](void){ this->onTimer(); })
            {   
                if(m_Timer.start())
                {
                    std::cout << " FleXdTimer.start() successful " << std::endl;
                } else {
                    std::cout << " FleXdTimer.start() failed " << std::endl;
                }
            }
            
            ~Sender(){ m_Timer.stop(); }
            
            Sender(const Sender&) = delete;
    
            void createClient(){
                std::cout <<"Send Request for Create Client"<< std::endl;
                std::shared_ptr<GenericClient::Header> header = std::make_shared<GenericClient::Header>();
                header->from = 00100;
                header->to = 00000;
                sendCreateClientMsg(std::move(header), 00100,"Sender","SenderSim","127.0.0.1", "backend/in", 2, true, 1883, 0, 60);
            }
            
            void onTimer() {
        
                srand(time(NULL));
                int number = std::rand() % 35;
                std::string message = "Data: temperature = " + std::to_string(number) + "°C"; 
                std::vector<uint8_t> data(message.begin(),message.end());
                std::cout <<"Sending data to MCM: " << message << std::endl;
                 std::shared_ptr<GenericClient::Header> header = std::make_shared<GenericClient::Header>();
                header->from = 00100;
                header->to = 00000;
                sendPublishMsg(header, 00100, "backend/in", "SenderSim", message);
            }
            
            void receiveRequestAckMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, uint8_t RequestAck)
            {
                std::cout <<"Receive Request Acknowledge: " << (int)RequestAck << std::endl;
            }
            
            void receiveBackMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& PayloadMsg) 
            {
                std::cout <<"Receive Message: " << PayloadMsg << std::endl;
            }
            
            void onConnectPeer(uint32_t peerID, bool genericPeer) 
            {
               createClient();
            }
        };
        
    }
}

int main(int argc, char** argv) {

    flexd::icl::ipc::FleXdEpoll poller(10);
    flexd::test::Sender sender(poller);
    poller.loop();
    
}
