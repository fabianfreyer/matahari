#include <common/partition_table.h>

mbr_t partition_table mbr = {
  .p1 = {
    .status = ACTIVE,
    .start = CHS(0,1,1),
    .end = CHS(1023,254,63),
    .partition_type = 0x0B, //Fat32
    .first_sector = 63,
    .num_sectors = 131009
  }
};
