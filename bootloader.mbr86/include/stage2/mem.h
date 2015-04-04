#pragma once
#include <common/types.h>
#include <common/multiboot.h>

#define SMAP_SIGNATURE 0x534D4150
#define SMAP_REGION_NORMAL 1
#define SMAP_REGION_RESERVED 2
#define SMAP_REGION_ACPI_RECLAIMABLE 3
#define SMAP_REGION_ACPI_NVS 4
#define SMAP_REGION_BAD 5

typedef struct {
  uint64_t base;
  uint64_t size;
  uint32_t type;
  uint32_t ACPI;
} __attribute__((packed)) smap_entry_t;

size_t detect_low_mem();
uint32_t mem_map(smap_entry_t *smap_entries, uint32_t max_entries); 
void detect_memory(multiboot_t *multiboot);
