#ifndef __list_h_
#define __list_h_

#include<stdlib.h>

typedef struct _list_interface List;
struct _list_interface{
   List * (*prepend)(List*, void*);
   List * (*append)(List*, void*);
   List * (*removefirst)(List*, void**);
   List * (*removelast)(List*, void**);
   List * (*set)(List*, size_t, void*);
   List * (*get)(List*, size_t, void**);
   List * (*insert)(List*, size_t, void*);
   List * (*remove)(List*, size_t, void**);
   size_t (*size)(List*);
   List * (*sort)(List*, int (*comp)(void*, void*));
   void * (*fold)(List*, void*, void* (*f)(void*,void*));
   void (*destroy)(List*);
};

#endif
