#include <disk.h>
#include <partition_table.h>
extern mbr_t mbr;

char get_bios_drive() {
  unsigned char bios_drive = 0;
  asm volatile("movb %%dl, %0" : "=r"(bios_drive));
  return bios_drive;
}

/* int __attribute__((noinline)) get_drive_geom(
    drive_geom *g, unsigned char drive) {
  unsigned short tmp1, tmp2;
  unsigned short failed=0;
  __asm__ __volatile__ (
      "movw $0, %0\n"
      "xor %%esi,%%esi\n"
      "int $0x13\n"
      "setcb %0\n"
      : "=m"(failed), "=c"(tmp1), "=d"(tmp2)
      : "a"(0x0800), "d"(drive), "D"(0)
      : "cc", "bx"
   );
  if(failed)
    return failed;
  g->spt = tmp1 & 0x3F;
  g->heads = tmp2 >> 8;
  return failed;
}*/

void __attribute__((noinline)) chs_read(
  const void *buffer, unsigned char c, unsigned char h, unsigned char s,
  unsigned char blocks, unsigned char drive){
  /*
   * we cannot clobber ebx, so need to push and pop it
   */
  __asm__ __volatile__(
    "movb $0x02, %%ah\n"
    "int $0x13\n"
    :
    :"al"(blocks), "b"(buffer),
    "ch"(c), "cl"(s), "dh"(h<<8), "dl"(drive)
    : "cc", "memory" 
  );
}
/*void __attribute__((noinline)) lba_read(
  const void *buffer, unsigned int lba, unsigned char blocks,
  drive_geom *g, unsigned char drive) {
  unsigned char c, h, s;
  c = C(lba, g->spt, g->heads);
  h = H(lba, g->spt, g->heads);
  s = S(lba, g->spt, g->heads);
  asm volatile(
    "int $0x13\n"
    :
    :"a"(0x0200), "c"((c<<8)|s), "d"((h<<8) | drive), "D"(0), "b"(buffer) 
  );
}*/


