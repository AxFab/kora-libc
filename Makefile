#      This file is part of the KoraOS project.
#  Copyright (C) 2015-2021  <Fabien Bavent>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as
#  published by the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Affero General Public License for more details.
#
#  You should have received a copy of the GNU Affero General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
topdir ?= $(shell readlink -f $(dir $(word 1,$(MAKEFILE_LIST))))
gendir ?= $(shell pwd)

include $(topdir)/make/global.mk
srcdir = $(topdir)/src

all: libc
static: $(gendir)/lib/libc.a
# 	crt0
# crt0: $(libdir)/crt0.o
install: $(prefix)/lib/libc.so $(prefix)/lib/crt0.o install-headers
# install-headers:
# 	$(V) cp -r $(topdir)/include $(prefix)/include
# 	$(V) cp -r $(topdir)/arch/$(target_arch)/include $(prefix)/include/$(target_arch)-$(target_os)

include $(topdir)/make/build.mk
include $(topdir)/make/check.mk

CFLAGS ?= -Wall -Wextra -Wno-unused-parameter -ggdb

SRCS_c += $(wildcard $(srcdir)/c89/*.c)
SRCS_c += $(wildcard $(srcdir)/convert/*.c)
SRCS_c += $(wildcard $(srcdir)/libio/*.c)
SRCS_c += $(wildcard $(srcdir)/misc/*.c)
SRCS_c += $(wildcard $(srcdir)/posix/*.c)
SRCS_c += $(wildcard $(srcdir)/string/*.c)
SRCS_c += $(wildcard $(srcdir)/synchro/*.c)
SRCS_c += $(wildcard $(srcdir)/xopen/*.c)
SRCS_c += $(wildcard $(srcdir)/net/*.c)

CFLAGS_c += $(CFLAGS)
CFLAGS_c += -ffreestanding -fPIC
CFLAGS_c += -I$(topdir)/include
CFLAGS_c += -I$(srcdir)/include/$(target_arch)
CFLAGS_c += -I$(srcdir)/include/$(target_os)
CFLAGS_c += -I$(srcdir)/include/$(target_arch)-$(target_os)

LFLAGS_c += -lgcc

ifeq ($(NOSCALL),y)
CFLAGS_c += -D__NO_SCALL
else
-include $(srcdir)/arch/$(target_arch)/make.mk
# -include $(srcdir)/os/$(target_os)/make.mk
SRCS_c += $(wildcard $(srcdir)/os/$(target_os)/*.c)
SRCS_c += $(wildcard $(srcdir)/os/$(target_os)/$(target_arch)/*.$(ASM_EXT))
endif

ifeq ($(GCOV),y)
CFLAGS_c += -fprofile-arcs -ftest-coverage
LFLAGS_c += -coverage
endif

$(gendir)/lib/libc.a:
	$(V) ar -rc $@ $(call fn_objs,SRCS_c,c)

SRCS_ck += ${SRCS_c}
SRCS_ck += $(wildcard $(srcdir)/tests/*.c)


$(eval $(call comp_source,c,CFLAGS_c))
$(eval $(call link_shared,c,SRCS_c,LFLAGS_c,c))
$(eval $(call link_bin,cklc,SRCS_ck,LFLAGS_c,c))

CHECKS += cklc

e_dist:
	@echo $(target_arch)-$(target_os)
e_srcs:
	@echo $(SRCS)


HDRS = $(wildcard $(topdir)/include/*.h)
HDRS += $(wildcard $(topdir)/include/sys/*.h)
HDRS += $(wildcard $(topdir)/include/bits/*.h)
HDRS += $(wildcard $(topdir)/include/bits/cdefs/*.h)
HDRS += $(wildcard $(topdir)/src/include/$(target_os)/bits/*.h)
HDRS += $(wildcard $(topdir)/src/include/$(target_arch)/bits/*.h)

HDRS_o = $(patsubst $(topdir)/include/%,$(prefix)/include/%, \
	$(patsubst $(topdir)/src/include/$(target_os)/%,$(prefix)/include/%, \
	$(patsubst $(topdir)/src/include/$(target_arch)/%,$(prefix)/include/%, \
	$(HDRS))))

install-headers: $(HDRS_o)

$(prefix)/include/%.h: $(topdir)/include/%.h
	$(S) mkdir -p $(dir $@)
	$(V) cp -vrP $< $@

$(prefix)/include/%.h: $(topdir)/src/include/$(target_os)/%.h
	$(S) mkdir -p $(dir $@)
	$(V) cp -vrP $< $@

$(prefix)/include/%.h: $(topdir)/src/include/$(target_arch)/%.h
	$(S) mkdir -p $(dir $@)
	$(V) cp -vrP $< $@



check: $(patsubst %,val_%,$(CHECKS))

ifeq ($(NODEPS),)
-include $(call fn_deps,SRCS_c,c)
-include $(call fn_deps,SRCS_ck,c)
endif
