#include <stage1.h>
#include <code16.h>
#include <disk.h>
#include <partition_table.h>
extern mbr_t mbr;

char get_bios_drive() {
  unsigned char bios_drive = 0;
  asm volatile("movb %%dl, %0" : "=r"(bios_drive));
  return bios_drive;
}

#ifdef GET_DRIVE_GEOM
int __attribute__((noinline)) get_drive_geom(
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
}
#endif

#ifdef CHS_READ
unsigned char __attribute__((noinline)) chs_read(const void *buffer, unsigned char cylinder, unsigned char head, unsigned short sector, unsigned char blocks, unsigned char drive) {
  asm volatile(
  "int $0x13"
    : 
    : "a"(0x200|blocks),
      "b"(buffer),
      "c"((cylinder&0xFF)<<8|(cylinder&0x300)>>2|(sector&0x3F)),
      "d"((unsigned short) head<<8|drive)
    : "cc","memory"
  );
  /* unsigned short status=i(a>>8); */
  return 0; //(unsigned char) (a&0xFF);
}
#endif

#ifdef LBA_READ
void __attribute__((noinline)) lba_read(
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
}
#endif


