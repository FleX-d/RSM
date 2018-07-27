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
 * File:   exampleManager.cpp
 * 
 * Author: Matus Bodorik
 * 
 * Created on July 18, 2018, 15:07 
 */


#include <gtest/gtest.h>
#include "MCManager.h"
#include "MCNewClientRequest.h"
#include "MCOperationRequest.h"
#include "MCRequestAck.h"
#include "MCMessage.h"
#include <functional>

namespace {
    
    rsm::msq::com::MCManager manager;
    
    TEST(MCManager, add_Client_Request){
        
        std::function<void(uint32_t id, const std::string& m)> onMessage;
        uint32_t ID = 12658;
        const std::string& externID = "Test"; 
        const std::string& requester = "TestApp";
        const std::string& ipAddress = "127.0.0.1";
        const std::string& topic = "test";
        const rsm::msq::com::DirectionType::Enum direction = rsm::msq::com::DirectionType::BOTH;
        bool cleanSession = true;
        int port = 1883;
        int qos = 0;
        int keepAlive = 60;
        rsm::msq::com::MCNewClientRequest request(onMessage, ID, externID, requester, ipAddress, topic, direction, cleanSession, port, qos ,keepAlive);
        rsm::msq::com::MCRequestAck ack = manager.addClient(request);
        
        EXPECT_EQ(ack.getAck(), rsm::msq::com::RequestAckType::Success);
    }
    
    TEST(MCManager, add_Client_And_subscribe){
        
        std::function<void(uint32_t id, const std::string& m)> onMessage;
        uint32_t ID = 12659;
        const std::string& externID = "Test1"; 
        const std::string& requester = "TestApp1";
        const std::string& ipAddress = "127.0.0.1";
        const std::string& topic = "test";
        const rsm::msq::com::DirectionType::Enum direction = rsm::msq::com::DirectionType::BOTH;
        bool cleanSession = true;
        int port = 1883;
        int qos = 0;
        int keepAlive = 60;
        rsm::msq::com::MCNewClientRequest request(onMessage, ID, externID, requester, ipAddress, topic, direction, cleanSession, port, qos ,keepAlive);
        rsm::msq::com::MCRequestAck ack = manager.addClient(request);
        sleep(1);
        
        EXPECT_EQ(ack.getAck(), rsm::msq::com::RequestAckType::Success);
        
        if(ack.getAck() == rsm::msq::com::RequestAckType::Success){
            rsm::msq::com::MCOperationRequest requestOperation(ID, requester, rsm::msq::com::OperationRequestType::Subscribe);
            ack = manager.runClient(requestOperation);
            EXPECT_EQ(ack.getAck(), rsm::msq::com::RequestAckType::Success);
            sleep(1);
        }
    }
    
    TEST(MCManager, add_Client_And_subscribe_unsubscribe)
    {
         std::function<void(uint32_t id, const std::string& m)> onMessage;
        uint32_t ID = 12659;
        const std::string& externID = "Test2"; 
        const std::string& requester = "TestApp2";
        const std::string& ipAddress = "127.0.0.1";
        const std::string& topic = "test";
        const rsm::msq::com::DirectionType::Enum direction = rsm::msq::com::DirectionType::BOTH;
        bool cleanSession = true;
        int port = 1883;
        int qos = 0;
        int keepAlive = 60;
        rsm::msq::com::MCNewClientRequest request(onMessage, ID, externID, requester, ipAddress, topic, direction, cleanSession, port, qos ,keepAlive);
        rsm::msq::com::MCRequestAck ack = manager.addClient(request);
        sleep(1);
        
        EXPECT_EQ(ack.getAck(), rsm::msq::com::RequestAckType::Success);
        
        if(ack.getAck() == rsm::msq::com::RequestAckType::Success){
            rsm::msq::com::MCOperationRequest requestOperation(ID, requester, rsm::msq::com::OperationRequestType::Subscribe);
            ack = manager.runClient(requestOperation);
            EXPECT_EQ(ack.getAck(), rsm::msq::com::RequestAckType::Success);
            sleep(1);
            if(ack.getAck() == rsm::msq::com::RequestAckType::Success){
                requestOperation.setOperationRequestType(rsm::msq::com::OperationRequestType::Unsubscribe);
                ack = manager.runClient(requestOperation);
                EXPECT_EQ(ack.getAck(), rsm::msq::com::RequestAckType::Success);
            }
        }
    }
    
    TEST(MCManager, add_Client_And_publish)
    {
         std::function<void(uint32_t id, const std::string& m)> onMessage;
        uint32_t ID = 12659;
        const std::string& externID = "Test3"; 
        const std::string& requester = "TestApp3";
        const std::string& ipAddress = "127.0.0.1";
        const std::string& topic = "test";
        const rsm::msq::com::DirectionType::Enum direction = rsm::msq::com::DirectionType::BOTH;
        bool cleanSession = true;
        int port = 1883;
        int qos = 0;
        int keepAlive = 60;
        rsm::msq::com::MCNewClientRequest request(onMessage, ID, externID, requester, ipAddress, topic, direction, cleanSession, port, qos ,keepAlive);
        rsm::msq::com::MCRequestAck ack = manager.addClient(request);
        sleep(1);
        
        EXPECT_EQ(ack.getAck(), rsm::msq::com::RequestAckType::Success);
        
        if(ack.getAck() == rsm::msq::com::RequestAckType::Success){
            std::string PayloadMsg = "Comunication working! ";
            rsm::msq::com::MCMessage m(ID, topic, requester, PayloadMsg);
            ack = manager.publish(m);
            EXPECT_EQ(ack.getAck(), rsm::msq::com::RequestAckType::Success);
        }
    }
}
