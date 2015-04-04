#include <common/arch.h>
#include <common/code16.h>
#include <common/config.h>
#include <common/interrupts.h>
#include <common/multiboot.h>
#include <mbr/io.h>
#include <mbr/disk.h>
#include <stage2/gdt.h>
#include <stage2/a20.h>
#include <stage2/pmode.h>
#include <stage2/mem.h>
#include <stage2/debug.h>

int __attribute__((noinline)) get_drive_geom(
    drive_geom *g, unsigned char drive) {
unsigned short failed=0;
#ifdef ARCH_x86
  unsigned short tmp1, tmp2;
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

void setup_a20() {
#ifdef DEBUG
  puts16("enabling a20 line... ");
#endif
  uint8_t a20;
  if (!a20_memory_status()) {
    a20=a20_enable();
#ifdef DEBUG
    switch (a20) {
    case A20_SET_BIOS:
      puts16("set using BIOS\n\r");
      break;
    case A20_SET_FAST:
      puts16("set using output port\n\r");
      break;
    case A20_SET_KEYB:
      puts16("set using Keyboard controller command\n\r");
      break;
    case A20_SET_KEYB_OUT:
      puts16("set using Keyboard controller pin\n\r");
      break;
    case A20_SET_FAILED:
    default:
      puts16("failed.\n\r");
    }
  }
  else puts16("already enabled \n\r");
#else
  }
#endif
}

void setup_gdt() {
  puts16("loading gdt...\n\r");
  // Disable all interrupts before loading GDT
  disable_interrupts();
  disable_nmi();
  setup_global_gdt();
  puts16("done\n\r");
}

void setup_vga(uint8_t video_mode) {
  puts16("setting up VGA\n\r");
  asm volatile("int $0x10"::"a"(video_mode):);
}

void stage2_entry(uint32_t boot_drive) {
  multiboot_t multiboot = {
    .flags = 0x00 | MULTIBOOT_BOOT_LOADER_NAME | MULTIBOOT_BOOT_DEVICE,
    .boot_loader_name = "Matahari",
    .boot_device = boot_drive
  };
#ifdef DEBUG
  puts16("in stage2\n\r");
#endif

  // enabling a20 line
  setup_a20();

  // Load the GDT
  setup_gdt();

  // Detect memory
  detect_memory(&multiboot);

  // Inspect drive geometry...
  puts16("inspecting drive geom... {spt=");
  drive_geom g;
  get_drive_geom(&g, boot_drive);
  dumpb(g.spt);
  puts16(", heads=");
  dumpb(g.heads);
  puts16("}\n\r");

  // Set up VGA
  //setup_vga(0x3);
  puts16("entering protected mode...\n\r");

  /*
   * Switch to protected mode, pass the multiboot structure.
   */
  enter_pmode((const void*) &stage2_pmode,
    GDT_GLOBAL_CODE_SEGMENT,
    GDT_GLOBAL_DATA_SEGMENT,
    &multiboot);
}

