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

#ifndef _H_VANADIS_SYSCALL_GETTIME64
#define _H_VANADIS_SYSCALL_GETTIME64

#include "os/voscallev.h"

namespace SST {
namespace Vanadis {

class VanadisSyscallGetTime64Event : public VanadisSyscallEvent {
public:
    VanadisSyscallGetTime64Event() : VanadisSyscallEvent() {}
    VanadisSyscallGetTime64Event(uint32_t core, uint32_t thr, VanadisOSBitType bittype, int64_t clk_id, uint64_t time_addr)
        : VanadisSyscallEvent(core, thr, bittype), clock_id(clk_id), timestruct_addr(time_addr) {}

    VanadisSyscallOp getOperation() override { return SYSCALL_OP_GETTIME64; }

    int64_t getClockType() const { return clock_id; }
    uint64_t getTimeStructAddress() const { return timestruct_addr; }

private:
    void serialize_order(SST::Core::Serialization::serializer& ser) override {
        VanadisSyscallEvent::serialize_order(ser);
        SST_SER(clock_id);
        SST_SER(timestruct_addr);
    }
    ImplementSerializable(SST::Vanadis::VanadisSyscallGetTime64Event);

    int64_t clock_id;
    uint64_t timestruct_addr;
};

} // namespace Vanadis
} // namespace SST

#endif
