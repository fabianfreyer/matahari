#include <common/arch.h>
#include <common/code16.h>

#include <stage2/gdt.h>

gdt_entry_t gdt_entry(void *base, void *limit, unsigned short flag) {
  gdt_entry_t gate;

  ((char*) &gate)[0] = (unsigned int)  limit          & 0xFF;
  ((char*) &gate)[1] = ((unsigned int) limit >> 0x08) & 0xFF;
  ((char*) &gate)[2] = (unsigned int)  base           & 0xFF;
  ((char*) &gate)[3] = ((unsigned int) base >> 0x08)  & 0xFF;
  ((char*) &gate)[4] = ((unsigned int) base >> 0x10)  & 0xFF;
  ((char*) &gate)[5] = flag & 0xFF;
  ((char*) &gate)[6] = ((unsigned int) limit >> 0x10) & 0x0F;
  ((char*) &gate)[6] |=               (flag >> 0x08)  & 0xF0;
  ((char*) &gate)[7] = ((unsigned int) base >> 0x18)  & 0xFF;

  return gate;
}

void gdt_load(gdt_entry_t *entries, unsigned short count) {
  /* load the GDT */
  #ifdef ARCH_x86
  /*
   * Loads the values in the source operand into the global descriptor table
   * register (GDTR). The source operand specifies a 6-byte memory location
   * that contains the base address (a linear address) and the limit (size of
   * table in bytes).
   */
   gdt_t gdtp = {
    .gdt_size = count*sizeof(gdt_entry_t) - 1,
    .gdt_descriptors = entries,
  };
  asm volatile("lgdt %0" : : "m" (gdtp));
  #else
  #warning gdt_load not implemented for arch
  #endif
}
