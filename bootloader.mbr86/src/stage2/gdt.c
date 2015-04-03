#include <common/arch.h>
#include <common/code16.h>

#include <stage2/gdt.h>

gdt_entry_t gdt_entry(void *base, void *limit, uint16_t flag) {
  gdt_entry_t gate;

  ((int8_t*) &gate)[0] = (uint32_t)  limit          & 0xFF;
  ((int8_t*) &gate)[1] = ((uint32_t) limit >> 0x08) & 0xFF;
  ((int8_t*) &gate)[2] = (uint32_t)  base           & 0xFF;
  ((int8_t*) &gate)[3] = ((uint32_t) base >> 0x08)  & 0xFF;
  ((int8_t*) &gate)[4] = ((uint32_t) base >> 0x10)  & 0xFF;
  ((int8_t*) &gate)[5] = flag & 0xFF;
  ((int8_t*) &gate)[6] = ((uint32_t) limit >> 0x10) & 0x0F;
  ((int8_t*) &gate)[6] |=               (flag >> 0x08)  & 0xF0;
  ((int8_t*) &gate)[7] = ((uint32_t) base >> 0x18)  & 0xFF;

  return gate;
}

void gdt_load(gdt_entry_t *entries, uint16_t count) {
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
