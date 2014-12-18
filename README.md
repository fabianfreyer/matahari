Matahari
========

This is a toy osdev project.
The aim is to write a boot loader and kernel from scratch.

At the moment, it's more a basic build environment for osdev projects. It includes scripts to build and install a cross-toolchain and a Makefile that takes care of everything.
Works on OS X and Linux.

Components
----------
The following components exist, possibly in other branches:
- bootloader.mbr86

Building
--------
The following build targets exist for the base environment
- toolchain

Dependencies
------------
- GNU `coreutils`
- `wget`
- `gcc`

Debugging
---------
The makefile contains a debug targets for some components. The choice of the debugger is made using the `DEBUGGER` variable. `GDB` and `NEMIVER` are currently supported.

    make DEBUGGER=GDB bootloader.mbr86-debug
  
