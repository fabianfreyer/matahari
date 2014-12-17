#pragma once

#include <partition_table.h>
extern mbr_t mbr;

char get_bios_drive();

typedef struct {
  unsigned char spt;
  unsigned char heads;
} drive_geom;

int __attribute__((noinline)) get_drive_geom(
    drive_geom *g, unsigned char drive);

void __attribute__((noinline)) lba_read(
  const void *buffer, unsigned int lba, unsigned char blocks,
  drive_geom *g, unsigned char drive);
unsigned char __attribute__((noinline)) chs_read(
  const void *buffer,
  unsigned char cylinder,
  unsigned char head,
  unsigned short sector,
  unsigned char blocks,
  unsigned char drive);


