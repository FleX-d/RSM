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
 * File:   MqttMessage.h
 * 
 * Author: Matus Bodorik
 *
 * Created on November 15, 2017, 1:10 PM
 */

#ifndef MQTTMESSAGE_H
#define MQTTMESSAGE_H

#include "MqttTypes.h"

namespace rsm {
    namespace conn {
        namespace mqtt {

            class MqttMessage {
            public:
                explicit MqttMessage(const mqttStr_t& topic, const mqttMsg_t& msg, int mid = 0, int payloadlen = 0, int qos = 0, bool retain = false);
                virtual ~MqttMessage() = default;

                MqttMessage(const MqttMessage& orig) = default;
                MqttMessage& operator=(const MqttMessage& orig) = default;

                const mqttMsg_t& getMessage() const;
                const mqttStr_t& getTopic() const;
                int getMid() const;
                int getLengthMessage()const;
                int getQOS() const;
                bool getRetain() const;

            private:
                const mqttStr_t m_topic;
                const mqttMsg_t m_msg;
                int m_mid;
                int m_payloadlen;
                int m_qos;
                bool m_retain;
            };
        } // namespace mqtt
    } // namespace conn
} // namespace rsm
#endif /* MQTTMESSAGE_H */

