
typedef struct hash *hashtable;  // Tipo astratto per la tabella hash
typedef struct Cliente *Cliente; // Tipo astratto per un Cliente

// ===============================
// Funzioni per la gestione della hashtable
// ===============================

// Crea una nuova hashtable di dimensione specificata
hashtable new_hashtable(int size);
// Aggiunge un cliente alla hashtable, se non è già presente.
int insert_hash(hashtable h, Cliente cliente);
// Crea un nuovo cliente.
Cliente crea_cliente(int id, char nome[], char cognome[], int abbonamento);

// Libera tutta la memoria associata alla hashtable e ai clienti contenuti.

// Funzione hash che calcola la posizione in tabella a partire da una chiave.
int hash_fun(int k, int m);
int get_id_cliente(Cliente cliente);

// Cerca un cliente nella hashtable dato il suo ID.
Cliente cerca_cliente(hashtable clienti, int id_cliente, int size_tabella);

// Stampa a video tutti i clienti presenti nella hashtable.
void visualizza_clienti(hashtable clienti);

// Restituisce il codice dell'abbonamento di un cliente dato il suo ID.
int get_abbonamento(hashtable clienti, int id_cliente, int size_tabella);

// Restituisce la dimensione della hashtable.
int get_size(hashtable clienti);
void destroy_hashtable(hashtable h);
void delete_list(struct Cliente *p);