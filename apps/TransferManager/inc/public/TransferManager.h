/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransferManager.h
 * Author: Matus Bodorik
 *
 * Created on December 21, 2017, 9:20 AM
 */

#ifndef TRANSFERMANAGER_H
#define TRANSFERMANAGER_H

#include "iTransferRequest.h"
#include "iTransferClient.h"
#include "TMFactory.h"
#include <queue>
#include <vector>
#include <memory>

namespace flexd {
    namespace rsm {
        namespace conn {

            class TransferManager {
            public:
                TransferManager(flexd::icl::ipc::FleXdEpoll& poller);
                TransferManager(const TransferManager& orig) = delete;
                virtual ~TransferManager();

                bool addTransfer(const iTransferRequest& request);
                bool runTransfer();
                bool abortTransfer();
                bool getTransferInfo();

            private:
                std::queue<std::shared_ptr<iTransferClient>> m_list;
                flexd::icl::ipc::FleXdEpoll& m_poller;
            };
        } //namespace conn
    } //namespace rsm
} //namespace flexd

#endif /* TRANSFERMANAGER_H */

