
$(outdir)/%.o: $(srcdir)/%.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf64 -o $@ $<

$(libdir)/crt0.o: $(srcdir)/arch/amd64/crt0.asm
	$(S) mkdir -p $(dir $@)
	$(Q) echo "    ASM $<"
	$(V) nasm -f elf64 -o $@ $<

ASM_EXT := asm
SRCS-y += $(wildcard $(srcdir)/arch/amd64/libc/*.asm)

