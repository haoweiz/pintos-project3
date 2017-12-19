#ifndef PAGE_H
#define PAGE_H

#include "filesys/filesys.h"
#include "threads/palloc.h"
#include <list.h>

struct spt_elem{
  int code_or_data;
  uint8_t *user_page;
  struct file *file;
  off_t ofs;
  bool writable;
  uint32_t read_bytes;
  uint32_t zero_bytes;
  struct list_elem elem;
};

struct list_elem *find_spte(void *fault_addr);
bool load_from_file(struct spt_elem *spte);

#endif 
