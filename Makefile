#      This file is part of the KoraOS project.
#  Copyright (C) 2018  <Fabien Bavent>
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
install: $(prefix)/lib/libc.so $(prefix)/lib/crt0.o
# install-headers:
# 	$(V) cp -r $(topdir)/include $(prefix)/include
# 	$(V) cp -r $(topdir)/arch/$(target_arch)/include $(prefix)/include/$(target_arch)-$(target_os)

include $(topdir)/make/build.mk
include $(topdir)/make/check.mk

SRCS += $(wildcard $(srcdir)/c89/*.c)
SRCS += $(wildcard $(srcdir)/convert/*.c)
SRCS += $(wildcard $(srcdir)/libio/*.c)
SRCS += $(wildcard $(srcdir)/misc/*.c)
SRCS += $(wildcard $(srcdir)/posix/*.c)
SRCS += $(wildcard $(srcdir)/string/*.c)
SRCS += $(wildcard $(srcdir)/synchro/*.c)
SRCS += $(wildcard $(srcdir)/xopen/*.c)

CFLAGS ?= -Wall -Wextra -Wno-unused-parameter -ggdb
CFLAGS += -ffreestanding -fPIC
CFLAGS += -I$(topdir)/include
CFLAGS += -I$(srcdir)/include/$(target_arch)
CFLAGS += -I$(srcdir)/include/$(target_os)
CFLAGS += -I$(srcdir)/include/$(target_arch)-$(target_os)

LFLAGS += -lgcc

ifeq ($(NOSCALL),y)
CFLAGS += -D__NO_SCALL
else
-include $(srcdir)/arch/$(target_arch)/make.mk
# -include $(srcdir)/os/$(target_os)/make.mk
SRCS += $(wildcard $(srcdir)/os/$(target_os)/*.c)
SRCS += $(wildcard $(srcdir)/os/$(target_os)/$(target_arch)/*.$(ASM_EXT))
endif

ifeq ($(GCOV),y)
CFLAGS += -fprofile-arcs -ftest-coverage
LFLAGS += -coverage
endif


$(gendir)/lib/libc.a:
	$(V) ar -rc $@ $(call fn_objs,SRCS)

SRCS_ck += ${SRCS}
SRCS_ck += $(wildcard $(srcdir)/tests/*.c)

CHECKS += cklc

$(eval $(call link_shared,c,SRCS,LFLAGS))
$(eval $(call link_bin,cklc,SRCS_ck,LFLAGS))

e_dist:
	@echo $(target_arch)-$(target_os)
e_srcs:
	@echo $(SRCS)

ifeq ($(NODEPS),)
include $(call fn_deps,SRCS)
endif
