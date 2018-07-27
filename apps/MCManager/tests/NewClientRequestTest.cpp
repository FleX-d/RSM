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
#include "MCNewClientRequest.h"
#include "GenericClient.h"

namespace {
    
    TEST(MCNewClientRequest, Test_MC_New_Client_Request){
        
        std::function<void(uint32_t id, const std::string& m)> onMessage([](uint32_t id, const std::string& m){});
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
        
        
        ASSERT_NE(request.getOnMessage(),  nullptr);
        ASSERT_EQ(nullptr, request.getOnGenMessage());
        
        ASSERT_EQ(ID, request.getClientID().getID());
        ASSERT_EQ(externID, request.getClientID().getExternalID());
        ASSERT_EQ(requester, request.getClientID().getRequester());
        ASSERT_EQ(ipAddress, request.getSettings().getIpAddress());
        ASSERT_EQ(topic, request.getClientID().getTopic());
        ASSERT_EQ(direction, request.getDirection());
        ASSERT_EQ(cleanSession, request.getSettings().getCleanSession());
        ASSERT_EQ(port, request.getSettings().getPort());
        ASSERT_EQ(qos, request.getSettings().getQOS());
        ASSERT_EQ(keepAlive, request.getSettings().getKeepAlive());
        
  
        const rsm::msq::com::DirectionType::Enum direction1 = rsm::msq::com::DirectionType::IN;
         const std::string& ipAddress1 = "128.0.0.1";
        bool cleanSession1 = false;
        int port1 = 1884;
        int qos1 = 2;
        int keepAlive1 = 40;
        
        ASSERT_TRUE(request.setDirection(direction1));
        ASSERT_EQ(direction1, request.getDirection());
        
        ASSERT_TRUE(request.setSettings(ipAddress1, port1, qos1, keepAlive1, cleanSession1));
        ASSERT_EQ(ipAddress1, request.getSettings().getIpAddress());
        ASSERT_EQ(cleanSession1, request.getSettings().getCleanSession());
        ASSERT_EQ(port1, request.getSettings().getPort());
        ASSERT_EQ(qos1, request.getSettings().getQOS());
        ASSERT_EQ(keepAlive1, request.getSettings().getKeepAlive());
    }
    
    
    TEST(MCNewClientRequest, Test_MC_New_Client_Request_Generic){
        
        std::function<void(std::shared_ptr<flexd::gen::GenericClient::Header> header , uint32_t id, const std::string& m)> onGenMessage([](std::shared_ptr<flexd::gen::GenericClient::Header> header , uint32_t id, const std::string& m){});
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
        rsm::msq::com::MCNewClientRequest request(onGenMessage, ID, externID, requester, ipAddress, topic, direction, cleanSession, port, qos ,keepAlive);
        
        ASSERT_NE(request.getOnGenMessage(), nullptr);
        ASSERT_EQ(nullptr, request.getOnMessage());
        
        ASSERT_EQ(ID, request.getClientID().getID());
        ASSERT_EQ(externID, request.getClientID().getExternalID());
        ASSERT_EQ(requester, request.getClientID().getRequester());
        ASSERT_EQ(ipAddress, request.getSettings().getIpAddress());
        ASSERT_EQ(topic, request.getClientID().getTopic());
        ASSERT_EQ(direction, request.getDirection());
        ASSERT_EQ(cleanSession, request.getSettings().getCleanSession());
        ASSERT_EQ(port, request.getSettings().getPort());
        ASSERT_EQ(qos, request.getSettings().getQOS());
        ASSERT_EQ(keepAlive, request.getSettings().getKeepAlive());
        
  
        const rsm::msq::com::DirectionType::Enum direction1 = rsm::msq::com::DirectionType::IN;
         const std::string& ipAddress1 = "128.0.0.1";
        bool cleanSession1 = false;
        int port1 = 1884;
        int qos1 = 2;
        int keepAlive1 = 40;
        
        ASSERT_TRUE(request.setDirection(direction1));
        ASSERT_EQ(direction1, request.getDirection());
        
        ASSERT_TRUE(request.setSettings(ipAddress1, port1, qos1, keepAlive1, cleanSession1));
        ASSERT_EQ(ipAddress1, request.getSettings().getIpAddress());
        ASSERT_EQ(cleanSession1, request.getSettings().getCleanSession());
        ASSERT_EQ(port1, request.getSettings().getPort());
        ASSERT_EQ(qos1, request.getSettings().getQOS());
        ASSERT_EQ(keepAlive1, request.getSettings().getKeepAlive());
    }
}
