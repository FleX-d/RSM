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
 * File:   TransferManagerTest.cpp
 * 
 * Author: Matus Bodorik
 * 
 * Created on July 18, 2018, 15:07 
 */

#include <gtest/gtest.h>
#include "iTransferRequest.h"
#include "TMFactory.h"
#include "FleXdEpoll.h"

namespace {
    
    TEST(Factory, Test_Factory){
        flexd::rsm::conn::iTransferRequest request1("http://test.url/test.dat" , "/home/dev/work/TransferManager/text2.txt", flexd::rsm::conn::TransferType::Enum::HTTPDownload);
        flexd::rsm::conn::iTransferRequest request2("http://test.url/test.dat" , "/home/dev/work/TransferManager/text2.txt", flexd::rsm::conn::TransferType::Enum::HTTPUpload);
        flexd::rsm::conn::iTransferRequest request3("http://test.url/test.dat" , "/home/dev/work/TransferManager/text2.txt", flexd::rsm::conn::TransferType::Enum::FTPDownload);
        flexd::rsm::conn::iTransferRequest request4("http://test.url/test.dat" , "/home/dev/work/TransferManager/text2.txt", flexd::rsm::conn::TransferType::Enum::FTPUpload);
        
        flexd::icl::ipc::FleXdEpoll poller(10);
        
        auto client1 = flexd::rsm::conn::TMFactory::createInstance(request1, poller);
        auto client2 = flexd::rsm::conn::TMFactory::createInstance(request2, poller);
        auto client3 = flexd::rsm::conn::TMFactory::createInstance(request3, poller);
        auto client4 = flexd::rsm::conn::TMFactory::createInstance(request4, poller);
        
        ASSERT_NE(client1, nullptr);
        ASSERT_NE(client2, nullptr);
        ASSERT_NE(client3, nullptr);
        ASSERT_NE(client4, nullptr);
        
    }
}
