
$(outdir)/%.o: $(srcdir)/%.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf32 -o $@ $<

$(libdir)/crt0.o: $(topdir)/dist/${target_arch}-${target_os}/crt0.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf32 -o $@ $<

ASM_EXT := asm

SRCS += $(wildcard $(srcdir)/arch/i386/*.asm)
SRCS += $(wildcard $(srcdir)/arch/i386/*.c)