#include "item.h"
typedef struct node *list;
// prototipi
list newList(void);
int emptyList(list l);
list tailList(list l);
list consList(item val, list l);
item getFirst(list l);