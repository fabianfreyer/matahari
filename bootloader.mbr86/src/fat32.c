typedef struct __attribute__((packed)) {
  char filename[11];
  char attr                 :8;
  char reserved[10];
  unsigned short created    :16;
  unsigned short file_date  :16;
  unsigned short cluster    :16;
  unsigned int length       :32;
} fat_entry_t;

typedef struct __attribute__((packed)) {
  unsigned int jmp_code                 :24; //3
  char oem_name[8];                          //8
  unsigned short sector_size            :16; //2
  unsigned char cluster_size            : 8; //1
  unsigned short reserved_sectors       :16; //2
  unsigned char fats                    : 8; //1
  unsigned short root_entries           :16; //2
  unsigned short sectors                :16; //2
  unsigned char media_descriptor        : 8; //1
  unsigned short sectors_per_fat        :16; //2
  unsigned short sectors_per_track      :16; //2
  unsigned short sectors_per_head       :16; //2
  unsigned int hidden_sectors           :32; //4
  unsigned int total_sectors            :32; //4
  unsigned int bigsectors_per_fat       :32; //4
  unsigned short flags                  :16; //2
  unsigned short fs_version             :16; //2
  unsigned int root_directory_start     :32; //4
  unsigned short fs_info_sector         :16; //2
  unsigned short backup_boot_sector     :16; //2
  unsigned char reserved_0[12];            
  unsigned char bios_drive              : 8;
  unsigned char reserved_1              : 8;
  unsigned char signature               : 8;
  unsigned int serial_number            :32;
  unsigned char volume_label[11];
  unsigned char system_identifier[8];
} fat_mbr;


