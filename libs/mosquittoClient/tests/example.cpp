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
 * File: example.cpp
 * Author: Matus Bodorik
 *
 * Created on January 17, 2018, 2:20 PM
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include "MqttTypes.h"
#include "MqttMessage.h"
#include "iMosquittoClient.h"
#include "MosquittoSetting.h"

class Client : public rsm::conn::mqtt::iMosquittoClient 
{
    public:
        Client(const rsm::conn::mqtt::mqttStr_t& id, const rsm::conn::mqtt::MosquittoSetting& settings)
        : iMosquittoClient(id, settings) 
        {
        }

        virtual ~Client() 
        {
        }
        
        
        virtual void onMessage(const rsm::conn::mqtt::MqttMessage& msg) override 
        {
            std::cout << "Client get message ... " << msg.getMessage() << "\n";
        }
        
        void onRecon() override;

};

int main(int argc, char** argv) {
    
    std::string topic = "test";
    rsm::conn::mqtt::MosquittoSetting setting("127.0.0.1");
    
    auto client1 = std::make_shared<Client>("client1", setting);
    auto client2 = std::make_shared<Client>("client2", setting);
    
    client1->subscribeTopic(topic);
    std::this_thread::sleep_for(std::chrono::seconds(1));    
    
    client2->publishMessage(rsm::conn::mqtt::MqttMessage(topic , " Communication is working! "));
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    client1->unsubscribeTopic(topic);

    return 0;
}

