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
 * File:   MCRequestAck.cpp
 * Author: Matus Bodorik
 * 
 * Created on January 25, 2018, 12:13 PM
 */

#include "MCRequestAck.h"
namespace rsm {
    namespace msq {
        namespace com {

            MCRequestAck::MCRequestAck()
            : m_ID(""),
            m_ack(RequestAckType::Success)
            {
            }
            
            MCRequestAck::MCRequestAck(const std::string& id, const RequestAckType::Enum type) 
            : m_ID(id),
            m_ack(type)
            {
            }
            
            MCRequestAck::~MCRequestAck()
            {
            }
            
            MCRequestAck::MCRequestAck(const MCRequestAck& orig)
            {
                m_ID = orig.m_ID;
                m_ack = orig.m_ack;
            }

            const RequestAckType::Enum MCRequestAck::getAck() const
            {
                return m_ack;
            }

            const std::string& MCRequestAck::getID() const
            {
                return m_ID;
            }

            void MCRequestAck::setAck(const RequestAckType::Enum ack)
            {
                this->m_ack = ack;
            }

            void MCRequestAck::setID(const std::string& id)
            {
                this->m_ID = id;
            }

        }
    }
}