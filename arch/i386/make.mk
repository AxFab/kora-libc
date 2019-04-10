
$(outdir)/%.o: $(srcdir)/%.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf32 -o $@ $<

$(libdir)/crt0.o: $(srcdir)/arch/i386/crt0.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf32 -o $@ $<

ASM_EXT := asm
SRCS-y += $(wildcard $(srcdir)/arch/i386/libc/*.asm)
SRCS-y += $(wildcard $(srcdir)/arch/i386/libc/*.c)

