#include <common/code16.h>
#include <common/config.h>
#include <common/common.h>
#include <common/types.h>
#include <stage2/mem.h>
#include <common/multiboot.h>
#ifdef DEBUG
#include <mbr/io.h>
#include <stage2/debug.h>
#endif

#if 0
size_t detect_low_mem() {
  size_t low_mem;
  asm volatile("int $0x12" : "=a"(low_mem) : "a"(0x0):);
  return low_mem;
}
#endif

mb_mmap_t mb_mmap[SMAP_LENGTH / sizeof(smap_entry_t)];

int32_t mem_smap(smap_entry_t *smap_entries, uint32_t max_entries) {
  uint32_t cont_id = 0;
  int32_t entries=0, signature, length;
  do{
    asm volatile(
      "int $0x15"
      : "=a"(signature), "=c"(length), "=b"(cont_id)
      : "a"(0xe820), "b"(cont_id), "c"(0x18), "d"(SMAP_SIGNATURE), "D"(smap_entries));
    if (signature != SMAP_SIGNATURE) return -1;
    if (length > 20 && !(smap_entries->ACPI & 0x1)) {}// Ignore entry for compatibility reasons
    else {
      smap_entries++;
      entries++;
    }
  }
  while(cont_id && entries < max_entries);
  return entries;
}

/**
 * because smap isn't sorted or complete, but rather holy (not in the religious
 * sense, but rather, full of holes), find the amout of memory available from
 * this addr to the next hole.
 * @param addr the base address
 * @param smap the entries returned by mem_smap
 * @param count the number of entries in smap
 * @return the amount of memory available above @p addr in bytes, floored to UINT32_MAX
 */
uint32_t get_avail_from(uint64_t addr, smap_entry_t* smap, uint32_t count) {
  int i = 0;
  uint64_t top = addr;
  for(i = 0; i<count; i++) { // Iterate over all memory segments
    if (
      // check if segment is usable memory
      (smap[i].type == SMAP_REGION_NORMAL)
      // check if segment base is below or equal to addr
      && (smap[i].base <= addr)
      // check if segment top is above or equal to addr
      && ((smap[i].base+smap[i].size) >= addr)
      // check if this is the larger than previous found segments
      && ((smap[i].base+smap[i].size) > top)
      )
      top = smap[i].base+smap[i].size;
  }
  // Floor to UINT32_MAX if more is available
  return ((top-addr)>UINT32_MAX)?UINT32_MAX:(top-addr);
}

void detect_memory(multiboot_t *multiboot) {
#ifdef DEBUG
  puts16("Detecting memory... \n\r");
#endif

  smap_entry_t *smap = (smap_entry_t *) SMAP_BASE;
  int32_t count = mem_smap(smap, SMAP_LENGTH / sizeof(smap_entry_t));

  if (count > 0) {
    // Detect lower memory, startig at 0x0
    multiboot->mem_lower = get_avail_from(0x0, smap, count) / 1024;
    // Detect upper memory, starting at 1MB
    multiboot->mem_upper = get_avail_from(0x100000, smap, count) / 1024;
    // Set the mem flag in the multiboot info struct
    multiboot->flags |= MULTIBOOT_MEM;
#ifdef DEBUG
    puts16("  lower mem:"), dump_uint32(multiboot->mem_lower), puts16(" kiB\n\r");
    puts16("  upper mem:"), dump_uint32(multiboot->mem_upper), puts16(" kiB\n\r");
#endif
    int i;
    for(i=0; i<count; i++) {
      mb_mmap[i] = (mb_mmap_t) {
        .size= 20,
	.addr = smap[i].base,
	.length = smap[i].size,
	.type = smap[i].type
      };
#ifdef DEBUG
      // Print the memory map.
      puts16("  base=0x"), dump_uint64(smap[i].base), puts16(" ");
      puts16("  size=0x"), dump_uint64(smap[i].size), puts16(" ");
      puts16("  type=0x"), dumpb(smap[i].type), puts16("\n\r");
#endif
    } 
    multiboot->mmap_addr = mb_mmap-sizeof(uint32_t); //length offset.
    multiboot->mmap_length = sizeof(mb_mmap_t)*count;
    multiboot->flags |= MULTIBOOT_MMAP;
  } 
  else {
  }
#ifdef DEBUG
  puts16("done.\n\r");
#endif
}
