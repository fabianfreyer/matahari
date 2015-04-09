#pragma once

#include <common/types.h>

typedef struct {
  char name[8];
  char ext[3];
  uint8_t attrib;
  uint8_t userattrib;
  char undelete;
  uint16_t createtime;
  uint16_t createdate;
  uint16_t accessdate;
  uint16_t clusterhigh;
  uint16_t modifiedtime;
  uint16_t modifieddate;
  uint16_t clusterlow;
  uint32_t filesize;
} __attribute__((packed)) fat32_dirent_t;

/**
 * FAT32 MBR
 */
typedef struct __attribute__((packed)) {
  uint8_t jmp_code[3];
  char oem_name[8];
  uint16_t sector_size;
  // cluster size in sectors per cluster
  uint8_t cluster_size;
  uint16_t reserved_sectors;
  // number of FATs
  uint8_t fats;
  uint16_t root_entries;
  uint16_t sectors;
  uint8_t media_descriptor;
  // fat size in sectors
  uint16_t sectors_per_fat;
  // track size in sectors
  uint16_t sectors_per_track;
  // Head size in sectors
  uint16_t sectors_per_head;
  // Number of hidden sectors
  uint32_t hidden_sectors;
  uint32_t total_sectors;
  uint32_t bigsectors_per_fat;
  uint16_t flags;
  uint16_t fs_version;
  uint32_t root_directory_start;
  uint16_t fs_info_sector;
  uint16_t backup_boot_sector;
  uint8_t reserved_0[12];
  uint8_t bios_drive;
  uint8_t reserved_1;
  uint8_t signature;
  uint32_t serial_number;
  uint8_t volume_label[11];
  uint8_t system_identifier[8];
} __attribute__((packed)) fat32_mbr_t;

void fat32_init(uint8_t bios_drive, uint8_t partition); 
