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
 * File:   MqttMessage.cpp
 * 
 * Author: Matus Bodorik
 * 
 * Created on November 15, 2017, 1:10 PM
 */

#include "MqttMessage.h"


namespace rsm {
    namespace conn {
        namespace mqtt {

            MqttMessage::MqttMessage(const mqttStr_t& topic, const mqttMsg_t& msg, int mid, int payloadlen, int qos, bool retain)
            : m_topic(topic),
            m_msg(msg),
            m_mid(mid),
            m_payloadlen(payloadlen),
            m_qos(qos),
            m_retain(retain) {
            }

            const mqttMsg_t& MqttMessage::getMessage() const {
                return m_msg;
            }

            const mqttStr_t& MqttMessage::getTopic() const {
                return m_topic;
            }

            int MqttMessage::getMid() const {
                return m_mid;
            }

            int MqttMessage::getLengthMessage()const {
                return m_payloadlen;
            }

            int MqttMessage::getQOS() const {
                return m_qos;
            }

            bool MqttMessage::getRetain() const {
                return m_retain;
            }

        } // namespace mqtt
    } // namespace conn
} // namespace rsm
