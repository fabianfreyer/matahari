/* Stage1 is the entry point */
ENTRY(init);

PHDRS {
  headers PT_PHDR PHDRS ;
  interp PT_INTERP ;
  text PT_LOAD FILEHDR PHDRS ;
  data PT_LOAD ;
  dynamic PT_DYNAMIC ;
}

SECTIONS {
  . = 0x7C00;
  /* The stack grows downward from underneath the Stage1 load address. */
  .stack : {
    _stack_base = ABSOLUTE(.)-4;
  } :data
  /* Stage1, a boot sector */
  .text_mbr : AT(0x7C00) {
    _text_mbr = .;
    src/mbr/?*.o (.text.startup);
    src/mbr/?*.o (.text);
    _text_mbr_end = .;
  } :text
  .data_mbr : {
    _data_mbr = .;
    src/mbr/?*.o (.bss);
    src/mbr/?*.o (.bss*);
    src/mbr/?*.o (.data);
    src/mbr/?*.o (.rodata*);
    src/mbr/?*.o (COMMON);
    _data_mbr_end = .;
    ASSERT((_data_mbr_end - _text_mbr) <= 0x200, "mbr too large");
  } :data

  .partition_table : AT(0x7DBE)
  {
    src/mbr/partition_table.o(.partition_table);
  }
  .sig : AT(0x7DFE)
  {
    SHORT(0xAA55);
  }

  . = 0x8000;

  /* Stage2, loaded by Stage1 */
  .text_stage2 : AT(0x8000) {
    _stage2_load_address = ABSOLUTE(.);
    _text_stage2 = .;
    src/stage2/?*.o(.text.startup);
    src/stage2/?*.o(.text);
    _text_stage2 = .;
  } : text
  .data_stage2 (): {
    _data_stage2 = .;
    src/stage2/?*.o(.bss);
    src/stage2/?*.o(.bss*);
    src/stage2/?*.o(.data);
    src/stage2/?*.o(.rodata*);
    src/stage2/?*.o(COMMON);
    _data_stage2_end = .;
    _stage2_end = .;
    _stage2_size = _stage2_end - _stage2_load_address;
  } :data

  /* Discard these sections */
  /DISCARD/ :
  {
    *(.note*);
    *(.iplt*);
    *(.igot*);
    *(.rel*);
    *(.comment*);
    *(.eh_frame*);
  }
  /* Include debug info */
  .debug : { *(.debug*); }
}
