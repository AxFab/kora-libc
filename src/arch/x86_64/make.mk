
$(outdir)/%.o: $(srcdir)/%.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf64 -o $@ $<

$(libdir)/crt0.o: $(topdir)/dist/${target_arch}-${target_os}/crt0.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf64 -o $@ $<

ASM_EXT := asm

SRCS += $(wildcard $(srcdir)/arch/x86_64/*.asm)
SRCS += $(wildcard $(srcdir)/arch/i386/*.c)
