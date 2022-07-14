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
`make execute`.