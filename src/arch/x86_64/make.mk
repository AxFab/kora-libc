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

$(outdir)/%.o: $(srcdir)/%.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf64 -o $@ $<

$(libdir)/crt0.o: $(srcdir)/os/${target_os}/${target_arch}/crts/crt0.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf64 -o $@ $<

ASM_EXT := asm

SRCS += $(wildcard $(srcdir)/arch/x86_64/*.asm)
SRCS += $(wildcard $(srcdir)/arch/i386/*.c)
