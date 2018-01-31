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
 * File:   MCClientConf.h
 * Author: Matus Bodorik
 *
 * Created on January 19, 2018, 9:36 AM
 */

#ifndef MCCLIENTCONF_H
#define MCCLIENTCONF_H

#include "MCTypes.h"
#include <string>

namespace rsm {
    namespace msq {
        namespace com {

            class MCClientID {
            public:
                MCClientID();
                MCClientID(const std::string& id, const std::string& externalID,
                           const std::string& requester, const std::string& topic,
                           const std::string& ipAddress, const uint port);
                
                MCClientID(const std::string& id, const std::string& externalID, 
                           const std::string& requester, const std::string& topic, 
                           const std::string& uniqueID);
                ~MCClientID();

                const std::string& getID() const;
                const std::string& getExternalID() const;
                const std::string& getRequester() const;
                const std::string& getTopic() const;
                const std::string& getUniqueID() const;
                
                MCClientID(const MCClientID& orig) = delete;
                MCClientID& operator=(const MCClientID& orig) = delete;

            private:
                const std::string m_ID;
                const std::string m_externalID;
                const std::string m_requester;
                const std::string m_topic;
                const std::string m_uniqueID;

            };
        }
    }
}
#endif /* MCCLIENTCONF_H */

