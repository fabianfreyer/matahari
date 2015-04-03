#pragma once

#define A20_BIOS_KEYB_SUPPORTED (1<<0)
#define A20_BIOS_0x92_SUPPORTED (1<<1)
#define A20_SET_BIOS (1<<2)
#define A20_SET_FAST (1<<3)
#define A20_SET_KEYB (1<<4)
#define A20_SET_KEYB_OUT (1<<5)
#define A20_SET_FAILED (1<<6)
#define A20_BIOS_UNSUPPORTED (1<<7)

unsigned char a20_enabled();
unsigned char a20_memory_status();
unsigned char a20_bios_status();
unsigned char a20_bios_enable();
unsigned char a20_bios_disable();
unsigned char a20_bios_support();
void a20_fast_enable();
void a20_keyb_out_enable();
void a20_keyb_enable();
unsigned char a20_enable();
