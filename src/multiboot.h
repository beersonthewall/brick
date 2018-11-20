#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

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

typedef struct map_entry map_entry;
typedef struct memory_map memory_map;
struct memory_map {
  uint32_t type;
  uint32_t size;
  uint32_t entry_sz;
  uint32_t entry_v;
  map_entry* first;
};

struct map_entry {
  uint64_t base;
  uint64_t length;
  uint64_t type;
  uint32_t res;
};

void* get_tag(enum tag tg, uint32_t* multiboot);

#endif