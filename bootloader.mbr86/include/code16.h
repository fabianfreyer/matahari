#pragma once
/**
 * Include this file in every c file that contains code running on real mode.
 */

#include <arch.h>

/**
 * This is a really ugly hack to compile code for x86 real mode.
 * @addtogroup bootloader
 */
#ifdef ARCH_x86
asm (".code16gcc\n");
#endif

#define REAL_MODE
#define CODE16
