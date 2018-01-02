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
 * File:   MosquittoConnection.cpp
 * 
 * Author: Matus Bodorik
 * 
 * Created on November 16, 2017, 9:31 AM
 */

#include "MosquittoConnection.h"
#include "FlexLogger.h"

namespace rsm {
    namespace conn {
        namespace mqtt {

            MosquittoConnection::MosquittoConnection(const mqttStr_t& id, bool clean_session)
            : mosquittopp(id.c_str(), clean_session) {
                mosqpp::lib_init();
                loop_start();
            }

            MosquittoConnection::~MosquittoConnection() {
                mosqpp::lib_cleanup();
                loop_stop();
            }

            void MosquittoConnection::on_connect(int rc) {
                FLEX_LOG_DEBUG("Connected with code: ", rc);
            }

            void MosquittoConnection::on_disconnect(int rc) {
                FLEX_LOG_DEBUG("Disconnected");
            }

            void MosquittoConnection::on_publish(int mid) {
                FLEX_LOG_DEBUG("Publishing: ", mid);
            }

            void MosquittoConnection::on_message(const struct mosquitto_message * message) {
                if (message) {
                    FLEX_LOG_INFO("Message delivery success! ", (const char*) message->payload);
                    //onMessage();
                } else {
                    FLEX_LOG_ERROR("Message Lost!!");
                }

            }

            void MosquittoConnection::on_subscribe(int mid, int qos_count, const int * granted_qos) {
                FLEX_LOG_INFO("Subscription succeeded! ", mid);
            }

            void MosquittoConnection::on_unsubscribe(int mid) {
                FLEX_LOG_DEBUG("Unsubscribing! ", mid);
            }

            void MosquittoConnection::on_log(int level, const char* str) {
                FLEX_LOG_DEBUG(str);
            }

            void MosquittoConnection::on_error() {
                FLEX_LOG_ERROR("Error - something is wrong!!!");
            }
        } // namespace mqtt
    } // namespace conn
} // namespace rsm
