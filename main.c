#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"fold.h"
#include"list.h"
#include"arraylist.h"
#include"linkedlist.h"
#include"stacklistwrapper.h"
#include"queuelistwrapper.h"
#include"trackedmemory.h"

void rlStressTest(List *);
void rfStressTest(List *);
void rStressTest(List *);

int main(int argc, char ** argv){

  char command[30];
  List * l = NULL;

  while(scanf("%s", command) > 0){
    if(strcmp(command, "ArrayList") == 0){
      if(l != NULL){
        List * copy = ArrayList(2);
        l->fold(l, copy, copyList);
        l->destroy(l);
        l = copy;
      } else {
        l = ArrayList(2);
      }
    } else if(strcmp(command, "LinkedList") == 0){
      if(l != NULL){
        List * copy = LinkedList();
        l->fold(l, copy, copyList);
        l->destroy(l);
        l = copy;
      } else {
        l = LinkedList();
      }
    } else if(strcmp(command, "prepend") ==0){
      int *d = MALLOC(sizeof(int));
      scanf("%d", d);
      l->prepend(l, d);
    } else if(strcmp(command, "removefirst") ==0){
      int * d;
      l->removefirst(l, (void**)&d);
      if(d){
        printf("removed %d from front of list.\n", *d);
        FREE(d);
      } else {
        printf("list is empty.\n");
      }
    } else if(strcmp(command, "append") ==0){
      int *d = MALLOC(sizeof(int));
      scanf("%d", d);
      l->append(l, d);
    } else if(strcmp(command, "removelast") ==0){
      int * d;
      l->removelast(l, (void**)&d);
      if(d){
        printf("removed %d from back of list.\n", *d);
        FREE(d);
      } else {
        printf("list is empty.\n");
      }
    } else if(strcmp(command, "get") ==0){
      size_t i;
      int *d;
      scanf("%lu", &i);
      l->get(l, i,  (void **) &d );
      printf("got %d at index %lu\n", *d, i);
    } else if(strcmp(command, "set") ==0){
      size_t i;
      int *d = MALLOC(sizeof(int));
      scanf("%lu", &i);
      scanf("%d", d);
      int * toDelete;
      if(i < l->size(l)){
        l->get(l, i,  (void **) &toDelete );
        FREE(toDelete);
      }
      l->set(l, i, d );
    } else if(strcmp(command, "insert") ==0){
      size_t i;
      int *d = MALLOC(sizeof(int));
      scanf("%lu", &i);
      scanf("%d", d);
      l->insert(l, i, d );
      printf("inserted %d at index %lu.\n", *d, i);
    } else if(strcmp(command, "remove") ==0){
      size_t i;
      int *d;
      scanf("%lu", &i);
      l->remove(l, i,  (void **) &d );
      if(d){
        printf("removed %d from index %lu.\n", *d, i);
        FREE(d);
      } else {
        printf("list does not have content at index %lu.\n", i);
      }
    } else if(strcmp(command, "display") ==0){
      printf("List Content:\n");
      l->fold(l, 0, printIntegerList);
    } else if(strcmp(command, "sum") ==0){
      int a = 0;
      l->fold(l, &a, sumIntegerList);
      printf("sum of list content is: %d\n",a);
    } else if(strcmp(command, "size") ==0){
      printf("the list contains %lu elements.\n",l->size(l));
    } else if(strcmp(command, "rlStressTest") ==0){
      rlStressTest(l);
    } else if(strcmp(command, "rfStressTest") ==0){
      rfStressTest(l);
    } else if(strcmp(command, "rStressTest") ==0){
      rStressTest(l);
    } else if(strcmp(command, "Stack") ==0){
      Stack * s = StackListWrapper(l);
      printf("Switching To Stack Mode.\n");
      while(scanf("%s", command) >0){
        if(strcmp(command, "endStack") == 0){
          printf("Leaving Stack Mode.\n");
          break;
        } else if(strcmp(command, "push") == 0){
          int* d = (int*)MALLOC(sizeof(int));
          scanf("%d", d);
          s->push(s, d);
          printf("pushed %d onto the stack.\n", *d);
        } else if(strcmp(command, "pop") == 0){
          int *d;
          s->pop(s, (void**)&d);
          if(d == NULL)
            printf("Stack Is Empty\n");
          else {
            printf("popped %d from the stack.\n", *d);
            FREE(d);
          }
        } else if(strcmp(command, "peek") == 0){
          int *d;
          s->peek(s,(void **)&d);
          if(d == NULL)
            printf("Stack Is Empty\n");
          else
            printf("peeked %d from the stack.\n", *d);
        } else if(strcmp(command, "size") == 0){
          printf("stack has %lu elements on it.\n", s->size(s));
        } else if(strcmp(command, "display") == 0){
          printf("StackListWrapper Content:\n");
          l->fold(l, 0, printIntegerList);
        } else {
          printf("Stack Mode, unrecognized command: %s\n",command);
        }
      }
      s->destroy(s);
    } else if(strcmp(command, "Queue") ==0){
      Queue * q = QueueListWrapper(l);
      printf("Switching To Queue Mode.\n");
      while(scanf("%s", command) >0){
        if(strcmp(command, "endQueue") == 0){
          printf("Leaving Queue Mode.\n");
          break;
        } else if(strcmp(command, "enqueue") == 0){
          int* d = (int*)MALLOC(sizeof(int));
          scanf("%d", d);
          q->enqueue(q,d);
          printf("enqueued %d into the queue.\n", *d);
        } else if(strcmp(command, "dequeue") == 0){
          int *d;
          q->dequeue(q, (void **)&d);
          if(d == NULL)
            printf("Queue Is Empty\n");
          else {
            printf("dequeued %d from the queue.\n", *d);
            FREE(d);
          }
        } else if(strcmp(command, "peek") == 0){
          int *d;
          q->peek(q,(void **)&d);
          if(d == NULL)
            printf("Queue Is Empty\n");
          else
            printf("peeked %d from the queue.\n", *d);
        } else if(strcmp(command, "size") == 0){
          printf("queue has %lu elements on it.\n", q->size(q));
        } else if(strcmp(command, "display") == 0){
          printf("QueueListWrapper Content:\n");
          l->fold(l, 0, printIntegerList);
        } else {
          printf("Queue Mode, unrecognized command: %s\n",command);
        }
      }
      q->destroy(q);
    } else if(strcmp(command, "size") ==0){
      printf("the list contains %lu elements.\n",l->size(l));
    } else {
      printf("unrecognized command: %s\n",command);
    }
  }

  if(l){
    l->fold(l, NULL, freeElement);
    l->destroy(l);
  }
  assertNoMemoryLeaks();
  return 0;
}



void rlStressTest(List * l){
  if(l->size(l) > 0){
    void *e;
    l->removelast(l,&e);
    rlStressTest(l);
    l->append(l, e);
  }
}
void rfStressTest(List *l){
  if(l->size(l) > 0){
    void *e;
    l->removefirst(l,&e);
    rfStressTest(l);
    l->prepend(l, e);
  }
}



void rStressTest(List *l){
  size_t size = l->size(l);
  if(size > 0){
    void *e;
    l->remove(l,size/2,&e);
    rStressTest(l);
    l->insert(l,size/2, e);
  }
}
