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


#define set_ds(_ds) _define_wrap(asm volatile("movw %w0,%%ds" :: "rm"(_ds) :);)
#define set_es(_es) _define_wrap(asm volatile("movw %w0,%%es" :: "rm"(_es) :);)
#define set_fs(_fs) _define_wrap(asm volatile("movw %w0,%%fs" :: "rm"(_fs) :);)
#define set_gs(_gs) _define_wrap(asm volatile("movw %w0,%%gs" :: "rm"(_gs) :);)
#define set_ss(_ss) _define_wrap(asm volatile("movw %w0,%%ss" :: "rm"(_ss) :);)
#define stack(_sp) _define_wrap(asm volatile("movw %w0,%%sp" :: "rm"(_sp) :);)

#define read_ds_32(addr, var) _define_wrap(asm volatile("movl %%ds:%1,%0" : "=r"(var) : "m" (*(uint32_t *)addr) :);)
#define read_ds_16(addr, var) _define_wrap(asm volatile("movw %%ds:%1,%0" : "=r"(var) : "m" (*(uint16_t *)addr) :);)
#define read_ds_8(addr, var) _define_wrap(asm volatile("movb %%ds:%1,%0" : "=r"(var) : "m" (*(uint8_t *)addr) :);)
#define write_ds_32(addr, var) _define_wrap(asm volatile("movl %1,%%ds:%0" : "+m" (*(uint32_t *)addr) : "ri"(var) :);)
#define write_ds_16(addr, var) _define_wrap(asm volatile("movw %1,%%ds:%0" : "+m" (*(uint16_t *)addr) : "ri"(var) :);)
#define write_ds_8(addr, var) _define_wrap(asm volatile("movb %1,%%ds:%0" : "+m" (*(uint8_t *)addr) : "ri"(var) :);)

#define read_fs_32(addr, var) _define_wrap(asm volatile("movl %%fs:%1,%0" : "=r"(var) : "m" (*(uint32_t *)addr) :);)
#define read_fs_16(addr, var) _define_wrap(asm volatile("movw %%fs:%1,%0" : "=r"(var) : "m" (*(uint16_t *)addr) :);)
#define read_fs_8(addr, var) _define_wrap(asm volatile("movb %%fs:%1,%0" : "=r"(var) : "m" (*(uint8_t *)addr) :);)
#define write_fs_32(addr, var) _define_wrap(asm volatile("movl %1,%%fs:%0" : "+m" (*(uint32_t *)addr) : "ri"(var) :);)
#define write_fs_16(addr, var) _define_wrap(asm volatile("movw %1,%%fs:%0" : "+m" (*(uint16_t *)addr) : "ri"(var) :);)
#define write_fs_8(addr, var) _define_wrap(asm volatile("movb %1,%%fs:%0" : "+m" (*(uint8_t *)addr) : "ri"(var) :);)

#define read_gs_32(addr, var) _define_wrap(asm volatile("movl %%gs:%1,%0" : "=r"(var) : "m" (*(uint32_t *)addr) :);)
#define read_gs_16(addr, var) _define_wrap(asm volatile("movw %%gs:%1,%0" : "=r"(var) : "m" (*(uint16_t *)addr) :);)
#define read_gs_8(addr, var) _define_wrap(asm volatile("movb %%gs:%1,%0" : "=r"(var) : "m" (*(uint8_t *)addr) :);)
#define write_gs_32(addr, var) _define_wrap(asm volatile("movl %1,%%gs:%0" : "+m" (*(uint32_t *)addr) : "ri"(var) :);)
#define write_gs_16(addr, var) _define_wrap(asm volatile("movw %1,%%gs:%0" : "+m" (*(uint16_t *)addr) : "ri"(var) :);)
#define write_gs_8(addr, var) _define_wrap(asm volatile("movb %1,%%gs:%0" : "+m" (*(uint8_t *)addr) : "ri"(var) :);)

/*
 * note: we cannot _define_wrap this because it may get called outside a function
 */
#define _longjmp_main __asm__ ("jmpl  $0, $main")
#define _longjmp_init __asm__ ("jmpl  $0, $init")
