#include <common.h>
#include <stage1.h>
#include <code16.h>
#include <arch.h>
#include <io.h>
#include <partition_table.h>
#include <gdt.h>
#include <disk.h>

#ifdef ARCH_x86
__asm__ ("jmpl  $0, $main\n");
#endif

#ifdef SETUP_GDT
void setup_gdt() {
  static gdt_entry_t gdt_entries[3];
   gdt_entries[0] = GDT_ENTRY_NULL;
   gdt_entries[1] = GDT_ENTRY(0,0xFFFFFFFF,gdt_granularity_4k,gdt_segment_32,
      1,gdt_kernel_mode,gdt_descriptor_code,gdt_executable_code,0,
      gdt_segment_rx,0);
   gdt_entries[2] = GDT_ENTRY(0,0xFFFFFFFF,gdt_granularity_4k,gdt_segment_32,
      1,gdt_kernel_mode,gdt_descriptor_data,gdt_executable_data,0,
      gdt_segment_rw,0);
  struct {unsigned int limit:16 ;void* pointer;} __attribute__((packed)) gdtp={
    .limit = 3*8 - 1,
    .pointer = (void*) gdt_entries,
  };
#ifdef ARCH_x86
  asm volatile("lgdt %0" : : "m" (gdtp));
#endif
}
#endif

void __attribute__((noreturn)) main(){
  unsigned char boot_drive = get_bios_drive();

  #ifdef PRINT
  puts("booting from ");
  if (0x80 & boot_drive) puts("hd");
  else puts("fd");
  putc('0'+boot_drive-0x80);
  puts("\r\n");
  #endif

  #ifdef GET_DRIVE_GEOM
  drive_geom g;
  get_drive_geom(&g, drv);
  #endif

  // Load Stage2
  #ifdef CHS_READ
  static void (*stage2)() = (void (*)()) STAGE2_BASE;
  #ifdef PRINT
  puts("Stage 2 loading, please wait...\r\n");
  #endif
  chs_read(
    (void*) stage2,
    STAGE2_CYLINDER,
    STAGE2_HEAD,
    STAGE2_SECTOR,
    STAGE2_LENGTH,
    boot_drive);
  stage2();
  /* This point should never be reached */
  #ifdef PRINT
  puts("FAILED.\r\n");
  #endif
  #endif

  while(1) {
  }
}
