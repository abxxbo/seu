# Checklist of features needed for SEU

## Release 0.0.1

### Bootloader
- [X] A more friendly GUI for the bootloader

### Kernel
- [X] Heap/Memory Management
- [ ] Rendering text in a different font than the original VGA font
- [X] Implement VFS
- [ ] Read from one of the following:
	- NVMe, AHCI, ATA
- [X] Library to output to QEMU's serial
- [X] Multitasking
- [ ] Shell
	- NOTE: This task can only be done if SFS or any other FS is implemented.
