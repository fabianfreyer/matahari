/* Stage1 is the entry point */
ENTRY(main);

PHDRS {
  headers PT_PHDR PHDRS ;
  interp PT_INTERP ;
  text PT_LOAD FILEHDR PHDRS ;
  data PT_LOAD ;
  dynamic PT_DYNAMIC ;
}

SECTIONS {
  . = 0x7C00;
  /* Stage1, a boot sector */
  .text_mbr : AT(0x7C00) {
    _text_mbr = .;
    build32/mbr/?*.o (.text.startup);
    build32/mbr/?*.o (.text);
    _text_mbr_end = .;
  } :text
  .data_mbr : {
    _data_mbr = .;
    build32/mbr/?*.o (.bss);
    build32/mbr/?*.o (.bss*);
    build32/mbr/?*.o (.data);
    build32/mbr/?*.o (.rodata*);
    build32/mbr/?*.o (COMMON);
    _data_mbr_end = .;
  } :data
  .partition_table : AT(0x7DBE)
  {
    build32/mbr/partition_table.o(.partition_table);
  }
  .sig : AT(0x7DFE)
  {
    SHORT(0xAA55);
  }

  . = 0x1000;
  /* Stage2, loaded by Stage1 */
  .text_stage2 : AT(0x1000) {
    _stage2_load_adress = .;
    _text_stage2 = .;
    build32/stage2/?*.o(.text.startup);
    build32/stage2/?*.o(.text);
    _text_stage2 = .;
  } : text
  .data_stage2 (): {
    _data_stage2 = .;
    build32/stage2/?*.o(.bss);
    build32/stage2/?*.o(.bss*);
    build32/stage2/?*.o(.data);
    build32/stage2/?*.o(.rodata*);
    build32/stage2/?*.o(COMMON);
    _data_stage2_end = .;
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
