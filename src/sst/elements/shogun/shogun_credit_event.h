// Copyright 2009-2025 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2025, NTESS
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// of the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef _H_SHOGUN_INC_CREDIT_EVENT
#define _H_SHOGUN_INC_CREDIT_EVENT

#include <sst/core/event.h>

namespace SST {
namespace Shogun {

    class ShogunCreditEvent : public SST::Event {

    public:
        ShogunCreditEvent()
            : sourcePort(0)
        {
        }
        ShogunCreditEvent(const int source)
            : sourcePort(source)
        {
        }
        ~ShogunCreditEvent() {}

        int getSrc() const
        {
            return sourcePort;
        }

        void serialize_order(SST::Core::Serialization::serializer& ser) override
        {
            Event::serialize_order(ser);

            SST_SER(sourcePort);
        }

        ImplementSerializable(SST::Shogun::ShogunCreditEvent);

    protected:
        int sourcePort;
    };

}
}

#endif
