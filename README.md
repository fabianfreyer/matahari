Matahari
========

This is a toy osdev project.
The aim is to write a boot loader and kernel from scratch.

At the moment, it's more a basic build environment for osdev projects. It
includes scripts to build and install a cross-toolchain.
Works on OS X and Linux.

Components
----------
The following components exist, possibly in other branches:
- bootloader.mbr86

Building
--------
To build the bootloader, install a ct-ng toolchain:

    $ tools/run install-ct-ng

This downloads and builds the cross-toolchain required to build the bootloader.

Build all other components using SCons:

    $ scons

Dependencies
------------
- GNU `coreutils`
- `wget`
- `gcc`
- `SCons`

Debugging
---------

A `bochsrc.txt` is provided.
