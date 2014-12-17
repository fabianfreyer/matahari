TOOLCHAIN_TUPLE=i386-unknown-elf
TOOLCHAIN=../toolchain/target/$(TOOLCHAIN_TUPLE)

GCC=$(TOOLCHAIN)/bin/$(TOOLCHAIN_TUPLE)-gcc
LD=$(TOOLCHAIN)/bin/$(TOOLCHAIN_TUPLE)-ld
OBJCOPY=$(TOOLCHAIN)/bin/$(TOOLCHAIN_TUPLE)-objcopy
QEMU=qemu-system-i386

DEBUGGER=nemiver
DEBUGGER_OPTIONS=--remote=localhost:1234

all: build32/stage1.bin

test: build32/stage1.bin
	$(QEMU) $^

qemu.pid: build32/stage1.bin
	$(QEMU) -monitor stdio -s -S $^ & echo $$! > $@

debug: qemu.pid build32/stage1.elf.debug
	$(DEBUGGER) $(DEBUGGER_OPTIONS) $(word 2,$^)
	kill `cat $<` 
	rm $<

clean:
	rm build32/*

%.bin : %.elf
	$(OBJCOPY) -O binary $< $@

build32/stage1.elf: build32/stage1.o build32/io.o build32/partition_table.o build32/disk.o
	$(LD) -melf_i386 -static -Tlinker.ld -nostdlib --nmagic -o $@ $^
	$(LD) -melf_i386 -static -Tdebug.ld -nostdlib --nmagic -o $@.debug	$^

build32/%.o: src/%.c
	$(GCC) -c -g -Os -m32 -march=i686 -ffreestanding -fno-pic -ffast-math -fomit-frame-pointer -Wall -Werror -Iinclude -o $@ $<
	echo size of $@ is `wc -c $@` \n
	
