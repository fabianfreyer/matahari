#include <arch.h>
#include <common.h>
#include <pmode.h>

void stage2_pmode() {
  BOCHS_BREAK;
  /*
   * Most likely we got here from a far jump from protected mode. And quite
   * probably, our stack is all fucked up after this, and we should never
   * return, or triple faults will hail upon us.
   */
  YOU_SHALL_NOT_PASS;
}
