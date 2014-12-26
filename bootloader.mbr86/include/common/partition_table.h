#pragma once

#define ACTIVE 0x80
#define INACTIVE 0x00

#define heads_per_cylinder 16
#define sectors_per_track  63

#define CHS(c,h,s)  (const chs_address_t) {h, (c && 0x300)>>8, s && 0x3F, c && 0xFF}
#define LBA(c,h,s)  (const unsigned int) ((c*heads_per_cylinder) + h) \
                      *sectors_per_track+s-1
#define C(lba,numh,spt) lba/(numh*spt)
#define H(lba,numh,spt) (unsigned short)  (lba % (numh*spt))/spt
#define S(lba,numh,spt) (unsigned short) ((lba % (numh*spt))%spt) +1

typedef struct __attribute__((packed)) {
  unsigned char h:8;
  unsigned char c_high:2;
  unsigned char s:6;
  unsigned char c_low:8;
} chs_address_t;

typedef struct __attribute__((packed)) {
  unsigned char status:8;
  chs_address_t start;
  unsigned char partition_type:8;
  chs_address_t end;
  unsigned int  first_sector:32;
  unsigned int  num_sectors:32;
} partition_entry;

typedef struct __attribute__((packed)) {
  partition_entry p1;
  partition_entry p2;
  partition_entry p3;
  partition_entry p4;
} mbr_t;

#define partition_table __attribute__(( section(".partition_table") ))
