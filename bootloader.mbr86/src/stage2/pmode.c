#include <common/arch.h>
#include <common/config.h>
#include <common/multiboot.h>
#include <stage2/pmode.h>
#include <drivers/video.h>

#ifdef ARCH_x86
void setup_segment_registers(uint8_t segment) {
  /* Set the data segments */
  asm volatile(
    "mov %0, %%ds\n"
    "mov %0, %%es\n"
    "mov %0, %%fs\n"
    "mov %0, %%gs\n"
    "mov %0, %%ss\n"
    ::"r"(segment<<3));
}
#endif

void kernel_stub() {
  puts32("failed to load kernel.\n");
  YOU_SHALL_NOT_PASS;
}

/**
 * The entry point for protected mode.
 */
void stage2_pmode() {
#ifdef ARCH_x86
  uint8_t global_code_segment, global_data_segment;
  multiboot_t *multiboot;
  // As commeted in pmode.h, we will get some arguments in registers c and d.
  asm volatile("":"=c"(global_code_segment), "=d"(global_data_segment), "=a"(multiboot):);
  setup_segment_registers(global_data_segment);
  puts32(multiboot->boot_loader_name);
#endif
  puts32("In protected mode.\n");
  /*
   * Most likely we got here from a far jump from protected mode. And quite
   * probably, our stack is all fucked up after this, and we should never
   * return, or triple faults will hail upon us.
   */

  // prepare machine state for multiboot
  void *kernel = kernel_stub;
#ifdef ARCH_x86
  asm volatile("jmp %0"::"m"(kernel), "a"(MULTIBOOT_MAGIC), "b"(multiboot));
#endif
  YOU_SHALL_NOT_PASS;
}
