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

#ifndef _H_VANADIS_UTIL_DATA_COPY
#define _H_VANADIS_UTIL_DATA_COPY

#include <vector>

namespace SST {
namespace Vanadis {

template <typename T>
void
vanadis_vec_copy_in(std::vector<uint8_t>& vec, T value) {
    uint8_t* value_ptr = (uint8_t*)&value;

    for (size_t i = 0; i < sizeof(T); ++i) {
        vec.push_back(value_ptr[i]);
    }
};

} // namespace Vanadis
} // namespace SST

#endif
