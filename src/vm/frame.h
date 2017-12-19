#ifndef FRAME_H
#define FRAME_H

#include "threads/palloc.h"
#include <list.h>

struct list frame_table;

struct frame_elem{
  void *upage;
  struct thread *owner;
  struct list_elem elem;
};

void *frame_get (enum palloc_flags);
void frame_free (void *);

#endif 
