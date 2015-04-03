#pragma once

void stage2_pmode();

#ifdef REAL_MODE
/*
 * Probably not the nicest way to do things, but hey, let's put this into a
 * header file. I mean, it's static, anyways.
 */
static inline void __attribute__((always_inline)) enter_pmode(
  const void *entrypoint, const uint8_t code_segment, const uint8_t data_segment) {
  #ifdef ARCH_x86
  /*
   * from Intel® 64 and IA-32 Architectures Software Developer’s Manual
   * Volume 3 (3A, 3B & 3C): System Programming Guide
   *
   * Enable protected mode
   * Setting the PE flag in register CR0 causes the processor to switch to
   * protected mode, which in turn enables the segment-protection mechanism.
   * Once in protected mode, there is no control bit for turning the protection
   * mechanism on or off.
   */
  asm volatile(
    "mov %%cr0, %%eax\n"
    "or $1, %%eax\n"
    "mov %%eax, %%cr0\n"
    :::"eax");
  /*
   * Let's jump to protected mode. Unfortunately, since this will mess with the
   * stack, we can't pass cdecl here. We have to pass via registers.
   * We will use the following calling convention here:
   *   ECX: code segment
   *   EDX: data segment
   */
  asm volatile("ljmp %0, %1"::"i"(code_segment<<3), "i"(entrypoint),"c"(code_segment),"d"(data_segment):);
  /*
   * Most likely the stack is all fucked up after this. At least, we should
   * never return from here.
   */
  YOU_SHALL_NOT_PASS;
  #endif
}
#endif
