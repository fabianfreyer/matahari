#pragma once
#include <arch.h>

/**
 * This is a really ugly hack to compile code for x86 real mode.
 * @addtogroup bootloader
 */
#ifdef ARCH_x86
asm (".code16gcc\n");
#endif
