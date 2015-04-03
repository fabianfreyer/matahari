SYS := $(firstword $(shell uname -s))
BUILD_DIR=target
CT_NG=../tools/bin/ct-ng

all: $(BUILD_DIR) $(BUILD_DIR)/i386-baremetal-elf/bin/i386-baremetal-elf-gcc

$(BUILD_DIR)/i386-baremetal-elf/bin/i386-baremetal-elf-gcc: $(BUILD_DIR)
	$(CT_NG) build

clean:clean-target
	rm build.log

menuconfig:
	$(CT_NG) $@ 

include ${SYS}.mk
