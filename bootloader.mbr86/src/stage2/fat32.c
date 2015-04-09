#include <common/code16.h>
#include <common/types.h>
#include <common/common.h>
#include <common/config.h>
#include <common/partition_table.h>

#include <stage2/fat32.h>
#include <mbr/disk.h>

#ifdef DEBUG
#include <mbr/io.h>
#include <stage2/debug.h>
#endif

#if 0
static uint32_t first_usable_cluster (uint32_t base_lba, fat32_mbr_t *fs) {
  return base_lba + fs->reserved_sectors + (fs->fats * fs->sectors_per_fat);
}

static uint64_t fat32_cluster2lba(uint32_t base_lba, uint32_t cluster, fat32_mbr_t *fs) {
  return + first_usable_cluster(base_lba, fs) + cluster * fs->cluster_size - (2 * fs->cluster_size);
}
#endif
void fat32_init(uint8_t bios_drive, uint8_t partition) {
  mbr_t *partt = (mbr_t*) (0x7c00 + 446);
#ifdef DEBUG
  puts16("Initializing FAT32 driver... ");
#endif
  partition_entry *part = (partition_entry*) partt + partition*sizeof(partition_entry);
#ifdef DEBUG
  dump_uint32(LBA(((part->start.c_high<<8)&part->start.c_low), part->start.h, part->start.s));
#endif
}
