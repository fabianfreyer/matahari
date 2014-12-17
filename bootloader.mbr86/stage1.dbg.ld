ENTRY(main);
SECTIONS {
  . = 0x7C00;
  .text : AT(0x7C00) {
    _text = .;
    *(.text.startup);
    *(.text);
    _text_end = .;
  } 
  .data : {
    _data = .;
    *(.bss);
    *(.bss*);
    *(.data);
    *(.rodata*);
    *(COMMON);
    _data_end = .;
  }
  .partition_table : AT(0x7DBE)
  {
    *(.partition_table);
  }
  .sig : AT(0x7DFE)
  {
    SHORT(0xAA55);
  }
  /DISCARD/ :
  {
    *(.note*);
    *(.iplt*);
    *(.igot*);
    *(.rel*);
    *(.comment*);
    *(.eh_frame*);
  }

}
