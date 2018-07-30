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
 * File:   main.cpp
 * Author: Matus Bodorik
 *
 * Created on December 15, 2017, 12:19 PM
 */

#include "iTransferRequest.h"
#include "HTTPDownloadClient.h"
#include "TransferTypes.h"
#include "TransferManager.h"
#include <FleXdLogger.h>
#include <FleXdEvent.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {

    flexd::rsm::conn::iTransferRequest request("http://test.url/test.dat" , "/home/dev/work/TransferManager/text2.txt", flexd::rsm::conn::TransferType::Enum::HTTPDownload);
    flexd::rsm::conn::iTransferRequest request2("http://test.url/upload/index.php" , "/home/dev/work/TransferManager/file1g", flexd::rsm::conn::TransferType::Enum::HTTPUpload);
    flexd::rsm::conn::iTransferRequest request3("http://test.url/upload/index.php" , "/home/dev/work/TransferManager/text2.txt", flexd::rsm::conn::TransferType::Enum::HTTPUpload);
    
    flexd::icl::ipc::FleXdEpoll poller(10);
    
    FLEX_LOG_INIT(poller, "TransferManager");
    FLEX_LOG_TRACE("TransferManager starting...");
    flexd::rsm::conn::TransferManager mng(poller);
    flexd::icl::ipc::FleXdTermEvent e(poller);
    if(e.init()) {
        mng.addTransfer(request2);
        mng.runTransfer();
        mng.getTransferInfo();
    //  mng.abortTransfer();
        
        poller.loop();
    }
    
    FLEX_LOG_UNINIT();

    return 0;
}

