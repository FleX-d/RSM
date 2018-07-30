/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransferManager.cpp
 * Author: flexd
 * 
 * Created on December 21, 2017, 9:20 AM
 */

#include "TransferManager.h"
#include "TMFactory.h"
#include <memory>
#include <FleXdLogger.h>

namespace flexd {
    namespace rsm {
        namespace conn {

            TransferManager::TransferManager(flexd::icl::ipc::FleXdEpoll& poller)
            : m_poller(poller)
            {
                FLEX_LOG_INFO("TransferManager -> Start");
            }

            TransferManager::~TransferManager()
            {
                FLEX_LOG_TRACE("TransferManager::~TransferManager() -> Destroyed");
            }

            bool TransferManager::addTransfer(const iTransferRequest& request)
            {
                m_list.push(flexd::rsm::conn::TMFactory::createInstance(request, m_poller));
                FLEX_LOG_TRACE("TransferManager::addTransfer() -> Transfer add Success.");
                return true;
            }

            bool TransferManager::runTransfer()
            {
                if (!m_list.empty())
                {
                    FLEX_LOG_TRACE("TransferManager::runTransfer() -> Transfer start run.");
                    m_list.back()->doTransfer();                
                    return true;
                } else {
                    FLEX_LOG_WARN("TransferManager::runTransfer() -> Transfer list empty.");
                    return false;
                }
            }
            
            bool TransferManager::abortTransfer()
            {
                if (!m_list.empty())
                {
                    FLEX_LOG_TRACE("TransferManager::abortTransfer() -> Abort transfer start!");
                    m_list.back()->abortTransfer();
                    return true;
                } else {
                    FLEX_LOG_WARN("TransferManager::abortTransfer() -> Transfer list empty.");
                    return false;
                }
            }
            
            bool TransferManager::getTransferInfo()
            {
                if (!m_list.empty())
                {
                    FLEX_LOG_TRACE("TransferManager::getTransferInfo() -> Transfer Info");
                    m_list.back()->getTransferStatus();
                    return true;
                } else {
                    FLEX_LOG_WARN("TransferManager::getTransferInfo() -> Transfer list empty.");
                    return false;
                }
            }            
        } //namespace conn
    } //namespace rsm
} //namespace flexd