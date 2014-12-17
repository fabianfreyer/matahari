export TOP_DIR=$(dir $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

export CC=gcc
export LD=ld
export OBJDUMP=objdump
export OBJCOPY=objcopy

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

.PHONY: bootloader.mbr86
bootloader.mbr86:
	$(MAKE) -C bootloader.mbr86
