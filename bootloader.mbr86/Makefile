ARCH=i386
QEMU=qemu-system-$(ARCH)

DEBUGGER=nemiver
DEBUGGER_OPTIONS=--remote=localhost:1234

OUTPUT=build32

LDFLAGS= -melf_$(ARCH) -static -nostdlib -nmagic
CFLAGS=-g -Os -m32 -march=i686 -ffreestanding -fno-pic -ffast-math -fomit-frame-pointer -Wall -Werror -Iinclude -DARCH_$(ARCH)

COMPONENTS=mbr stage2

#MBR configuration
mbr_MODULES=entry disk io partition_table
mbr_SECTIONS=.text_mbr .data_mbr .partition_table .sig

#Stage2 configuration
stage2_MODULES=entry
stage2_SECTIONS=.text_stage2 .data_stage2

.PHONY: all
all: $(foreach component,$(COMPONENTS),$(OUTPUT)/$(component).bin) section-headers

.PHONY: section-headers
section-headers: $(OUTPUT)/loader.elf
	$(call toolchain,$(OBJDUMP)) -h $^

.PHONY: test
test: $(OUTPUT)/mbr.bin
	$(QEMU) $^

qemu.pid: $(OUTPUT)/mbr.bin
	$(QEMU) -monitor stdio -s -S $^ & echo $$! > $@

.PHONY: qemu.pid
debug: qemu.pid $(OUTPUT)/loader.elf
	$(DEBUGGER) $(DEBUGGER_OPTIONS) $(word 2,$^)
	kill `cat $<` 
	rm $<

.PHONY: clean
clean:
	rm $(OUTPUT)/*

$(OUTPUT)/%.bin: $(OUTPUT)/loader.elf
	$(call toolchain,$(OBJCOPY)) -O binary $(foreach section,$($*_SECTIONS),-j $(section)) $< $@

%.bin : %.elf
	$(call toolchain,$(OBJCOPY)) -O binary $< $@

$(OUTPUT)/loader.elf: loader.ld $(foreach component, $(COMPONENTS),$(foreach mod,$($(component)_MODULES),$(OUTPUT)/$(mod).$(component).o))
	$(call toolchain,$(LD)) -T$(filter %.ld,$^) $(LDFLAGS) -o $@ $(filter %.o,$^)

$(OUTPUT)/%.o: src/%.c
	$(call toolchain,$(CC)) $(CFLAGS) -c -o $@ $<
