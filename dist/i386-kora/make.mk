
$(outdir)/%.o: $(srcdir)/%.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf32 -o $@ $<

$(libdir)/crt0.o: $(topdir)/dist/${target_arch}-${target_os}/crt0.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf32 -o $@ $<

ASM_EXT := asm

# CFLAGS += -I$(topdir)/dist/${target_arch}-${target_os}
# CFLAGS += -I$(srcdir)/os/${target_os}

SRCS += $(wildcard $(srcdir)/arch/${target_arch}/*.asm)
SRCS += $(wildcard $(srcdir)/arch/${target_arch}/*.c)
SRCS += $(wildcard $(srcdir)/os/${target_os}/*.c)
