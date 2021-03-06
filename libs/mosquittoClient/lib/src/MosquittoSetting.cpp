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
 * File:   MosquittoSetting.cpp
 * 
 * Author: Matus Bodorik
 * 
 * Created on November 20, 2017, 10:25 AM
 */

#include "MosquittoSetting.h"

namespace rsm {
    namespace conn {
        namespace mqtt {

            MosquittoSetting::MosquittoSetting(const mqttStr_t& ipAddress, int port, int qos, int keepAlive, bool cleanSesion) 
            : m_ipAddress(ipAddress),
              m_port(port),
              m_qos(qos),
              m_keepAlive(keepAlive),
              m_cleanSession(cleanSesion)
            {
            }

            void MosquittoSetting::setIpAddress(const mqttStr_t& ipAddress) {
                this->m_ipAddress = ipAddress;
            }

            void MosquittoSetting::setPort(int port) {
                this->m_port = port;
            }

            void MosquittoSetting::setQOS(int qos) {
                this->m_qos = qos;
            }

            void MosquittoSetting::setCleanSession(bool cleanSession)
            {
                this->m_cleanSession = cleanSession;
            }

            void MosquittoSetting::setKeepAlive(int keepAlive) {
                this->m_keepAlive = keepAlive;
            }

            const mqttStr_t& MosquittoSetting::getIpAddress() const {
                return m_ipAddress;
            }

            int MosquittoSetting::getPort() const {
                return m_port;
            }

            int MosquittoSetting::getQOS() const {
                return m_qos;
            }

            bool MosquittoSetting::getCleanSession() const
            {
                return m_cleanSession;
            }

            int MosquittoSetting::getKeepAlive()const {
                return m_keepAlive;
            }

        } // namespace mqtt
    } // namespace conn
} // namespace rsm
