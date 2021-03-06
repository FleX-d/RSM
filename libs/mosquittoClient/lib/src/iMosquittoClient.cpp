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
#include "FleXdLogger.h"

namespace rsm
{
    namespace conn
    {
        namespace mqtt
        {

            iMosquittoClient::iMosquittoClient(const mqttStr_t& id, const MosquittoSetting& settings)
            : MosquittoConnection(id.c_str(), settings.getCleanSession())
            {
                FLEX_LOG_TRACE("iMosquittoClient::iMosquittoClient -> Start connect: ", id);
                int ret = connect(settings.getIpAddress().c_str(), settings.getPort(), settings.getKeepAlive());
                if(ret == MOSQ_ERR_SUCCESS)
                {
                    FLEX_LOG_INFO("iMosquittoClient::connect() -> Client: ", id ," connect Success! Port: ", settings.getPort(), ", IP Address ", settings.getIpAddress());
                    m_connected = true;
                } else {
                    FLEX_LOG_ERROR("iMosquittoClient::connect() -> Client: ", id ," connect Fail! Port: ", settings.getPort(), ", IP Address ", settings.getIpAddress());
                    m_connected = false;
                    //reconnect_async();
                }
            }

            iMosquittoClient::~iMosquittoClient()
            {   
                disconnect();
                FLEX_LOG_TRACE("iMosquittoClient::~iMosquittoClient() -> Destroyed");
            }

            int iMosquittoClient::publishMessage(const MqttMessage& message)
            {  
                int ret = publish(NULL , message.getTopic().c_str(), message.getMessage().size(), message.getMessage().c_str(), message.getQOS(), message.getRetain());
                if (ret == MOSQ_ERR_SUCCESS)
                {
                    FLEX_LOG_DEBUG("iMosquittoClient::publishMessage() -> Publish message Success: ", message.getMessage().c_str() , "  length ", message.getMessage().length(), " topic ",  message.getTopic().c_str());
                    return Success;
                }
                FLEX_LOG_ERROR("iMosquittoClient::publishMessage() -> Error: Publish message Fail! ", message.getMessage().c_str() , "  length ", message.getMessage().length(), " topic ",  message.getTopic().c_str());
                return Error;
            }

            int iMosquittoClient::subscribeTopic(const mqttStr_t& topic, int qos)
            {
                int ret = subscribe(NULL, topic.c_str(), qos);
                if (ret == MOSQ_ERR_SUCCESS && m_connected)
                {
                    FLEX_LOG_INFO("iMosquittoClient::subscribeTopic() -> Subscribe topic Success, topic: ", topic);
                    return Success;
                }
                FLEX_LOG_ERROR("iMosquittoClient::subscribeTopic() -> Error: Subscribe topic Fail, topic: ", topic);
                return Error;
            }

            int iMosquittoClient::unsubscribeTopic(const mqttStr_t& topic)
            {
                int ret = unsubscribe(NULL, topic.c_str());
                if (ret == MOSQ_ERR_SUCCESS)
                {
                    FLEX_LOG_INFO("iMosquittoClient::unsubscribeTopic() -> Unsubscribe topic Success, topic: ", topic);
                    return Success;
                }
                FLEX_LOG_ERROR("iMosquittoClient::unsubscribeTopic() -> Error: Unsubscribe topic Fail, topic: ", topic);
                return Error;
            }

            int iMosquittoClient::switchTopic(const mqttStr_t& leaveTopic, const mqttStr_t& subTopic, int qos)
            {
                int ret1 = unsubscribe(NULL, leaveTopic.c_str());
                int ret2 = subscribe(NULL, subTopic.c_str(), qos);
                if (ret1 == MOSQ_ERR_SUCCESS && ret2 == MOSQ_ERR_SUCCESS)
                {
                    FLEX_LOG_INFO("iMosquittoClient::switchTopic() -> Change topic Success, leave topic: ", leaveTopic, " ,subscribe topic: ", subTopic);
                    return Success;
                }
                FLEX_LOG_ERROR("iMosquittoClient::switchTopic() -> Change topic Fail, leave topic: ", leaveTopic, " ,subscribe topic: ", subTopic);
                return Error;
            }
            
            const mqttStr_t& iMosquittoClient::getVersion() const
            {
                return m_version;
            }

        } // namespace mqtt
    } // namespace conn
} // namespace rsm
