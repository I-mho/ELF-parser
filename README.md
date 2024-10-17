## Environment
ubuntu 22.04 or else

## Compile
```bash
gcc -o parse parse.c
```

## Usage
```bash
./parser <path to file>
```

## Example
```bash
$ ./parse ./example
[*] ELF header
Magic: 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
Type: 3
Machine: 62
Version: 1
Entry point: 0x1040
Program header file offset: 0x40
Number of program headers: 13
Program header table entry size: 56
Section header file offset: 0x36a0
Number of section headers: 29
Section header table entry size: 64
Section header string table index: 28

[*] Section header table
1. .interp      size: 28                vaddr: 0x318            file offset: 0x318
2. .note.gnu.property   size: 48                vaddr: 0x338            file offset: 0x338
3. .note.gnu.build-id   size: 36                vaddr: 0x368            file offset: 0x368
4. .note.ABI-tag        size: 32                vaddr: 0x38c            file offset: 0x38c
5. .gnu.hash    size: 36                vaddr: 0x3b0            file offset: 0x3b0
6. .dynsym      size: 144               vaddr: 0x3d8            file offset: 0x3d8
7. .dynstr      size: 136               vaddr: 0x468            file offset: 0x468
8. .gnu.version size: 12                vaddr: 0x4f0            file offset: 0x4f0
9. .gnu.version_r       size: 48                vaddr: 0x500            file offset: 0x500
10. .rela.dyn   size: 192               vaddr: 0x530            file offset: 0x530
11. .init       size: 27                vaddr: 0x1000           file offset: 0x1000
12. .plt        size: 16                vaddr: 0x1020           file offset: 0x1020
13. .plt.got    size: 16                vaddr: 0x1030           file offset: 0x1030
14. .text       size: 412               vaddr: 0x1040           file offset: 0x1040
15. .fini       size: 13                vaddr: 0x11dc           file offset: 0x11dc
16. .rodata     size: 4                 vaddr: 0x2000           file offset: 0x2000
17. .eh_frame_hdr       size: 36                vaddr: 0x2004           file offset: 0x2004
18. .eh_frame   size: 112               vaddr: 0x2028           file offset: 0x2028
19. .init_array size: 8                 vaddr: 0x3df0           file offset: 0x2df0
20. .fini_array size: 8                 vaddr: 0x3df8           file offset: 0x2df8
21. .dynamic    size: 448               vaddr: 0x3e00           file offset: 0x2e00
22. .got        size: 64                vaddr: 0x3fc0           file offset: 0x2fc0
23. .data       size: 16                vaddr: 0x4000           file offset: 0x3000
24. .bss        size: 8                 vaddr: 0x4010           file offset: 0x3010
25. .comment    size: 43                vaddr: 0x0              file offset: 0x3010
26. .symtab     size: 888               vaddr: 0x0              file offset: 0x3040
27. .strtab     size: 471               vaddr: 0x0              file offset: 0x33b8
28. .shstrtab   size: 268               vaddr: 0x0              file offset: 0x358f
```