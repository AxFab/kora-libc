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

all: libc crt0
crt0: $(libdir)/crt0.o
install: $(prefix)/lib/libc.so $(prefix)/lib/crt0.o
# install-headers:
# 	$(V) cp -r $(topdir)/include $(prefix)/include
# 	$(V) cp -r $(topdir)/arch/$(target_arch)/include $(prefix)/include/$(target_arch)-$(target_os)

include $(topdir)/make/build.mk

SRCS += $(wildcard $(srcdir)/c89/*.c)
SRCS += $(wildcard $(srcdir)/c95/*.c)
SRCS += $(wildcard $(srcdir)/c99/*.c)
SRCS += $(wildcard $(srcdir)/c11/*.c)
CFLAGS ?= -Wall -Wextra -Wno-unused-parameter -ggdb
CFLAGS += -ffreestanding
# CFLAGS += -nostdinc
CFLAGS += -I$(topdir)/include -fPIC

include $(topdir)/dist/$(target_arch)-${target_os}/make.mk

$(eval $(call link_shared,c,SRCS,LFLAGS))

r:
	@echo ${SRCS}
	@echo $(call fn_deps,SRCS)

ifeq ($(NODEPS),)
include $(call fn_deps,SRCS)
endif
