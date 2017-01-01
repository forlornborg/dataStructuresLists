#ifndef __stack_h_
#define __stack_h_

#include<stdlib.h>

typedef struct _stack Stack;
struct _stack{
  Stack* (*push)(Stack*, void*);
  Stack* (*pop)(Stack*, void **);
  Stack* (*peek)(Stack*, void**);
  size_t (*size)(Stack*);
  void (*destroy)(Stack*);
};



#endif
