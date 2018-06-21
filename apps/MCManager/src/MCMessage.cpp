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
 * File:   MCMessage.cpp
 * Author: Matus Bodorik
 *
 * Created on January 19, 2018, 9:38 AM
 */

#include "MCMessage.h"

namespace rsm {
    namespace msq {
        namespace com {

            MCMessage::MCMessage(uint32_t ID, const std::string& topic, const std::string& requester, const std::string& payload) :
            m_ID(ID),
            m_topic(topic),
            m_requester(requester),
            m_payload(payload)
            {
            }

            MCMessage::~MCMessage()
            {
            }

            uint32_t MCMessage::getID() const
            {
                return m_ID;
            }

            const std::string& MCMessage::getPayload() const
            {
                return m_payload;
            }

            const std::string& MCMessage::getRequester() const
            {
                return m_requester;
            }

            const std::string& MCMessage::getTopic() const
            {
                return m_topic;
            }

            void MCMessage::setTopic(const std::string& topic)
            {
                this->m_topic = topic;
            }

            void MCMessage::setID(uint32_t ID)
            {
                this->m_ID = ID;
            }

            void MCMessage::setPayload(const std::string& payload)
            {
                this->m_payload = payload;
            }

            void MCMessage::setRequester(const std::string& requester)
            {
                this->m_requester = requester;
            }
        }
    }
}
