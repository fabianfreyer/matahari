#include <common/arch.h>
#include <common/code16.h>

#include <common/config.h>

#include <mbr/features.h>
#include <mbr/io.h>
#include <mbr/disk.h>
#include <common/partition_table.h>

extern void stage2_entry(uint8_t drive);

#ifdef ARCH_x86
__asm__ ("jmpl  $0, $main\n");
#endif


void __attribute__((noreturn)) main(){
  uint8_t boot_drive = get_bios_drive();

  #ifdef PRINT
  puts16("booting from ");
  if (0x80 & boot_drive) puts16("hd");
  else puts16("fd");
  putc16('0'+boot_drive-0x80);
  puts16("\r\n");
  #endif

  #ifdef MBR_GET_DRIVE_GEOM
  drive_geom g;
  get_drive_geom(&g, drv);
  #endif

  // Load Stage2
  #ifdef MBR_CHS_READ

  #ifdef MBR_PRINT
  puts16("Stage 2 loading, please wait...\r\n");
  #endif

  //calculate stage2 length
  extern unsigned long _stage2_load_address;
  void (*stage2)() = (void (*)()) &_stage2_load_address;
  extern unsigned long _stage2_size;
  uint16_t stage2_blocks = ((uint32_t) &_stage2_size >> 9) + (((uint32_t) &_stage2_size % 0x200)?1:0);

  chs_read(
    (void*) stage2,
    STAGE2_CYLINDER,
    STAGE2_HEAD,
    STAGE2_SECTOR,
    stage2_blocks,
    boot_drive);
  stage2_entry(boot_drive);
  /* This point should never be reached */
  #ifdef MBR_PRINT
  puts16("FAILED.\r\n");
  #endif
  #endif

  YOU_SHALL_NOT_PASS;
}
