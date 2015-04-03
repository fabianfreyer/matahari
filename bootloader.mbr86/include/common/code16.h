#pragma once
/**
 * Include this file in every c file that contains code running on real mode.
 */

#include <common/common.h>
#include <common/types.h>
#include <common/arch.h>

/**
 * This is a really ugly hack to compile code for x86 real mode.
 * @addtogroup bootloader
 */
#ifdef ARCH_x86
asm (".code16gcc\n");
#endif

#define REAL_MODE
#define CODE16


#define set_ds(_ds) MACRO(asm volatile("movw %0 %%ds" :: "rm"(_ds) :);)
#define set_fs(_fs) MACRO(asm volatile("movw %0,%%fs" :: "rm"(_fs) :);)
#define set_gs(_gs) MACRO(asm volatile("movw %0,%%gs" :: "rm"(_gs) :);)

#define read_ds_32(addr, var) MACRO(asm volatile("movl %%ds:%1,%0" : "=r"(var) : "m" (*(uint32_t *)addr) :);)
#define read_ds_16(addr, var) MACRO(asm volatile("movw %%ds:%1,%0" : "=r"(var) : "m" (*(uint16_t *)addr) :);)
#define read_ds_8(addr, var) MACRO(asm volatile("movb %%ds:%1,%0" : "=r"(var) : "m" (*(uint8_t *)addr) :);)
#define write_ds_32(addr, var) MACRO(asm volatile("movl %1,%%ds:%0" : "+m" (*(uint32_t *)addr) : "ri"(var) :);)
#define write_ds_16(addr, var) MACRO(asm volatile("movw %1,%%ds:%0" : "+m" (*(uint16_t *)addr) : "ri"(var) :);)
#define write_ds_8(addr, var) MACRO(asm volatile("movb %1,%%ds:%0" : "+m" (*(uint8_t *)addr) : "ri"(var) :);)

#define read_fs_32(addr, var) MACRO(asm volatile("movl %%fs:%1,%0" : "=r"(var) : "m" (*(uint32_t *)addr) :);)
#define read_fs_16(addr, var) MACRO(asm volatile("movw %%fs:%1,%0" : "=r"(var) : "m" (*(uint16_t *)addr) :);)
#define read_fs_8(addr, var) MACRO(asm volatile("movb %%fs:%1,%0" : "=r"(var) : "m" (*(uint8_t *)addr) :);)
#define write_fs_32(addr, var) MACRO(asm volatile("movl %1,%%fs:%0" : "+m" (*(uint32_t *)addr) : "ri"(var) :);)
#define write_fs_16(addr, var) MACRO(asm volatile("movw %1,%%fs:%0" : "+m" (*(uint16_t *)addr) : "ri"(var) :);)
#define write_fs_8(addr, var) MACRO(asm volatile("movb %1,%%fs:%0" : "+m" (*(uint8_t *)addr) : "ri"(var) :);)

#define read_gs_32(addr, var) MACRO(asm volatile("movl %%gs:%1,%0" : "=r"(var) : "m" (*(uint32_t *)addr) :);)
#define read_gs_16(addr, var) MACRO(asm volatile("movw %%gs:%1,%0" : "=r"(var) : "m" (*(uint16_t *)addr) :);)
#define read_gs_8(addr, var) MACRO(asm volatile("movb %%gs:%1,%0" : "=r"(var) : "m" (*(uint8_t *)addr) :);)
#define write_gs_32(addr, var) MACRO(asm volatile("movl %1,%%gs:%0" : "+m" (*(uint32_t *)addr) : "ri"(var) :);)
#define write_gs_16(addr, var) MACRO(asm volatile("movw %1,%%gs:%0" : "+m" (*(uint16_t *)addr) : "ri"(var) :);)
#define write_gs_8(addr, var) MACRO(asm volatile("movb %1,%%gs:%0" : "+m" (*(uint8_t *)addr) : "ri"(var) :);)
