#pragma once
#include <common/config.h>

#ifdef DEBUG
void dumpb(uint8_t byte);
void dump(void *addr, uint32_t count);
void dump_uint64(uint64_t val);
void dump_uint32(uint32_t val);
void dump_uint16(uint32_t val);
#endif
