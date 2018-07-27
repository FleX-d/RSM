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
#include "MCMessage.h"

namespace {
    
    TEST(MCMessage, Test_MC_Message){
        
        
        uint32_t ID = 12658;
        const std::string& requester = "TestApp";
        const std::string& topic = "test";
        std::string payload = "Communication working!";
        rsm::msq::com::MCMessage msg(ID, topic, requester, payload);
        
        ASSERT_EQ(ID, msg.getID());
        ASSERT_EQ(requester, msg.getRequester());
        ASSERT_EQ(topic, msg.getTopic());
        ASSERT_EQ(payload, msg.getPayload());
        

        msg.setTopic("Test1");
        msg.setRequester("TestApp2");
        msg.setPayload("Communication Fail!");
        
        ASSERT_EQ("Test1", msg.getTopic());
        ASSERT_EQ("TestApp2", msg.getRequester());
        ASSERT_EQ("Communication Fail!" , msg.getPayload());
        
    }
}
