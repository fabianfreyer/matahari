#include <stage1.h>
#include <code16.h>
#include <io.h>
#include <partition_table.h>
#include <gdt.h>
#include <disk.h>

__asm__ ("jmpl  $0, $main\n");

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
  asm volatile("lgdt %0" : : "m" (gdtp));
}
#endif

void __attribute__((noreturn)) main(){
  unsigned char drv = get_bios_drive();
  putc('0'+drv-0x80);
  puts("...\r\n");

  #ifdef GET_DRIVE_GEOM
  drive_geom g;
  get_drive_geom(&g, drv);
  #endif

  char block[512];
  chs_read((const void*) &block, 0,0,1,1, drv);
  putc('X');
  puts("\n\rread block\n\r");
  int i;
  for(i=0; i<=block[0]; i++) {putc('0');}
  puts("\n\rread block\n\r");

  #ifdef SETUP_GDT
  setup gdt();
  #endif

  while(1) {
  }
}
