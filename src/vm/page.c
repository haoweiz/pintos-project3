#include "vm/page.h"
#include "threads/vaddr.h"
#include "threads/thread.h"
#include "filesys/file.h"
#include "userprog/process.h"
#include <list.h>
#include <string.h>
#include <stdio.h>

struct list_elem *find_spte(void *fault_addr){
  void *upage = pg_round_down(fault_addr);
  struct list_elem *e;
  for(e = list_begin(&thread_current()->sup_page_table);
      e != list_end(&thread_current()->sup_page_table);
      e = list_next(e))
  {
    if(list_entry(e,struct spt_elem,elem)->user_page == upage)
      return e;
  }
  return NULL;
}


bool load_from_file(struct spt_elem *spte){
    /* Get a page of memory. */
  uint8_t *kpage = palloc_get_page (PAL_USER);
  if (kpage == NULL){
    return false;
  }
      

    /* Load this page. */
  if (file_read_at (spte->file, kpage, spte->read_bytes, spte->ofs) != (int) spte->read_bytes){
    palloc_free_page (kpage);
    return false; 
  }
  memset (kpage + spte->read_bytes, 0, spte->zero_bytes);
      

    /* Add the page to the process's address space. */
  if (!install_page (spte->user_page, kpage, spte->writable)){
    palloc_free_page (kpage);
    return false; 
  }
  spte->is_load = 1;
  return true;
}
