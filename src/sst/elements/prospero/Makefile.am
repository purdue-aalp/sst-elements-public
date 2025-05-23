AM_CPPFLAGS += \
	$(MPI_CPPFLAGS) \
	-DPROSPERO_TOOL_DIR="$(libexecdir)"

compdir = $(pkglibdir)
comp_LTLIBRARIES = libprospero.la

libprospero_la_SOURCES = \
        proscpu.h \
        proscpu.cc \
	prosreader.h \
	prostextreader.h \
	prostextreader.cc \
	prosbinaryreader.h \
	prosbinaryreader.cc \
	prosmemmgr.h \
	prosmemmgr.cc

EXTRA_DIST = \
        tests/array/trace-binary.py \
        tests/array/trace-compressed.py \
        tests/array/trace-text.py \
        tests/array/trace-common.py \
        tests/array/array.c \
        tests/array/Makefile \
        tests/refFiles/test_prospero_with_timingdram.out \
        tests/refFiles/test_prospero_with_timingdram_binary.out \
        tests/refFiles/test_prospero_with_timingdram_compressed.out \
        tests/refFiles/test_prospero_with_timingdram_text.out \
        tests/refFiles/test_prospero_wo_timingdram.out \
        tests/refFiles/test_prospero_wo_timingdram_binary.out \
        tests/refFiles/test_prospero_wo_timingdram_compressed.out \
        tests/refFiles/test_prospero_wo_timingdram_text.out \
        tests/testsuite_default_prospero.py \
        tracetool/Makefile \
        tracetool/Makefile.osx \
        tracetool/sstmemtrace.cc \
        tracetool/api/Makefile \
        tracetool/api/Makefile.osx \
        tracetool/api/prospero.c \
        tracetool/api/prospero.h

libprospero_la_LDFLAGS = -module -avoid-version
libprospero_la_LIBADD = $(SHM_LIB)

install-exec-local:
	$(SST_REGISTER_TOOL) SST_ELEMENT_SOURCE     prospero=$(abs_srcdir)
	$(SST_REGISTER_TOOL) SST_ELEMENT_TESTS      prospero=$(abs_srcdir)/tests

if USE_LIBZ
libprospero_la_LIBADD += -lz

libprospero_la_SOURCES += \
	prosbingzreader.h \
	prosbingzreader.cc
endif # USE_LIBZ

if HAVE_PINTOOL

TARGET = intel64
BIONIC_ARCH = x86_64
XED_ARCH = intel64

bin_PROGRAMS = sst-prospero-trace
sst_prospero_trace_SOURCES = runprosperotrace.cc
AM_CPPFLAGS += $(PINTOOL_CPPFLAGS)

if SST_COMPILE_OSX

all-local: tracetool/sstmemtrace.cc
	$(CXX) -O3 -shared \
	$(AM_CPPFLAGS) \
	$(CPPFLAGS) \
	$(LIBZ_CPPFLAGS) \
	-DBIGARRAY_MULTIPLIER=1 \
	-DTARGET_IA32E -DHOST_IA32E -fPIC -DTARGET_MAC \
	-I$(PINTOOL_DIR)/source/include/pin \
	-I$(PINTOOL_DIR)/ \
	-I$(PINTOOL_DIR)/extras/components/include \
	-I$(PINTOOL_DIR)/source/include/pin/gen/ \
	-I$(PINTOOL_DIR)/extras/xed-$(XED_ARCH)/include \
	-I$(top_srcdir)/sst \
	-fomit-frame-pointer -fno-stack-protector \
	-Wl,-exported_symbols_list \
	-Wl,$(PINTOOL_DIR)/source/include/pin/pintool.exp \
	-L$(PINTOOL_DIR)/$(TARGET)/lib \
	-L$(PINTOOL_DIR)/$(TARGET)/lib-ext \
	-L$(PINTOOL_DIR)/extras/xed-$(XED_ARCH)/lib \
	-o prosperotrace.dylib $(top_srcdir)/src/sst/elements/prospero/tracetool/sstmemtrace.cc \
	-stdlib=libstdc++ \
	-lpin -lxed -lpindwarf -lpthread $(LIBZ_LDFLAGS) $(LIBZ_LIB)

install-exec-hook: prosperotrace.dylib
	cp prosperotrace.dylib $(libexecdir)/prosperotrace.dylib

else # !SST_COMPILE_OSX

all-local: prosperotrace.so

if HAVE_PIN325
prosperotrace.so : prosperotrace.o
	$(CXX) -shared -Wl,--hash-style=sysv \
	    $(PINTOOL_DIR)/$(TARGET)/runtime/pincrt/crtbeginS.o \
	    -Wl,-Bsymbolic -Wl,--version-script=$(PINTOOL_DIR)/source/include/pin/pintool.ver \
	    -o prosperotrace.so prosperotrace.o \
	    -L$(PINTOOL_DIR)/$(TARGET)/runtime/pincrt \
	    -L$(PINTOOL_DIR)/$(TARGET)/lib \
	    -L$(PINTOOL_DIR)/$(TARGET)/lib-ext \
	    -L$(PINTOOL_DIR)/extras/xed-$(XED_ARCH)/lib -lpin -lxed \
	    $(PINTOOL_DIR)/$(TARGET)/runtime/pincrt/crtendS.o \
	    -lpindwarf -ldl-dynamic -nostdlib -lc++ -lc++abi -lm-dynamic -lc-dynamic -lunwind-dynamic

prosperotrace.o : $(top_srcdir)/src/sst/elements/prospero/tracetool/sstmemtrace.cc
	$(CXX) \
	    $(PIN_CPPFLAGS) $(PIN_CPPFLAGS_COMPILER) \
	    $(AM_CPPFLAGS) $(CPPFLAGS) \
	    -I$(PINTOOL_DIR)/source/include/pin \
	    -I$(PINTOOL_DIR)/source/include/pin/gen \
	    -isystem $(PINTOOL_DIR)/extras/cxx/include \
	    -isystem $(PINTOOL_DIR)/extras/crt/include \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/arch-$(BIONIC_ARCH) \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/kernel/uapi \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/kernel/uapi/asm-x86 \
	    -I$(PINTOOL_DIR)/extras/components/include \
	    -I$(PINTOOL_DIR)/extras/xed-$(XED_ARCH)/include/xed \
	    -I$(PINTOOL_DIR)/source/tools/Utils \
	    -I$(PINTOOL_DIR)/source/tools/InstLib \
	    -O3 -o prosperotrace.o -c $(top_srcdir)/src/sst/elements/prospero/tracetool/sstmemtrace.cc

else # !HAVE_PIN325

if HAVE_PIN324
prosperotrace.so : prosperotrace.o
	$(CXX) -shared -Wl,--hash-style=sysv \
	    $(PINTOOL_DIR)/$(TARGET)/runtime/pincrt/crtbeginS.o \
	    -Wl,-Bsymbolic -Wl,--version-script=$(PINTOOL_DIR)/source/include/pin/pintool.ver \
	    -o prosperotrace.so prosperotrace.o \
	    -L$(PINTOOL_DIR)/$(TARGET)/runtime/pincrt \
	    -L$(PINTOOL_DIR)/$(TARGET)/lib \
	    -L$(PINTOOL_DIR)/$(TARGET)/lib-ext \
	    -L$(PINTOOL_DIR)/extras/xed-$(XED_ARCH)/lib -lpin -lxed \
	    $(PINTOOL_DIR)/$(TARGET)/runtime/pincrt/crtendS.o \
	    -lpin3dwarf -ldl-dynamic -nostdlib -lc++ -lc++abi -lm-dynamic -lc-dynamic -lunwind-dynamic

prosperotrace.o : $(top_srcdir)/src/sst/elements/prospero/tracetool/sstmemtrace.cc
	$(CXX) \
	    $(PIN_CPPFLAGS) $(PIN_CPPFLAGS_COMPILER) \
	    $(AM_CPPFLAGS) $(CPPFLAGS) \
	    -I$(PINTOOL_DIR)/source/include/pin \
	    -I$(PINTOOL_DIR)/source/include/pin/gen \
	    -isystem $(PINTOOL_DIR)/extras/cxx/include \
	    -isystem $(PINTOOL_DIR)/extras/crt/include \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/arch-$(BIONIC_ARCH) \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/kernel/uapi \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/kernel/uapi/asm-x86 \
	    -I$(PINTOOL_DIR)/extras/components/include \
	    -I$(PINTOOL_DIR)/extras/xed-$(XED_ARCH)/include/xed \
	    -I$(PINTOOL_DIR)/source/tools/Utils \
	    -I$(PINTOOL_DIR)/source/tools/InstLib \
	    -O3 -o prosperotrace.o -c $(top_srcdir)/src/sst/elements/prospero/tracetool/sstmemtrace.cc
else # !HAVE_PIN325 and !HAVE_PIN324
prosperotrace.so : prosperotrace.o
	$(CXX) -shared -Wl,--hash-style=sysv \
	    $(PINTOOL_DIR)/$(TARGET)/runtime/pincrt/crtbeginS.o \
	    -Wl,-Bsymbolic -Wl,--version-script=$(PINTOOL_DIR)/source/include/pin/pintool.ver \
	    -o prosperotrace.so prosperotrace.o \
	    -L$(PINTOOL_DIR)/$(TARGET)/runtime/pincrt \
	    -L$(PINTOOL_DIR)/$(TARGET)/lib \
	    -L$(PINTOOL_DIR)/$(TARGET)/lib-ext \
	    -L$(PINTOOL_DIR)/extras/xed-$(XED_ARCH)/lib -lpin -lxed \
	    $(PINTOOL_DIR)/$(TARGET)/runtime/pincrt/crtendS.o \
	    -lpin3dwarf -ldl-dynamic -nostdlib -lstlport-dynamic -lm-dynamic -lc-dynamic -lunwind-dynamic

prosperotrace.o : $(top_srcdir)/src/sst/elements/prospero/tracetool/sstmemtrace.cc
	$(CXX) \
	    $(PIN_CPPFLAGS) $(PIN_CPPFLAGS_COMPILER) -DHAVE_PIN3=1 \
	    $(AM_CPPFLAGS) \
	    $(CPPFLAGS) \
	    -I$(PINTOOL_DIR)/source/include/pin \
	    -I$(PINTOOL_DIR)/source/include/pin/gen \
	    -isystem $(PINTOOL_DIR)/extras/stlport/include \
	    -isystem $(PINTOOL_DIR)/extras/libstdc++/include \
	    -isystem $(PINTOOL_DIR)/extras/crt/include \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/arch-$(BIONIC_ARCH) \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/kernel/uapi \
	    -isystem $(PINTOOL_DIR)/extras/crt/include/kernel/uapi/asm-x86 \
	    -I$(PINTOOL_DIR)/extras/components/include\
	    -I$(PINTOOL_DIR)/extras/xed-$(XED_ARCH)/include/xed \
	    -I$(PINTOOL_DIR)/source/tools/Utils \
	    -I$(PINTOOL_DIR)/source/tools/InstLib \
	    -O3 -o prosperotrace.o -c $(top_srcdir)/src/sst/elements/prospero/tracetool/sstmemtrace.cc
endif
endif

install-exec-hook: prosperotrace.so
	cp prosperotrace.so $(libexecdir)/prosperotrace.so

endif
endif
