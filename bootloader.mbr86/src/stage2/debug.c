#include <common/code16.h>
#include <common/config.h>
#include <mbr/io.h>

#ifdef DEBUG
void dumpb(uint8_t byte) {
  uint8_t hi_nybble = byte >> 4;
  uint8_t lo_nybble = byte & 0xF;
  putc16((hi_nybble)+(hi_nybble<0xA?'0':'a'-0xA));
  putc16((lo_nybble)+(lo_nybble<0xA?'0':'a'-0xA));
}
void dump(void * addr, uint32_t count) {
  uint8_t* byte = addr;
  int32_t i;
  for(i=0; i<count; i++) {
    dumpb(byte[i]);
    if (! (i+1) % 16) puts16("\n\r");
    else if (! (i+1) % 8) puts16("  ");
    else putc16(' ');
  }
  puts16("\n\r");
}
#endif
