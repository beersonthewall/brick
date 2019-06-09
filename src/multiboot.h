#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

/*
 * Contains structures for interacting with the multiboot information provided
 * by a multiboot compliant bootloader.
 */

enum tag {
  BOOT_CMD_LINE = 1,
  NAME = 2,
  MODULES = 3,
  BASIC_MEM_INFO = 4,
  BIOS_BOOT_DEV = 5,
  MEM_MAP = 6,
  VBE_INFO = 7,
  FRAME_BUF_INFO = 8,
  ELF_SYMBOLS = 9,
  APM_TABLE = 10,
  EFI_SYS_TBL_32 = 11,
  EFI_SYS_TBL_64 = 12,
  SMBIOS = 13,
  OLD_RSDP = 14,
  NEW_RSDP = 15,
  NETWORK = 16,
  EFI_MEM_MAP = 17,
  EFI_NOT_TERM = 18,
  EFI_IMG_HNDL_32 = 19,
  EFI_IMG_HNDL_64 = 20,
  IMG_LOAD_BASE = 21,
};

typedef struct basic_mem_info basic_mem_info;
struct basic_mem_info {
  uint32_t type;
  uint32_t size;
  uint32_t mem_lower;
  uint32_t mem_upper;
};

typedef struct map_entry map_entry;
struct map_entry {
  uint64_t base;
  uint64_t length;
  uint32_t type;
  uint32_t res; // reserved space, should be zero.
};

typedef struct memory_map memory_map;
struct memory_map {
  uint32_t type;
  uint32_t size;
  uint32_t entry_sz;
  uint32_t entry_v;
  struct map_entry entries[0];
};

typedef struct elf_section_header elf_section_header;
struct elf_section_header {
  uint32_t sh_name_index;
  uint32_t sh_type;
  uint64_t sh_flags;
  uint64_t sh_addr;
  uint64_t sh_offset;
  uint64_t sh_size;
  uint32_t sh_link;
  uint32_t sh_info;
  uint64_t sh_addralign;
  uint64_t sh_entsize;
};

typedef struct elf_symbols elf_symbols;
struct elf_symbols {
  uint32_t type;
  uint32_t size;
  uint16_t num;
  uint16_t entsize;
  uint16_t shndx;
  uint16_t res;
  elf_section_header* sh_table;
};

void* get_tag(enum tag tg, uint32_t* multiboot);

#endif
