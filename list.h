// file list.h
typedef struct node *list;
typedef void *item;
// prototipi
list newList(void);
int emptyList(list l);
list tailList(list l);
list consList(item val, list l);
list reverseList(list l);
item getFirst(list l);