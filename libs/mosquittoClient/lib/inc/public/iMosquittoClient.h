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
 * File:   iMosquittoClient.h
 * 
 * Author: Matus Bodorik
 * 
 * Created on November 10, 2017, 10:07 AM
 */

#ifndef IMOSQUITTOCLIENT_H
#define IMOSQUITTOCLIENT_H

#include "MosquittoConnection.h"
#include "MqttTypes.h"
#include "MqttMessage.h"
#include <atomic>

namespace rsm {
    namespace conn {
        namespace mqtt {
            
            class MosquittoSetting;
            class iMosquittoClient : public MosquittoConnection {
            public:
                iMosquittoClient(const mqttStr_t& id, const MosquittoSetting& settings);
                virtual ~iMosquittoClient();

                int publishMessage(const MqttMessage& message);
                int subscribeTopic(const mqttStr_t& topic, int qos = 0);
                int unsubscribeTopic(const mqttStr_t& topic);
                int switchTopic(const mqttStr_t& leaveTopic, const mqttStr_t& subTopic, int qos = 0);
                const mqttStr_t& getVersion() const;
                
            protected:
                virtual void onRecon() = 0;
                virtual void onMessage(const MqttMessage& msg) = 0;
            private:
                std::atomic<bool> m_connected; 
                const mqttStr_t& m_version = "1.0.1";
            };
        } // namespace mqtt
    } // namespace conn
} // namespace rsm

#endif /* IMOSQUITTOCLIENT_H */
