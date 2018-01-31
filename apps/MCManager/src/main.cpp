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
 * Created on January 19, 2018, 09:19 PM
 */

#include "MCManager.h"
#include "MCNewClientRequest.h"
#include "MCTypes.h"
#include "IPCClient.h"
#include <iostream>
#include <functional>



int main(int argc, char** argv)
{
    rsm::msq::com::IPCClient ipc;
    rsm::msq::com::MCRequestAck ack;
    
    rsm::msq::com::MCNewClientRequest request([&ipc](const std::string& m){ipc.echo(m);}, "6H5616FK", "CLIENTFLEXD1", "FlexD", "127.0.0.1", "test", rsm::msq::com::BOTH,  true,  1883,  0,  60);
    ack = ipc.addClient(request);
    std::cout << "ID: " << ack.getID() << " status: " << ack.getAck()<< std::endl;
    
    rsm::msq::com::MCOperationRequest operation("6H5616FK" , "FlexD", rsm::msq::com::Subscribe);
    ack = ipc.sendRequest(operation);
    std::cout << "ID: " << ack.getID() << " status: " << ack.getAck()<< std::endl;
    
    
    rsm::msq::com::MCMessage msg("6H5616FK", "FlexD", "Communication is working!");
    ack = ipc.publish(msg);
    std::cout << "ID: " << ack.getID() << " status: " << ack.getAck()<< std::endl;
    
    while(1){}
    //manager.runClient();

    return 0;
}

