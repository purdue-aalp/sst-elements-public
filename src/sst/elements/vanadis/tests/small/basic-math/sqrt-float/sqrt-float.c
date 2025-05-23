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

#include <stdio.h>

float squareRoot(float n) {
	float i = 0;
	float precision = 0.00001;

	for(i = 1; i*i <=n; ++i);
  	for(--i; i*i < n; i += precision);

   	return i;
}

int main( int argc, char* argv[] ) {
   	int n = 24;

	for( int i = 1; i < n; ++i ) {
		printf("Square root of %d = %30.12f\n", i,
			squareRoot( (float) i));
		fflush(stdout);
	}

	return 0;
}
