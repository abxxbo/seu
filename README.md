# SEU
A x86_32 hobbyist operating system with a homebrew bootloader and libc.

**Disclaimer:** some code, like the IDT/GDT code is based off of [JamesM's tutorial](http://www.jamesmolloy.co.uk/tutorial_html/). Everything else is written by me.

## Compilation
Dependencies:
- i386-elf-gcc (see [OSDev Wiki - GCC Cross Compiler](https://wiki.osdev.org/GCC_Cross-Compiler))
- binutils (`ld` and `cat`)
- nasm

Once all these dependencies are installed, run `make`. To run in qemu, use
`make execute`. (note: you can run `make run`, since that is an alias to
`make execute`).