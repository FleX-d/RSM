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
 * File:   MCMessage.h
 * Author: Matus Bodorik
 *
 * Created on January 19, 2018, 9:38 AM
 */

#ifndef MCMESSAGE_H
#define MCMESSAGE_H

#include <string>

namespace rsm {
    namespace msq {
        namespace com {

            class MCMessage {
            public:
                MCMessage();
                MCMessage(const std::string& id, const std::string& topic, const std::string& requester, const std::string& payload);
                virtual ~MCMessage();
                
                void setPayload(const std::string& payload);
                void setID(const std::string& id);
                void setRequester(const std::string& requester);
                void setTopic(const std::string& topic);
                const std::string& getTopic() const;
                const std::string& getPayload() const;
                const std::string& getID() const;
                const std::string& getRequester() const;
                
                MCMessage& operator=(const MCMessage& orig) = delete;
                MCMessage(const MCMessage& orig) = delete;
                
            private:
                std::string m_ID;
                std::string m_topic;
                std::string m_requester;
                std::string m_payload;
                
            };
        }
    }
}
#endif /* MCMESSAGE_H */

