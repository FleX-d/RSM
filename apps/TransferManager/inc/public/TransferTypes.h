/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransferTypes.h
 * Author: flexd
 *
 * Created on December 19, 2017, 3:29 PM
 */

#ifndef TRANSFERTYPES_H
#define TRANSFERTYPES_H
namespace flexd {
    namespace rsm {
        namespace conn {

            namespace TransferType{
                enum Enum {
                    HTTPUpload = 0,
                    HTTPDownload,
                    FTPUpload,
                    FTPDownload
                };
            }
            
            namespace TransferStatus{
                enum Enum {
                    Pending = 0,
                    Idle,
                    Queued,
                    Running,
                    Finished,
                    Aborted,
                    Failed,
                    Paused,
                    Frozen,
                    /*...*/
                    Undefined = 0xFF
                };
            }
             namespace TransferReturn{   
                enum Enum {
                    Fail = 1,
                    Success, 
                    UndefinedError,
                    Abort
                };
            }
        }
    }
}
#endif /* TRANSFERTYPES_H */

