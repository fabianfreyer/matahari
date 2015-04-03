#!/bin/bash
set -e
 
# Usage:
#
# ./inteltoatt [16|32|64] "mov eax, eax \n xor ecx, edx"
#
 
case "$1" in
16|32|64)
	bits="$1"
	shift ;;
*)
	bits="32" ;;
esac
code="$1"
 
nasm="$(mktemp /tmp/nasm.XXXXXXXX)"
obj="$(mktemp /tmp/obj.XXXXXXXX)"
objdump="$(mktemp /tmp/objdump.XXXXXXXX)"
 
case "$bits" in
	16) m="i8086"       ;;
	32) m="i386"        ;;
	64) m="i386:x86-64" ;;
esac
 
echo -e "BITS $bits\n$code" > "$nasm"
 
nasm "$nasm" -o "$obj"
gobjdump -D -b binary -m $m -Maddr${bits},data${bits} "$obj" > "$objdump"
 
lineno="$(egrep -m 1 -n '<\.data>\:$' "$objdump" | cut -d':' -f1)"
lineno=$((lineno+1))
 
tail -n +$lineno "$objdump"
