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

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include <stdint.h>

#define SIRIUS_MPI_CONST const

#define SIRIUS_MPI_INIT 1
#define SIRIUS_MPI_FINALIZE 2

#define SIRIUS_MPI_SEND 4
#define SIRIUS_MPI_ISEND 5

#define SIRIUS_MPI_RECV 16
#define SIRIUS_MPI_IRECV 17

#define SIRIUS_MPI_BARRIER 64
#define SIRIUS_MPI_ALLREDUCE 65
#define SIRIUS_MPI_REDUCE 66
#define SIRIUS_MPI_BCAST 67

#define SIRIUS_MPI_WAIT 128
#define SIRIUS_MPI_WAITALL 129

#define SIRIUS_MPI_COMM_SPLIT 256
#define SIRIUS_MPI_COMM_DISCONNECT 257

#define SIRIUS_MPI_COMM_SELF 1
#define SIRIUS_MPI_COMM_WORLD 0

#define SIRIUS_MPI_INTEGER 1
#define SIRIUS_MPI_DOUBLE 2
#define SIRIUS_MPI_CHAR 4
#define SIRIUS_MPI_LONG 8
#define SIRIUS_MPI_FLOAT 16
#define SIRIUS_MPI_COMPLEX 32

#define SIRIUS_MPI_SUM 1
#define SIRIUS_MPI_MAX 16
#define SIRIUS_MPI_MIN 17

#define SIRIUS_MPI_REQUEST_NULL UINT64_MAX
