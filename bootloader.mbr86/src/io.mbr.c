#include <arch.h>
#include <code16.h>

#include <mbr/features.h>
#include <mbr/io.h>

#ifdef MBR_PRINT
void __attribute__((noinline)) __attribute__((regparm(3))) puts16(const char *s){
#ifdef ARCH_x86
  while (*s){
    /* Interrupt 0x10: Teletype output
     *    AH 0x0E Print character
     *    AL=Character
     *    BH=Page Number
     *    BL=Color (in graphics mode)
     */
    asm volatile ("int $0x10" :: "a" (0x0E00 | *s), "b" (7));
    s++;
  }
#else
#warning puts not implemented for arch
#endif
}

void putc16(const char c){
#ifdef ARCH_x86
  asm volatile ("int $0x10" :: "a" (0x0E00 | c), "b" (7));
#else
#warning puts not implemented for arch
#endif
}
#endif

#ifdef MBR_READ
char getc16() {
#ifdef ARCH_x86
  char c;
  /* Interrupt 0x16: Keyboard interrupt
   *   AH=0 read keyboard scancode
   * Returns:
   *   AL: keyboard scancode
   */
  asm volatile (
      "xorw %%ax,%%ax\n"
      "int $0x16\n"
      "mov %%al,%0\n" : "=r"(c)
      );
#else
#warning puts not implemented for arch
#endif
  return c;
}
#endif
