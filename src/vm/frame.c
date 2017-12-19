#include "vm/frame.h"
#include "threads/palloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include <stdlib.h>

void *frame_get (enum palloc_flags flags){
  void *f = palloc_get_page (flags);
  struct frame_elem *fe = malloc(sizeof(struct frame_elem));
  fe->upage = f;
  fe->owner = thread_current();
  list_push_back(&frame_table,&fe->elem);
  return f;
}

void frame_free (void *frame){
  palloc_free_page (frame);
  struct list_elem *e;
  struct frame_elem *fe;
  for(e = list_begin(&frame_table);e != list_end(&frame_table);e = list_next(e)){
    fe = list_entry(e, struct frame_elem, elem);
    if(fe->upage == frame){
      list_remove(e);
      return;
    }
  }
}
