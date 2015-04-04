#pragma once
#include <common/config.h>
#include <common/types.h>

#define MULTIBOOT_MAGIC 0x2BADB002
#define MULTIBOOT_MEM (1<<0)
#define MULTIBOOT_BOOT_DEVICE (1<<1)
#define MULTIBOOT_CMDLINE (1<<2)
#define MULTIBOOT_MODS (1<<3)
#define MULTIBOOT_AOUT (1<<4)
#define MULTIBOOT_ELF (1<<5)
#define MULTIBOOT_MMAP (1<<6)
#define MULTIBOOT_DRIVES (1<<7)
#define MULTIBOOT_CONFIG_TABLE (1<<8)
#define MULTIBOOT_BOOT_LOADER_NAME (1<<9)
#define MULTIBOOT_APM_TABLE (1<<10)
#define MULTIBOOT_GRAPHICS (1<<11)

typedef struct {
  uint32_t tabsize;
  uint32_t strsize;
  void* addr;
  uint32_t reserved;
} __attribute__((packed)) mb_aout_sym_table_t;

typedef struct {
  uint32_t num;
  size_t size;
  void* addr;
  uint32_t shndx;
} __attribute__((packed)) mb_elf_sect_table_t;

typedef struct {
  void* mod_start;
  void* mod_end;
  char* string;
  uint32_t reserved;
} __attribute__((packed)) mb_mod_t;

typedef struct {
  uint32_t size;
  uint64_t addr;
  uint64_t length;
  uint32_t type;
} __attribute__((packed)) mb_mmap_t;

typedef struct {
  size_t size;
  uint8_t drive_number;
  uint8_t drive_mode;
  uint8_t drive_cylinders;
  uint8_t drive_heads;
  uint8_t drive_sectors;
  uint8_t drive_ports[];
} __attribute((packed)) mb_drive_t;

typedef struct {
  uint32_t flags;
  uint32_t mem_lower;
  uint32_t mem_upper;
  uint32_t boot_device;
  char* cmdline;
  size_t mods_count;
  mb_mod_t* motds_addr;
  union{
    mb_aout_sym_table_t aout_sym_table;
    mb_elf_sect_table_t elf_sect_table;
  } syms;
  uint32_t mmap_length;
  mb_mmap_t* mmap_addr;
  uint32_t drives_length;
  void* drives_addr;
  uint32_t config_table;
  char* boot_loader_name;
  uint32_t apm_table;
  uint32_t vbe_control_info;
  uint32_t vbe_mode_info;
  uint16_t vbe_mode;
  uint16_t vbe_interface_seg;
  uint16_t vbe_interface_off;
  uint16_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;

