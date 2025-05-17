typedef struct hash *hashtable;
typedef struct Cliente *Cliente;
typedef struct Cliente *Cliente;

hashtable newHashtable(int size);
int aggiungiCliente(hashtable h, Cliente cliente);
struct Cliente *newCliente(int id, char nome[], char cognome[], int abbonamento);
struct Cliente *hashDelete(hashtable h, int key);
void destroyHashtable(hashtable h);
static void deleteList(struct Cliente *c);
int hashFun(int k, int m);
Cliente cercaCliente(hashtable h, int id_cliente, int size_tabella);
void stampaClienti(hashtable h);