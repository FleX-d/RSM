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
 * File:   MosquittoConnection.h
 * 
 * Author: Matus Bodorik
 *
 * Created on November 16, 2017, 9:31 AM
 */

#ifndef MOSQUITTOCONNECTION_H
#define MOSQUITTOCONNECTION_H

#include "mosquittopp.h"
#include "MqttTypes.h"
#include "MqttMessage.h"

namespace rsm {
    namespace conn {
        namespace mqtt {

            class MosquittoConnection : public mosqpp::mosquittopp {
            public:
                explicit MosquittoConnection(const mqttStr_t& id, bool clean_session);
                virtual ~MosquittoConnection();

                MosquittoConnection(const MosquittoConnection&) = delete;
                MosquittoConnection& operator=(const MosquittoConnection&) = delete;

            protected:
                virtual void onMessage(const MqttMessage& msg) = 0;

            private:
                virtual void on_connect(int rc) override;
                virtual void on_disconnect(int rc) override;
                virtual void on_publish(int mid) override;
                virtual void on_message(const struct mosquitto_message * message) override;
                virtual void on_subscribe(int mid, int qos_count, const int * granted_qos) override;
                virtual void on_unsubscribe(int mid) override;
                virtual void on_log(int level, const char* str) override;
                virtual void on_error() override;
            };
        } // namespace mqtt
    } // namespace conn
} // namespace rsm

#endif /* MOSQUITTOCONNECTION_H */

