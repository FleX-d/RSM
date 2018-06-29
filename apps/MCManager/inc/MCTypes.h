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
 * File:   MCTypes.h
 * Author: Matus Bodorik
 *
 * Created on January 22, 2018, 1:15 PM
 */



#ifndef MCTYPES_H
#define MCTYPES_H

#include <stdint.h>

namespace rsm {
    namespace msq {
        namespace com {

            namespace OperationRequestType {
                enum Enum {
                    Subscribe = 0x00,
                    Unsubscribe =0x01
                };
            }

            namespace RequestAckType {
                enum Enum {
                    Success = 0x01,
                    Fail = 0x00,
                    ClientExist = 0x02,
                    ClientNotExist = 0x03,
                    UndefinedError = 0xFF
                };
            }

            namespace DirectionType {
                enum Enum {
                    IN = 0x00,
                    OUT = 0x01,
                    BOTH = 0x02
                };
            }

            class MCPeer {
            public:
                explicit MCPeer(uint32_t id) : m_ID(id) {}
                virtual ~MCPeer() = default;

                void setID(uint32_t id)  { m_ID = id; }
                uint32_t getID() const { return m_ID; }

            protected:
                uint32_t m_ID;
            };

        }
    }
}
#endif /* MCTYPES_H */

