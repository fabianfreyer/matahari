#pragma once

#define DEBUG

/**
 * Stage1 Data
 */
#define STAGE1_BASE 0x7C00


/**
 * \defgroup stage2_config Stage2 configuration data
 * @{
 */

/**
 * stage2 base adress. This is where stage2 will be loaded.
 */
#define STAGE2_BASE 0x1000

/**
 * CHS Adress of Stage2
 * @{
 */
#define STAGE2_CYLINDER 0
#define STAGE2_HEAD 0
#define STAGE2_SECTOR 2
/**@}*/

/**
 * Length of Stage2 in sectors
 */
#define STAGE2_LENGTH 2

/**@}*/

#define _define_wrap(x) do { x } while(0)

#define BOCHS_BREAK _define_wrap(asm volatile ("xchgw %bx, %bx");)
#define YOU_SHALL_NOT_PASS _define_wrap(while(1) {}; )
