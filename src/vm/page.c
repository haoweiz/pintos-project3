#include "vm/page.h"
#include "vm/frame.h"
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
    if(list_entry(e,struct sup_page_entry,elem)->user_page == upage)
      return e;
  }
  return NULL;
}


bool load_from_file(struct sup_page_entry *spte){
    /* Get a page of memory. */
  uint8_t *kpage = frame_get (PAL_USER);
  if (kpage == NULL){
    return false;
  }
      

    /* Load this page. */
  if (file_read_at (spte->file, kpage, spte->read_bytes, spte->ofs) != (int) spte->read_bytes){
    frame_free (kpage);
    return false; 
  }
  memset (kpage + spte->read_bytes, 0, spte->zero_bytes);
      

    /* Add the page to the process's address space. */
  if (!install_page (spte->user_page, kpage, spte->writable)){
    frame_free (kpage);
    return false; 
  }
  return true;
}
