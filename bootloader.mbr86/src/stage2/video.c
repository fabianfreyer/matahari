#include <common/arch.h>
#include <common/config.h>

#include <drivers/video.h>

typedef struct {
  int8_t line;
  int8_t column;
} cursor_position_t;

typedef struct __attribute__((__packed__)) {
  char ascii;
  uint8_t attr;
} screen_character_t;

/*
 * Define a static cursor and screen size
 */
static cursor_position_t cursor_position = {0, 0};
static cursor_position_t screen_size = {25,80};

#ifndef PMODE
screen_character_t* video_init() {
#ifdef ARCH_x86
  /*
   * Get the video memory pointer, depending on detected hardware.
   */
  const uint16_t *bda_detected_hardware = (const uint16_t *) 0x410;
  switch (*bda_detected_hardware & 0x30) {
    case 0x20: // color 80x25
      return (screen_character_t*) 0xB8000;
      break;
    case 0x10: // monochrome 40x25
      screen_size.column=40;
    case 0x30: // monocrhome 80x25
      return (screen_character_t*) 0xB0000;
      break;
    default:   // video not supported
      return (screen_character_t*) 0x0;
  }
#else
#warning video_init not implemented for arch.
  return 0x0;
#endif
}

void puts32_color(uint8_t color, const char *string ){
  volatile screen_character_t* video = video_init();
  // Write a string
  if(video) {
    do {
      // Calculate offset
      uint16_t offset = (cursor_position.line * screen_size.column + cursor_position.column);
      switch(*string) {
      case '\n':
        cursor_position.line++;
      case '\r':
	cursor_position.column = 0;
        break;
      default:
        // Write to video memory
        (video+offset)->ascii = *string;
        (video+offset)->attr = color;
        // Move the cursor position
        cursor_position.column++;
        if(cursor_position.column == 80) {
          // Line break at the end of a line
          cursor_position.column = 0;
          cursor_position.line++;
        }
      }
    }
    while( *(string++) != 0 ); 
  }
}
#endif
