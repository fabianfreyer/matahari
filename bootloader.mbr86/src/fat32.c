#include <common/types.h>

typedef struct __attribute__((packed)) {
  char filename[11];
  uint8_t attr                 :8;
  uint8_t reserved[10];
  uint16_t created    :16;
  uint16_t file_date  :16;
  uint16_t cluster    :16;
  uint32_t length       :32;
} fat_entry_t;

typedef struct __attribute__((packed)) {
  uint32_t jmp_code                 :24; //3
  char oem_name[8];                          //8
  uint16_t sector_size            :16; //2
  uint8_t cluster_size            : 8; //1
  uint16_t reserved_sectors       :16; //2
  uint8_t fats                    : 8; //1
  uint16_t root_entries           :16; //2
  uint16_t sectors                :16; //2
  uint8_t media_descriptor        : 8; //1
  uint16_t sectors_per_fat        :16; //2
  uint16_t sectors_per_track      :16; //2
  uint16_t sectors_per_head       :16; //2
  uint32_t hidden_sectors           :32; //4
  uint32_t total_sectors            :32; //4
  uint32_t bigsectors_per_fat       :32; //4
  uint16_t flags                  :16; //2
  uint16_t fs_version             :16; //2
  uint32_t root_directory_start     :32; //4
  uint16_t fs_info_sector         :16; //2
  uint16_t backup_boot_sector     :16; //2
  uint8_t reserved_0[12];
  uint8_t bios_drive              : 8;
  uint8_t reserved_1              : 8;
  uint8_t signature               : 8;
  uint32_t serial_number            :32;
  uint8_t volume_label[11];
  uint8_t system_identifier[8];
} fat_mbr;


