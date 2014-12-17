#include <stage1.h>
#include <code16.h>
#include <io.h>

#ifdef PRINT
void __attribute__((noinline)) __attribute__((regparm(3))) puts(const char *s){
  while (*s){
    /* Interrupt 0x10: Teletype output
     *    AH 0x0E Print character
     *    AL=Character
     *    BH=Page Number
     *    BL=Color (in graphics mode)
     */
    __asm__ __volatile__ ("int $0x10" :: "a" (0x0E00 | *s), "b" (7));
    s++;
  }
}

void putc(const char c){
    __asm__ __volatile__ ("int $0x10" :: "a" (0x0E00 | c), "b" (7));
}
#endif

#ifdef READ
char getc() {
  char c;
  /* Interrupt 0x16: Keyboard interrupt
   *   AH=0 read keyboard scancode
   * Returns:
   *   AL: keyboard scancode
   */
  __asm__ __volatile__ (
      "xorw %%ax,%%ax\n"
      "int $0x16\n"
      "mov %%al,%0\n" : "=r"(c)
      );
  return c;
}
#endif
