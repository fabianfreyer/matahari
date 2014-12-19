#include <arch.h>
#include <code16.h>
#include <common.h>
#include <interrupts.h>

#include <mbr/io.h>
#include <gdt.h>
#include <pmode.h>

void setup_global_gdt();

#ifdef DEBUG
void dumpb(unsigned char byte) {
  unsigned char hi_nybble = byte >> 4;
  unsigned char lo_nybble = byte & 0xF;
  putc16((hi_nybble)+(hi_nybble<0xA?'0':'a'-0xA));
  putc16((lo_nybble)+(lo_nybble<0xA?'0':'a'-0xA));
}
void dump(void * addr, unsigned int count) {
  unsigned char* byte = addr;
  int i;
  for(i=0; i<count; i++) {
    dumpb(byte[i]);
    if (! (i+1) % 16) puts16("\n\r");
    else if (! (i+1) % 8) puts16("  ");
    else putc16(' ');
  }
  puts16("\n\r");
}
#endif

void stage2_entry(unsigned char boot_drive) {
  puts16("in stage2\n\r");
  puts16("loading gdt...\n\r");

  /*
   * Disable all interrupts before loading GDT
   */
  disable_interrupts();
  disable_nmi();
  setup_global_gdt();
  puts16("done\n\r");
  puts16("entering protected mode...\n\r");

  /*
   * Switch to protected mode
   */
  enter_pmode((const void*) &stage2_pmode, 1);
}

/**
 * Sets up a global code page and a global data page
 */
void setup_global_gdt() {
  static gdt_entry_t gdt_entries[3];
  /* Null entry */
  gdt_entries[0] = gdt_entry((void*) 0, (void*) 0,0);

  /* Global code segment */
  gdt_entries[1] = gdt_entry((void*) 0, (void*) 0xFFFFFFFFU,
    SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
    SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
    SEG_PRIV(0)     | SEG_CODE_EXRD);

  /* Global data segment */
  gdt_entries[2] = gdt_entry((void*) 0, (void*) 0xFFFFFFFFU,
    SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
    SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
    SEG_PRIV(0)     | SEG_DATA_RDWR);

  #ifdef DEBUG
  puts16("null entry: ");
  dump(&gdt_entries[0], sizeof(gdt_entry_t));
  puts16("code entry: ");
  dump(&gdt_entries[1], sizeof(gdt_entry_t));
  puts16("data entry: ");
  dump(&gdt_entries[2], sizeof(gdt_entry_t));
  gdt_load(gdt_entries, 3);
  #endif
}
