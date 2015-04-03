#include <common/arch.h>
#include <common/code16.h>
#include <common/config.h>

#include <mbr/io.h>
#include <stage2/a20.h>

uint8_t a20_enabled() {
  return a20_memory_status();
}

uint8_t a20_enable() {
  uint8_t a20_support = a20_bios_support();
  // Try enabling the a20 line using the BIOS
  if (!(a20_support & A20_BIOS_UNSUPPORTED)){
    a20_bios_enable();
    if (a20_enabled()) return A20_SET_BIOS;
  }
  // Try enabling the a20 line using the output port 0x92
  if (a20_support & A20_BIOS_0x92_SUPPORTED) {
    a20_fast_enable();
    if (a20_enabled()) return A20_SET_FAST;
  }
  // Try enabling the a20 line using the keyboard controller command
  if (a20_support & A20_BIOS_KEYB_SUPPORTED){
    a20_keyb_enable();
    if (a20_enabled()) return A20_SET_KEYB;
  }
  // Fall back to enabling the a20 line using the keyboard controller pin
  a20_keyb_out_enable();
  if (a20_enabled()) return A20_SET_KEYB_OUT;
  else return A20_SET_FAILED;
}

#define A20_TEST_VECTOR 0x500

uint8_t a20_memory_status() {
  uint32_t saved, check;

  set_fs(0x0000);
  set_gs(0xFFFF);
  read_fs_32(A20_TEST_VECTOR, saved);
  write_fs_32(A20_TEST_VECTOR, 0xDEADBABA);
  read_gs_32((A20_TEST_VECTOR+0x10), check);

  write_fs_32(A20_TEST_VECTOR, saved);
  return (check == 0xDEADBABA);
}

void a20_keyb_enable() {
  asm volatile("out %%al, $0x64" :: "a"(0xdd) :);
}

void a20_keyb_wait_output() {
  /**
   * Wait until the keyboard controller output buffer is empty and ready to
   * be written
   */
  uint8_t status;
  do asm volatile("in $0x64, %%al" : "=a"(status) ::); while (!(status & 0x1));
}

void a20_keyb_wait_input() {
  /**
   * Wait until the keyboard controller input buffer is empty and ready to
   * be written
   */
  uint8_t status;
  do asm volatile("in $0x64, %%al" : "=a"(status) ::); while (!(status & 0x2));
}

void a20_keyb_out_enable() {
  /**
   * Enable the a20 line using the keyboard controller's output port.
   * Slightly more complex, but most portable method.
   */
  uint8_t keyb_out_port;
  // send read output port command.
  asm volatile("out %%al, $0x64" :: "a"(0xd0) :);
  a20_keyb_wait_output();

  // read input buffer
  asm volatile("in $0x60, %%al": "=a"(keyb_out_port) ::);
  a20_keyb_wait_input();

  // write output port command
  asm volatile("out %%al, $0x64" :: "a"(0xd1) :);
  a20_keyb_wait_output();

  // write back with flipped bit 2.
  asm volatile("out %%al, $0x60" :: "a"(keyb_out_port | 0x2) :);
}

/**
 * Enable the A20 line using BIOS interrupt 0x15, ah=0x24, al=0x1
 * @return 1 if unsupported, 0 if supported
 */
uint8_t a20_bios_enable() {
  uint16_t status;
  asm volatile("int $0x15" : "=a"(status) : "a"(0x2401) :);
  // AH = 0x86 if not supported, return 1
  return ((status & 0xFF00) == 0x8600) ? 0 : A20_BIOS_UNSUPPORTED;
}

/**
 * Disable the A20 line using BIOS interrupt 0x15, ah=0x24, al=0x1
 * @return 1 if unsupported, 0 if supported
 */
uint8_t a20_bios_disable() {
  uint16_t status;
  asm volatile("int $0x15" : "=a"(status) : "a"(0x2400) :);
  // AH = 0x86 if not supported, return 1
  return ((status & 0xFF00) == 0x8600) ? 0 : A20_BIOS_UNSUPPORTED;
}

/**
 * Check the a20 bios status.
 * @ return 1 if a20 enabled, 0 if a20 disabled.
 */
uint8_t a20_bios_status() {
  uint16_t status;
  asm volatile("int $0x15" : "=a"(status) : "a"(0x2402) :);
  return (uint8_t)(status & 0xFF);
}

/**
 * Check bios a20 bios support.
 */
uint8_t a20_bios_support() {
  uint16_t status;
  uint16_t support;
  asm volatile("int $0x15" : "=a"(status), "=b"(support) : "a"(0x2403) :);
  if ((status & 0xFF) == 0x8600) return A20_BIOS_UNSUPPORTED;
  else return support & (A20_BIOS_KEYB_SUPPORTED | A20_BIOS_0x92_SUPPORTED);
}

void a20_fast_enable() {
  asm volatile(
    "in $0x92, %%al\n"
    "or $0x02, %%al\n"
    "out %%al, $0x92\n"
    :::"ax"
  );
}
