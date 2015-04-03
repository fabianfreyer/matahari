#pragma once

#include <common/partition_table.h>
extern mbr_t mbr;

char get_bios_drive();

typedef struct {
  uint8_t spt;
  uint8_t heads;
} drive_geom;

int32_t __attribute__((noinline)) get_drive_geom(
    drive_geom *g, uint8_t drive);

void __attribute__((noinline)) lba_read(
  const void *buffer, uint32_t lba, uint8_t blocks,
  drive_geom *g, uint8_t drive);
uint8_t __attribute__((noinline)) chs_read(
  const void *buffer,
  uint8_t cylinder,
  uint8_t head,
  uint16_t sector,
  uint8_t blocks,
  uint8_t drive);


