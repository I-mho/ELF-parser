#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
        unsigned char e_magic[16]; // Magic(elf identity, 7f E L F 02 01 01 00 ..)
        uint16_t e_type; // Type
        uint16_t e_machine; // Machine
        uint32_t e_version; // Version
        uint64_t e_entry; // Entry Point
        uint64_t e_phoff; // Program header file offset
        uint64_t e_shoff; // Section header file offset
        uint32_t e_flags;
        uint16_t e_ehsize;
        uint16_t e_phentsize; // Program header table entry size
        uint16_t e_phnum; // Number of program headers
        uint16_t e_shentsize; // Section header table entry size
        uint16_t e_shnum; // Number of section headers
        uint16_t e_shstrndx; // Section header string table index
} Elf_hdr;

typedef struct {
        uint32_t sh_name; // .name
        uint32_t sh_type;
        uint64_t sh_flags;
        uint64_t sh_addr; // vaddr
        uint64_t sh_offset; // file offset
        uint64_t sh_size; // size
        uint32_t sh_link;
        uint32_t sh_info;
        uint64_t sh_addralign;
        uint64_t sh_entsize;
} Elf_shdr;

int parse_elf_header(FILE *file, Elf_hdr *elf_hdr) {
        fread(elf_hdr, 1, sizeof(Elf_hdr), file);

        if (elf_hdr->e_magic[0] != 0x7f || elf_hdr->e_magic[1] != 'E' || elf_hdr->e_magic[2] != 'L' || elf_hdr->e_magic[3] != 'F')
        {
                printf("This file is not a valid ELF file\n");
                return 1;
        }
}

void parse_section_header(FILE *file, const Elf_hdr *elf_hdr, Elf_shdr *section_hdr) {
        fseek(file, elf_hdr->e_shoff, SEEK_SET);
        fread(section_hdr, elf_hdr->e_shnum, sizeof(Elf_shdr), file);
}

void print_elf_header(const Elf_hdr *elf_hdr) {
        printf("[*] ELF header\n");

        printf("Magic: ");
        for (int i = 0; i < 16; i++) { printf("%02x ", elf_hdr->e_magic[i]); }
        printf("\n");
        printf("Type: %u\n", elf_hdr->e_type);
        printf("Machine: %u\n", elf_hdr->e_machine);
        printf("Version: %lu\n", elf_hdr->e_version);
        printf("Entry point: 0x%lx\n", elf_hdr->e_entry);
        printf("Program header file offset: 0x%lx\n", elf_hdr->e_phoff);
        printf("Number of program headers: %u\n", elf_hdr->e_phnum);
        printf("Program header table entry size: %u\n", elf_hdr->e_phentsize);
        printf("Section header file offset: 0x%lx\n", elf_hdr->e_shoff);
        printf("Number of section headers: %u\n", elf_hdr->e_shnum);
        printf("Section header table entry size: %u\n", elf_hdr->e_shentsize);
        printf("Section header string table index: %u\n", elf_hdr->e_shstrndx);
}

void print_section_header_table(const Elf_shdr *section_hdr, int shnum, const char *section_name) {
        printf("[*] Section header table\n");

        for (int i = 1; i < shnum; i++) {
                printf("%d. %-10s\tsize: %-10u\tvaddr: 0x%-10x\tfile offset: 0x%-10x\n", i, section_name + section_hdr[i].sh_name, section_hdr[i].sh_size, section_hdr[i].sh_addr, section_hdr[i].sh_offset);
        }
}

int main(int argc, char *argv[]) {
        int fd;

        // command execution exception
        if (argc != 2) {
                printf("Usage: ./parser <path to file>\n");
                return 1;
        }

        FILE *file = fopen(argv[1], "rb");
        if (!file) {
                return 1;
        }

        // ELF header
        Elf_hdr elf_hdr;
        parse_elf_header(file, &elf_hdr);
        print_elf_header(&elf_hdr);

        printf("\n");

        // Section header table
        fseek(file, elf_hdr.e_shstrndx * elf_hdr.e_shentsize + elf_hdr.e_shoff, SEEK_SET);

        Elf_shdr shstrtab;
        fread(&shstrtab, 1, sizeof(Elf_shdr), file);
        char *section_name = (char *)malloc(shstrtab.sh_size);

        fseek(file, shstrtab.sh_offset, SEEK_SET);
        fread(section_name, 1, shstrtab.sh_size, file);

        Elf_shdr *section_hdr = (Elf_shdr *)malloc(elf_hdr.e_shentsize * elf_hdr.e_shnum);
        parse_section_header(file, &elf_hdr, section_hdr);
        print_section_header_table(section_hdr, elf_hdr.e_shnum, section_name);

        free(section_name);
        free(section_hdr);
        fclose(file);
        return 0;
}