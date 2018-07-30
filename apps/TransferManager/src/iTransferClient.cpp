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
 * File:   iTransferClient.cpp
 * Author: Matus Bodorik
 * 
 * Created on December 19, 2017, 10:27 AM
 */

#include "iTransferClient.h"
#include <FleXdLogger.h>
#include <curl/curl.h>
#include <unistd.h>
#include <functional>

namespace flexd {
    namespace rsm {
        namespace conn {

            iTransferClient::iTransferClient(flexd::icl::ipc::FleXdEpoll& poller)
            : m_poller(poller),
              m_transferSize(0),
              m_elapsedTime(0),
              m_abort(false),
              m_event(poller, std::bind(&iTransferClient::onEvent, this, std::placeholders::_1)),
              m_transferedPerc(0),
              m_thread(nullptr)
            {
                this->m_curl = curl_easy_init();
            }

            iTransferClient::~iTransferClient()
            {
                curl_easy_cleanup(m_curl);
                if(m_thread && m_thread->joinable())
                {
                    m_thread->join();
                }
            }
            
            bool iTransferClient::getAbort()
            {
                return m_abort.load();
            }
            
            void iTransferClient::onEvent(eventfd_t value)
            {
                FLEX_LOG_DEBUG("iTransferClient::onEvent() -> value: ", value);
                if(value == TransferReturn::Success)
                {
                    FLEX_LOG_INFO("iTransferClient::doTransfer() -> Transfer Success");
                    m_status = TransferStatus::Finished;
                } else if(value == TransferReturn::Abort)
                {
                    FLEX_LOG_INFO("iTransferClient::doTransfer() -> Transfer Aborted");
                    m_status = TransferStatus::Aborted;
                } else 
                {
                    FLEX_LOG_WARN("iTransferClient::doTransfer() -> Transfer Fail");
                    m_status = TransferStatus::Failed;
                }
                if(m_thread && m_thread->joinable())
                {
                    m_thread->join();
                    m_thread.release();
                    FLEX_LOG_TRACE("iTransferClient::onEvent() -> Join Success.");
                }
            }
            
            void iTransferClient::countTransferedPerc()
            {
                m_transferedPerc += 1;
            }
            
            uint8_t iTransferClient::getTransferedPerc()
            {
                return m_transferedPerc;
            }
        } //namespace conn
    } //namespace rsm
} //namespace flexd
