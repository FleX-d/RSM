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
 * File:   MosquittoSetting.h
 * 
 * Author: Matus Bodorik
 *
 * Created on November 20, 2017, 10:25 AM
 */

#ifndef MOSQUITTOSETTING_H
#define MOSQUITTOSETTING_H

#include "MqttTypes.h"

namespace rsm {
    namespace conn {
        namespace mqtt {

            class MosquittoSetting {
            public:
                explicit MosquittoSetting(const mqttStr_t& ipAddress, int port=1883, int qos=0, int keepAlive=60, bool cleanSession=true);
                virtual ~MosquittoSetting() = default;
                
                void setIpAddress(const mqttStr_t& ipAddress);
                void setPort(int port);
                void setQOS(int qos);
                void setCleanSession(bool cleanSession);
                void setKeepAlive(int keepAlive);
                
                const mqttStr_t& getIpAddress()const;
                int getPort() const;
                int getQOS() const;
                bool getCleanSession() const;
                int getKeepAlive()const;
                
                MosquittoSetting(const MosquittoSetting& orig) = default;
                MosquittoSetting& operator=(const MosquittoSetting& orig) = default;
                
            private:
                mqttStr_t m_ipAddress;
                int m_port;
                int m_qos;
                int m_keepAlive;
                bool m_cleanSession;
            };

        } // namespace mqtt
    } // namespace conn
} // namespace rsm

#endif /* MOSQUITTOSETTING_H */
