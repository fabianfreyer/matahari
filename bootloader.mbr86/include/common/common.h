#pragma once

#include <common/types.h>

#define _define_wrap(x) do { x } while(0)
#define YOU_SHALL_NOT_PASS _define_wrap(while(1) {}; )
#define BOCHS_BREAK _define_wrap(asm volatile ("xchgw %bx, %bx");)
