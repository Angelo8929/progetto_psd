typedef struct hash *hashtable;

hashtable newHashtable(int size);
int aggiungiCliente(hashtable h, struct Cliente cliente);
struct Cliente *newCliente(int id, char *nome, char *cognome);
struct Cliente *hashDelete(hashtable h, int key);
void destroyHashtable(hashtable h);
static void deleteList(struct Cliente *c);
int hashFun(int k, int m);
