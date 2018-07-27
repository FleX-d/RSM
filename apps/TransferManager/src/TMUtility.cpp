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
 * File:   TMUtility.cpp
 * 
 * Author: Matus Bodorik
 *
 * Created on April 16, 2018, 9:28 AM
 */

#include "TMUtility.h"
#include "FleXdLogger.h"
#include "curl/curl.h"
#include "iTransferClient.h"

namespace flexd {
    namespace rsm {
        namespace conn {
            
            size_t writeCallback(void *ptr, size_t size, size_t nmemb, FILE *stream)
            {
                return fwrite(ptr, size, nmemb, stream);
            }
            
            size_t writeDataToBuf(void *ptr, size_t size, size_t nmemb, void *stream)
            {
                std::string data((const char*) ptr, (size_t) size * nmemb);
                *((std::stringstream*) stream) << data << std::endl;
                return size * nmemb;
            }
            
            size_t readCallback(void *ptr, size_t size, size_t nmemb, FILE * stream)
            {
                return fread(ptr, size, nmemb, stream);
            }

            int progressDownloadFunction(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
            {
                iTransferClient * client = static_cast<iTransferClient *>(ptr);
                if(client->getAbort())
                {
                    return -1;
                }
                
                if (TotalToDownload <= 0.0)
                {
                    return 0;
                }
                int totaldotz = 40;
                double fractiondownloaded = NowDownloaded / TotalToDownload;   
                
                
                if((int)round(fractiondownloaded*100) >= client->getTransferedPerc()*10){
                    client->countTransferedPerc();
                    int dotz = (int)round(fractiondownloaded * totaldotz);
                    int ii = 0;
                    std::string progress = "";
                    for (; ii < dotz; ii++)
                    {
                        progress += "*";
                    }

                    for (; ii < totaldotz; ii++)
                    {
                        progress += "-";
                    }

                    FLEX_LOG_DEBUG("progressDownloadFunction() -> Download [ ", (float)round(fractiondownloaded * 100), " % ", progress, "]");
                }
                return 0;
            }
             
            int progressUploadFunction(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
            {
                iTransferClient * client = static_cast<iTransferClient *>(ptr);
                if(client->getAbort())
                {
                    return -1;
                }
                
                if (TotalToUpload <= 0.0)
                {
                    return 0;
                }
                int totaldotz = 40;
                double fractionUploaded = NowUploaded / TotalToUpload;
                
                if((uint8_t)round(fractionUploaded*100) >= client->getTransferedPerc()*10){
                    client->countTransferedPerc();
                    int dotz = (int)round(fractionUploaded * totaldotz);
                    int ii = 0;
                    std::string progress = "";
                    for (; ii < dotz; ii++)
                    {
                        progress += "*";
                    }

                    for (; ii < totaldotz; ii++)
                    {
                        progress += "-";
                    }

                    FLEX_LOG_DEBUG("progressUploadFunction() -> Upload: [ ", (float)round(fractionUploaded * 100), " % ", progress, "]");
                } 
                
                return 0;
            }

            
        } //namespace conn
    } //namespace rsm
} //namespace rsm
