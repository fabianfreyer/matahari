SYS := $(firstword $(shell uname -s))
BUILD_DIR=target
CT_NG=../tools/bin/ct-ng

all:$(BUILD_DIR)
	$(CT_NG) build

clean:clean-target
	rm build.log

include ${SYS}.mk
