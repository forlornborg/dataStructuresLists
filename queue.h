#ifndef __queue_h_
#define __queue_h_

#include<stdlib.h>

typedef struct _queue Queue;
struct _queue{
  Queue* (*enqueue)(Queue*, void*);
  Queue* (*dequeue)(Queue*, void **);
  Queue* (*peek)(Queue*, void**);
  size_t (*size)(Queue*);
  void (*destroy)(Queue*);
};



#endif
