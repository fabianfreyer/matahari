#include <common/arch.h>
#include <common/code16.h>

#include <mbr/features.h>
#include <mbr/disk.h>
#include <common/partition_table.h>
extern mbr_t mbr;

int8_t get_bios_drive() {
  uint8_t bios_drive = 0;
  asm volatile("movb %%dl, %0" : "=r"(bios_drive));
  return bios_drive;
}

#ifdef MBR_GET_DRIVE_GEOM
int32_t __attribute__((noinline)) get_drive_geom(
    drive_geom *g, uint8_t drive) {
uint16_t failed=0;
#ifdef ARCH_x86
  uint16_t tmp1, tmp2;
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
#else
#warn get_drive_geom not implemented for arch
#endif
  return failed;
}
#endif

#ifdef MBR_CHS_READ
uint8_t __attribute__((noinline)) chs_read(const void *buffer, uint8_t cylinder, uint8_t head, uint16_t sector, uint8_t blocks, uint8_t drive) {
#ifdef ARCH_x86
  asm volatile(
  "int $0x13"
    :
    : "a"(0x200|blocks),
      "b"(buffer),
      "c"((cylinder&0xFF)<<8|(cylinder&0x300)>>2|(sector&0x3F)),
      "d"((uint16_t) head<<8|drive)
    : "cc","memory"
  );
  /* uint16_t status=i(a>>8); */
#else
#warning chs_read not implemented for arch
#endif
  return 0; //(uint8_t) (a&0xFF);
}
#endif

#ifdef MBR_LBA_READ
void __attribute__((noinline)) lba_read(
  const void *buffer, uint32_t lba, uint8_t blocks,
  drive_geom *g, uint8_t drive) {
#ifdef ARCH_x86
  uint8_t c, h, s;
  c = C(lba, g->spt, g->heads);
  h = H(lba, g->spt, g->heads);
  s = S(lba, g->spt, g->heads);
  asm volatile(
    "int $0x13\n"
    :
    :"a"(0x0200), "c"((c<<8)|s), "d"((h<<8) | drive), "D"(0), "b"(buffer)
  );
#else
#warning lba_read not implemented for arch
#endif
}
#endif


