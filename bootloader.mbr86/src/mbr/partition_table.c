#include <common/partition_table.h>

mbr_t partition_table mbr = {
  .p1 = {
    .status = ACTIVE,
    .start = CHS(0,0,63),
    .end = CHS(1,0,1),
    .partition_type = 0x0B, //Fat32
    .first_sector = 62,
    .num_sectors = 946
  },
  .p2 = {
    .status = ACTIVE,
    .start = CHS(0,0,63),
    .end = CHS(1,0,1),
    .partition_type = 0x0B, //Fat32
    .first_sector = 62,
    .num_sectors = 946
  },
};
