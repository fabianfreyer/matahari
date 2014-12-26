#pragma once

#define DEFAULT_COLOR 0x06
#define puts32(str) puts32_color(DEFAULT_COLOR, str)
void puts32_color(unsigned char color, const char *string );
typedef struct __attribute__((__packed__)) {
  unsigned bold :1;
  unsigned bg   :3;
  unsigned fg   :4;
} color_t;

