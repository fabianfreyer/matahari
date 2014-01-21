SYS := $(firstword $(shell uname -s))
BUILD_DIR=target


all:$(BUILD_DIR)
	ct-ng build

clean:clean-target
	rm build.log

include ${SYS}.mk
