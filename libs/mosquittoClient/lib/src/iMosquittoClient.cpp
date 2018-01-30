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
 * File:   iMosquittoClient.cpp
 * 
 * Author: Matus Bodorik
 * 
 * Created on November 10, 2017, 10:07 AM
 */

#include "iMosquittoClient.h"
#include "MosquittoSetting.h"
#include "FlexLogger.h"

namespace rsm
{
    namespace conn
    {
        namespace mqtt
        {

            iMosquittoClient::iMosquittoClient(const mqttStr_t& id, const MosquittoSetting& settings)
            : MosquittoConnection(id.c_str(), settings.getCleanSession())
            {
                FLEX_LOG_DEBUG("iMosquittoClient::iMosquittoClient connect -> ", id, connect(settings.getIpAddress().c_str(), settings.getPort(), settings.getKeepAlive()));
            }

            iMosquittoClient::~iMosquittoClient()
            {
                FLEX_LOG_DEBUG("iMosquittoClient::~iMosquittoClient");
                disconnect();
            }

            int iMosquittoClient::publishMessage(const MqttMessage& message)
            {
                FLEX_LOG_DEBUG("Publishing message! ", message.getMessage().c_str() , "  length ", message.getMessage().length(), " topic ",  message.getTopic().c_str());
                int ret = publish(NULL , message.getTopic().c_str(), message.getMessage().size(), message.getMessage().c_str(), message.getQOS(), message.getRetain());
                if (ret == MOSQ_ERR_SUCCESS)
                {
                    return Success;
                }
                FLEX_LOG_ERROR("ERROR - cannot publish message!", message.getMessage().c_str() , "  length ", message.getMessage().length(), " topic ",  message.getTopic().c_str());
                return Error;
            }

            int iMosquittoClient::subscribeTopic(const mqttStr_t& topic, int qos)
            {
                FLEX_LOG_DEBUG("Subscribing topic! ", topic);
                int ret = subscribe(NULL, topic.c_str(), qos);
                if (ret == MOSQ_ERR_SUCCESS)
                {
                    return Success;
                }
                FLEX_LOG_ERROR("ERROR - cannot subscribe topic!", topic);
                return Error;
            }

            int iMosquittoClient::unsubscribeTopic(const mqttStr_t& topic)
            {
                FLEX_LOG_DEBUG("Unsubscribing topic! ", topic);
                int ret = unsubscribe(NULL, topic.c_str());
                if (ret == MOSQ_ERR_SUCCESS)
                {
                    return Success;
                }
                FLEX_LOG_ERROR("ERROR - cannot unsubscribe topic!", topic);
                return Error;
            }

            int iMosquittoClient::switchTopic(const mqttStr_t& leaveTopic, const mqttStr_t& subTopic, int qos)
            {
                FLEX_LOG_DEBUG("Changing topic! ");
                int ret1 = unsubscribe(NULL, leaveTopic.c_str());
                int ret2 = subscribe(NULL, subTopic.c_str(), qos);
                if (ret1 == MOSQ_ERR_SUCCESS && ret2 == MOSQ_ERR_SUCCESS)
                {
                    return Success;
                }
                FLEX_LOG_ERROR("ERROR - cannot change topic!");
                return Error;

            }
            
            const mqttStr_t& iMosquittoClient::getVersion() const
            {
                return m_version;
            }

        } // namespace mqtt
    } // namespace conn
} // namespace rsm
