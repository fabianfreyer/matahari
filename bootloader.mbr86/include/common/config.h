#pragma once
#include <common/types.h>

#define DEBUG

/**
 * \defgroup stage2_config Stage2 configuration data
 * @{
 */

/**
 * stage2 base adress. This is where stage2 will be loaded.
 */
#define SMAP_BASE 0x7000
#define SMAP_LENGTH 0xB00

/**
 * CHS Adress of Stage2
 * @{
 */
#define STAGE2_CYLINDER 0
#define STAGE2_HEAD 0
#define STAGE2_SECTOR 2
/**@}*/

/**@}*/

#define _define_wrap(x) do { x } while(0)

#define BOCHS_BREAK _define_wrap(asm volatile ("xchgw %bx, %bx");)
#define YOU_SHALL_NOT_PASS _define_wrap(while(1) {}; )
