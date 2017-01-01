#include"fold.h"
#include"trackedmemory.h"
#include<stdio.h>
#include"list.h"

void * freeElement(void * a, void *e){ FREE(e); return a;}


void * printIntegerList(void * a, void *e){ 
  printf("%3lu: %d\n", (unsigned long)a, *((int*)e));
  return a+1;
}

void * sumIntegerList(void * a, void *e){
  *((int*)a) += *((int*)e);
  return a;
}

void * copyList(void *a, void * e){
  List * l = (List*)a;
  l->append(l, e);
  return a;
}

