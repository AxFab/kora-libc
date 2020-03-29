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
#  This makefile is more or less generic.
#  The configuration is on `sources.mk`.
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
topdir ?= $(shell readlink -f $(dir $(word 1,$(MAKEFILE_LIST))))
gendir ?= $(shell pwd)

include $(topdir)/make/global.mk

all: libc crt0
crt0: $(libdir)/crt0.o
install: $(prefix)/lib/libc.so $(prefix)/lib/crt0.o

DISTO ?= kora

include $(topdir)/make/build.mk

SRCS-y += $(wildcard $(srcdir)/src/c89/*.c)
SRCS-y += $(wildcard $(srcdir)/src/c95/*.c)
SRCS-y += $(wildcard $(srcdir)/src/c99/*.c)
SRCS-y += $(wildcard $(srcdir)/src/c11/*.c)
SRCS-y += $(wildcard $(srcdir)/src/os-$(DISTO)/*.c)
CFLAGS ?= -Wall -Wextra -Wno-unused-parameter -ggdb
CFLAGS += -I$(srcdir)/include -fPIC

include $(topdir)/arch/$(target_arch)/make.mk

$(eval $(call link_shared,c,SRCS,LFLAGS))


ifeq ($(NODEPS),)
include $(call fn_deps,SRCS-y)
endif
