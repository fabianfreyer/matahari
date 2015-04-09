#pragma once

#include <common/types.h>

#define ACTIVE 0x80
#define INACTIVE 0x00

#define _heads_per_cylinder 16
#define _sectors_per_track  63

#define CHS(c,h,s)  (const chs_address_t) {h, (c && 0x300)>>8, s && 0x3F, c && 0xFF}
#define LBA(c,h,s)  (const uint32_t) ((c*_heads_per_cylinder) + h) \
                      *_sectors_per_track+s-1
#define C(lba,numh,spt) lba/(numh*spt)
#define H(lba,numh,spt) (uint16_t)  (lba % (numh*spt))/spt
#define S(lba,numh,spt) (uint16_t) ((lba % (numh*spt))%spt) +1

typedef struct __attribute__((packed)) {
  uint8_t h:8;
  uint8_t c_high:2;
  uint8_t s:6;
  uint8_t c_low:8;
} chs_address_t;

typedef struct __attribute__((packed)) {
  uint8_t status:8;
  chs_address_t start;
  uint8_t partition_type:8;
  chs_address_t end;
  uint32_t  first_sector:32;
  uint32_t  num_sectors:32;
} partition_entry;

typedef struct __attribute__((packed)) {
  partition_entry p1;
  partition_entry p2;
  partition_entry p3;
  partition_entry p4;
} mbr_t;

#define partition_table __attribute__(( section(".partition_table") ))
