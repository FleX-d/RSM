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
 * File:   MCOperationRequest.cpp
 * Author: Matus Bodorik
 * 
 * Created on January 25, 2018, 12:16 PM
 */

#include "MCOperationRequest.h"

namespace rsm {
    namespace msq {
        namespace com {

            MCOperationRequest::MCOperationRequest()
            {
            }

            MCOperationRequest::MCOperationRequest(const std::string& id, const std::string& requester, const OperationRequestType::Enum type) :
            m_ID(id),
            m_requester(requester),
            m_operationRequestType(type)
            {
            }

            MCOperationRequest::~MCOperationRequest()
            {
            }

            const std::string& MCOperationRequest::getID() const
            {
                return m_ID;
            }

            const OperationRequestType::Enum MCOperationRequest::getOperationRequestType() const
            {
                return m_operationRequestType;
            }

            const std::string& MCOperationRequest::getRequester() const
            {
                return m_requester;
            }
            
            void MCOperationRequest::setID(const std::string& id)
            {
                this->m_ID = id;
            }

            void MCOperationRequest::setOperationRequestType(const OperationRequestType::Enum type)
            {
                this->m_operationRequestType = type;
            }

            void MCOperationRequest::setRequester(const std::string& requester)
            {
                this->m_requester = requester;
            }

        }
    }
}
