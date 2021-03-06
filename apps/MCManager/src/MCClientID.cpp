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
 * File:   MCClientConf.cpp
 * Author: Matus Bodorik
 * 
 * Created on January 19, 2018, 9:36 AM
 */

#include "MCClientID.h"

namespace rsm {
    namespace msq {
        namespace com {
            
            MCClientID::~MCClientID()
            {
            }

            MCClientID::MCClientID(const std::string& id, const std::string& externalID, 
                                   const std::string& requester, const std::string& topic) 
            : m_ID(id),
            m_externalID(externalID),
            m_requester(requester),
            m_topic(topic),
            m_uniqueID(m_ID + m_requester)
            {
            }

            MCClientID::MCClientID(const std::string& id, const std::string& externalID, 
                                   const std::string& requester, const std::string& topic, 
                                   const std::string& uniqueID) 
            : m_ID(id),
            m_externalID(externalID),
            m_requester(requester),
            m_topic(topic),
            m_uniqueID(uniqueID)
            {
            }
            
            MCClientID::MCClientID()
            {    
            }

            const std::string& MCClientID::getID() const
            {
                return m_ID;
            }

            const std::string& MCClientID::getExternalID() const
            {
                return m_externalID;
            }

            const std::string& MCClientID::getRequester() const
            {
                return m_requester;
            }

            const std::string& MCClientID::getTopic() const
            {
                return m_topic;
            }

            const std::string& MCClientID::getUniqueID() const
            {
                return m_uniqueID;
            }
        }
    }
}