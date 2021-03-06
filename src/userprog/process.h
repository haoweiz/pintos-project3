#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

static int code_or_data = 0; /* 0: load code segment.  */
                             /* 1: load data segment.  */
                             /* 2: load mmap segment.  */
tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (void);
bool install_page (void *upage, void *kpage, bool writable);   /* load() helpers. */

#endif /* userprog/process.h */
