#include"stacklistwrapper.h"
#include"trackedmemory.h"
#include <stdio.h>

struct _wrapStack{
  Stack s;
  List * li;
};

typedef struct _wrapStack stackType;
typedef struct _wrapStack* S;

Stack * sPop(Stack * s, void ** e){
  S sList = (S) s;
  sList->li->removefirst(sList->li,e);
}

Stack * sPush(Stack * s, void * e){
S sList = (S) s;
sList -> li -> prepend(sList->li, e);
return s;
}

Stack * sPeek(Stack *s, void ** e){
  S sList = (S) s;
  sList->li->get(sList->li, sList->li->size(sList->li)-1, e);

  return s;
}

size_t sSize(Stack * s){
  S sList = (S) s;

  return sList->li->size(sList->li);
}

void sDestroy(Stack *s){
  S sList = (S) s;
  FREE(sList);
}


Stack* StackListWrapper(List *l){
  S sList = (S) MALLOC(sizeof(stackType));
  sList -> li = l;
  sList -> s.push = sPush;
  sList -> s.pop = sPop;
  sList -> s.peek = sPeek;
  sList -> s.size = sSize;
  sList -> s.destroy = sDestroy;

  return  (Stack *) sList;
}
