

typedef struct hash *hashtable;     // Tipo astratto per la tabella hash
typedef struct Cliente *Cliente;    // Tipo astratto per un Cliente

// ===============================
// Funzioni per la gestione della hashtable
// ===============================


  // Crea una nuova hashtable di dimensione specificata 
    hashtable newHashtable(int size);

  // Aggiunge un cliente alla hashtable, se non è già presente.
    int aggiungiCliente(hashtable h, Cliente cliente);

  // Crea un nuovo cliente.
    Cliente newCliente(int id, char nome[], char cognome[], int abbonamento);

 // Libera tutta la memoria associata alla hashtable e ai clienti contenuti.
    void destroyHashtable(hashtable h);

// Libera la memoria occupata da una lista di clienti.
    void deleteList(struct Cliente *p);

  // Funzione hash che calcola la posizione in tabella a partire da una chiave.
    int hashFun(int k, int m);

  // Cerca un cliente nella hashtable dato il suo ID.
    Cliente cercaCliente(hashtable h, int id_cliente, int size_tabella);

 // Stampa a video tutti i clienti presenti nella hashtable.
    void stampaClienti(hashtable h);

 // Restituisce il codice dell'abbonamento di un cliente dato il suo ID.
    int getAbbonamento(hashtable h, int id_cliente, int size_tabella);

  // Restituisce la dimensione della hashtable.
    int getSize(hashtable h);