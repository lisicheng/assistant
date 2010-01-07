#   Makefile for Symbian Project
#
#   Copyright 2009, Harry Li <harry.li AT pagefreedom.org>
#   Copyright 2009, Yuan Ye <yuanyelele@gmail.com>
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

GCCPATH = /home/symbian/csl-gcc

SYSINCPATH = $(EPOCROOT)/epoc32/include
VARIANT = $(SYSINCPATH)/variant
OS_HRH = $(VARIANT)/symbian_os_v9.1.hrh
CERT = ~/cert_dev.cer
KEY = ~/cert_dev.key
LANG = zh_CN.UTF-8

include config.mk

.PHONY: check clean resource bin build pack install

check:
	@echo 'EPOCROOT:' $(EPOCROOT)
	@echo ' GCCPATH:' $(GCCPATH)
	@echo '    PATH:' $(PATH)
	@echo 'CXXFLAGS:' $(CXXFLAGS)
	@echo '==============================================================='

CXX = arm-none-symbianelf-g++ # GNU project C and C++ compiler
LD  = arm-none-symbianelf-ld  # The GNU linker

ARMV5URELPATH = $(EPOCROOT)/epoc32/release/armv5/urel
ARMV5LIBPATH = $(EPOCROOT)/epoc32/release/armv5/lib

CXXFLAGS += -fexceptions -march=armv5t -mapcs -pipe -nostdinc -c -msoft-float \
	-include $(SYSINCPATH)/gcce/gcce.h \
	-D__SYMBIAN32__ -D__EPOC32__ -D__SERIES60_30__ -D__SERIES60_3X__ \
	-D__GCCE__ -D__MARM__ -D__MARM_ARMV5__ -D__EABI__ \
	-D__SUPPORT_CPP_EXCEPTIONS__ -DNDEBUG -D_UNICODE \
	-D__$(shell echo $(TARGETTYPE) | tr a-z A-Z)__ \
	-Wall -Wno-unknown-pragmas \
	-D__PRODUCT_INCLUDE__="$(OS_HRH)" -I$(VARIANT) \
	-Iinc -I$(SYSINCPATH) \
	-I$(GCCPATH)/lib/gcc/arm-none-symbianelf/3.4.3/include \
	-Wno-ctor-dtor-privacy -x c++

ifeq ($(TARGETTYPE), exe)
ENTRY=_E32Startup
TYPELIB = $(ARMV5URELPATH)/eexe.lib
else
ENTRY=_E32Dll
TYPELIB = $(ARMV5URELPATH)/edll.lib $(ARMV5URELPATH)/edllstub.lib
endif
LDFLAGS = \
	--entry $(ENTRY) -soname $(PROJECT){000a0000}[$(UID3)].$(TARGETTYPE) \
	--library-path $(GCCPATH)/arm-none-symbianelf/lib --library supc++ \
	--library-path $(GCCPATH)/lib/gcc/arm-none-symbianelf/3.4.3 --library gcc \
	--output dist/$(PROJECT).elf --undefined $(ENTRY) \
	--no-undefined --default-symver -nostdlib -shared \
	-Tdata 0x400000 -Ttext 0x8000 --target1-abs \
	$(TYPELIB) $(ARMV5URELPATH)/usrt2_2.lib \
	$(ARMV5LIBPATH)/dfpaeabi.dso $(ARMV5LIBPATH)/dfprvct2_2.dso \
	$(ARMV5LIBPATH)/drtaeabi.dso $(ARMV5LIBPATH)/drtrvct2_2.dso \
	$(ARMV5LIBPATH)/scppnwdl.dso

OBJTARGET = $(patsubst %.cpp,src/%.o,$(SRCFILES))
RSSTARGET = $(patsubst %.rss,dist/%_$(UID3).rsc,$(RSSFILES))
BINTARGET = dist/$(PROJECT)_$(UID3).$(TARGETTYPE)
SISX = sis/$(PROJECT).sisx

clean: check
	rm -rf dist/*
	rm -f $(OBJTARGET)
	rm -f $(patsubst %.cpp,src/%.d,$(SRCFILES))
	rm -f $(patsubst %.rss,rss/%.d,$(RSSFILES))
	rm -f inc/*.rsg

include $(patsubst %.cpp,src/%.d,$(SRCFILES))
include $(patsubst %.rss,rss/%.d,$(RSSFILES))

src/%.d: src/%.cpp
	$(CXX) -M -MG -MP -MT $@ -MT src/$*.o $(CXXFLAGS) $< > $@

rss/%.d: rss/%.rss
	$(CXX) -M -MG -MP -MT $@ -MT dist/$*_$(UID3).rsc $(CXXFLAGS) $< > $@

dist/$(PROJECT).elf: $(OBJTARGET)
	$(LD) $^ $(LDFLAGS) \
		$(addprefix $(ARMV5URELPATH)/,$(STATICLIBRARY)) \
		$(patsubst %.lib,$(ARMV5LIBPATH)/%.dso,$(LIBRARY))

ifeq ($(TARGETTYPE), dll)
DSOTARGET = dist/$(PROJECT){000a0000}.dso
DSO = --dso $(DSOTARGET)
endif
$(BINTARGET) $(DSOTARGET): dist/$(PROJECT).elf
	elf2e32 --elfinput $< --output $@ --targettype $(TARGETTYPE) \
		--linkas $(PROJECT){000a0000}[$(UID3)].$(TARGETTYPE) \
		--uid1 0x$(UID1) --uid2 0x$(UID2) --uid3 0x$(UID3) \
		--sid 0x$(SECUREID) --vid 0x$(VENDORID) \
		--capability $(subst $(NULL) $(NULL),+,$(CAPABILITY)) \
		--libpath $(ARMV5LIBPATH) --fpu softvfp $(DSO)

dist/%_$(UID3).rsc inc/%_$(UID3).rsg: rss/%.rss
	epocrc.pl -Iinc -I$(SYSINCPATH) -D$(LANG) -u -v \
		$< -odist/$*_$(UID3).rsc -hinc/$*_$(UID3).rsg

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

%.sis: %.pkg $(RSSTARGET) $(BINTARGET)
	makesis -v $< $@

%.sisx: %.sis $(CERT) $(KEY)
	signsis -v $< $@ $(CERT) $(KEY)

resource: check $(RSSTARGET)

bin: check $(BINTARGET)

build: resource bin

pack: $(SISX)

install: $(SISX)
	bluetooth-sendto $<

