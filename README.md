# SEU
A x86_32 hobbyist operating system

**Disclaimer:** some code, like the IDT/GDT code is based off of [JamesM's tutorial](http://www.jamesmolloy.co.uk/tutorial_html/). Everything else is written by me.

## Compilation
Dependencies:
- i386-elf-gcc (see [OSDev Wiki - GCC Cross Compiler](https://wiki.osdev.org/GCC_Cross-Compiler))
- an install of grub
- xorriso
- mtools
- nasm

Once all these dependencies are installed, run `make`. To run in qemu, use
`make execute`. (note: you can run `make run`, since that is an alias to
`make execute`).


## Burning to an ISO
**Prerequisite:** Compile the ISO via `make`.

### Find your disk
First, you need to find the disk, on Linux, you can either do:
- `fdisk -l`
- `lsblk`

### Write to the disk
Now, using dd, you can do this
```sh
# Make sure you have the correct drive, dd will format the *ENTIRE*
# disk!
sudo dd if=./seu.iso of=[DRIVE (e.g. /dev/sda)] # bs=4M 
# last argument, bs=4M, optional.
```