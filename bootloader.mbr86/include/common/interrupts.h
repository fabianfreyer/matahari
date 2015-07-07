#pragma once

inline void disable_interrupts() { asm volatile ("cli"); }
inline void enable_interrupts() { asm volatile ("sti"); }
inline void disable_nmi() { asm volatile ("out %%al, $0x70":: "a"((uint8_t) 0x80):); }
inline void enable_nmi() { asm volatile ("out %%al, $0x70":: "a"((uint8_t) 0x00):); }
inline void ireturn() {asm volatile ("leave\n iret");}
