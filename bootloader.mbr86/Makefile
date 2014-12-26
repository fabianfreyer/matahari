ARCH=i386
QEMU=qemu-system-$(ARCH)

# Debugging
GDB=$(call toolchain,gdb)
GDB_OPTIONS=-ex "target remote localhost:1234" -ex "set architecture i8086" -ex "break main" -ex "set step-mode on"

NEMIVER=nemiver
NEMIVER_OPTIONS=--remote=localhost:1234

OUTPUT=build32

LDFLAGS= -melf_$(ARCH) -static -nostdlib -nmagic
CFLAGS=-g -Os -m32 -march=i686 -ffreestanding -fno-pic -ffast-math -fomit-frame-pointer -Wall -Werror -Iinclude -DARCH_$(ARCH)

COMPONENTS=mbr stage2

#MBR configuration
mbr_MODULES=entry disk io partition_table
mbr_SECTIONS=.text_mbr .data_mbr .partition_table .sig

#Stage2 configuration
stage2_MODULES=entry gdt pmode video
stage2_SECTIONS=.text_stage2 .data_stage2

.PHONY: all
all: build32/image.bin section-headers

.PHONY: section-headers
section-headers: $(OUTPUT)/loader.elf
	$(call toolchain,$(OBJDUMP)) -h $^

.PHONY: test
test: $(OUTPUT)/mbr.bin
	$(QEMU) $^

qemu.pid: build32/image.bin
	$(QEMU) -monitor stdio -s -S -d int,cpu_reset $^ & echo $$! > $@

.PHONY: qemu.pid
debug: qemu.pid $(OUTPUT)/loader.elf
	$($(DEBUGGER)) $($(DEBUGGER)_OPTIONS) $(word 2,$^)
	kill `cat $<` 
	rm $<

.PHONY: clean
clean:
	rm $(OUTPUT)/*

build32/image.bin: $(foreach component,$(COMPONENTS),$(OUTPUT)/$(component).bin)
	cat build32/mbr.bin build32/stage2.bin > $@

$(OUTPUT)/%.bin: $(OUTPUT)/loader.elf
	$(call toolchain,$(OBJCOPY)) -O binary $(foreach section,$($*_SECTIONS),-j $(section)) $< $@

%.bin : %.elf
	$(call toolchain,$(OBJCOPY)) -O binary $< $@

$(OUTPUT)/loader.elf: loader.ld $(foreach component, $(COMPONENTS),$(foreach mod,$($(component)_MODULES),$(OUTPUT)/$(mod).$(component).o))
	$(call toolchain,$(LD)) -T$(filter %.ld,$^) $(LDFLAGS) -o $@ $(filter %.o,$^)

.PHONY: depend
depend: $(OUTPUT)/loader.elf.depend

$(OUTPUT)/loader.elf.depend: $(foreach component, $(COMPONENTS),$(foreach mod,$($(component)_MODULES),$(OUTPUT)/$(mod).$(component).depend))
	cat $^ > $@

include $(OUTPUT)/loader.elf.depend

$(OUTPUT)/%.o: src/%.c
	$(call toolchain,$(CC)) $(CFLAGS) -c -o $@ $<

$(OUTPUT)/%.depend: src/%.c
	$(call toolchain,$(CC)) $(CFLAGS) -MM -MT $(OUTPUT)/$*.o -MF $@ $^
