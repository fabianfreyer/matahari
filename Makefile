export TOP_DIR=$(dir $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

export CC=gcc
export LD=ld
export OBJDUMP=objdump
export OBJCOPY=objcopy

IMAGE_SIZE=64 #mb

#Tools
export TOOL_PATH=$(TOP_DIR)tools/bin
toolify_=$(TOOL_PATH)/$(1)
export toolify=$(value toolify_)

CT_NG=$(call toolify_,ct-ng)

# toolchain
export TOOLCHAIN_TUPLE=$(shell cd toolchain && $(CT_NG) show-tuple)
export TOOLCHAIN=$(TOP_DIR)toolchain/target/$(TOOLCHAIN_TUPLE)
toolchain_=$(TOOLCHAIN)/bin/$(TOOLCHAIN_TUPLE)-$(1)
export toolchain=$(value toolchain_)

.PHONY: bootloader bootloader.mbr86 bootloader.mbr86-debug
bootloader: bootloader.mbr86

bootloader.mbr86: toolchain
	$(MAKE) -C bootloader.mbr86

bootloader.mbr86-debug:
	$(MAKE) -C bootloader.mbr86 debug


image.bin: bootloader.mbr86
	#dd if=/dev/zero of=image.img bs=1m count=$(IMAGE_SIZE)
	cp foo.img image.img
	dd conv=notrunc if=bootloader.mbr86/build32/image.bin of=image.img

.PHONY: toolchain
toolchain: $(CT_NG) $(call toolchain_,gcc)
$(call toolchain_,gcc):
	$(MAKE) -C toolchain

$(CT_NG):
	tools/run install-ct-ng

.PHONY: docs
docs: doc/doxyfile
	doxygen doc/doxyfile

.PHONY: clean
clean:
	rm crosstool-ng-*.tar.bz2
	rm -r crosstool-ng-*/
	rm -r tools/bin tools/lib
	$(MAKE) -C toolchain clean
	$(MAKE) -C bootloader.mbr86 clean
