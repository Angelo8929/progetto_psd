
typedef struct hash *hashtable;  // Tipo astratto per la tabella hash
typedef struct Cliente *Cliente; // Tipo astratto per un Cliente

// ===============================
// Funzioni per la gestione della hashtable
// ===============================

/*
    Funzione: new_hashtable
    Restituisce una nuova hashtable di dimensione size
    Parametri:
        size: dimensione della tabella hash da creare, intero
*/

hashtable new_hashtable(int size);

/*
    Funzione: insert_hash
    Restituisce 1 se il cliente viene inserito correttamente nella tabella hash, altrimenti 0 se esiste già
    Parametri:
        h: la tabella hash su cui effettuare l'inserimento
        cliente: istanza della struct Cliente
*/

int insert_hash(hashtable h, Cliente cliente);

/*
    Funzione: crea_cliente
    Restituisce cliente = {id, nome, cognome, abbonamento}
    Parametri:
        id: identificativo del cliente, di tipo intero
        nome: nome del cliente, di tipo stringa
        cognome: cognome del cliente, di tipo stringa
        abbonamento: stato dell'abbonamento del cliente (0 indica non valido, 1 indica valido), di tipo intero
*/

Cliente crea_cliente(int id, char nome[], char cognome[], int abbonamento);

// Libera tutta la memoria associata alla hashtable e ai clienti contenuti.

/*
    Funzione: hash_fun
    Restituisce il valore hash di id_cliente, di tipo intero
    Parametri:
        id_cliente: chiave di cui si vuole ottenere il valore hash, di tipo intero
        size_tabella_hash: dimensione della tabella hash in cui deve rientrare il valore hash

*/

// Funzione hash che calcola la posizione in tabella a partire da una chiave.
int hash_fun(int k, int m);

int get_id_cliente(Cliente cliente);

/*
    Funzione: cerca_cliente
    Restituisce l'istanza della struct Cliente tale che il campo id_cliente sia uguale a quello specificato nei parametri
    Parametri:
        clienti: la tabella hash in cui andare a ricercare il cliente
        id_cliente: il campo secondo il quale si effettua la ricerca
        size_tabella: la dimensione della tabella hash per poter effettuare la ricerca

*/
// Cerca un cliente nella hashtable dato il suo ID.
Cliente cerca_cliente(hashtable clienti, int id_cliente, int size_tabella);

/*
    Funzione: visualizza_clienti
    Stampa a video tutti i clienti presenti nella hashtable
    Parametri:
        clienti: la hashtable per la quale si vogliono stampare gli elementi
*/

void visualizza_clienti(hashtable clienti);

/*
    Funzione: get_abbonamento
    Restituisce il campo abbonamento di un cliente dato il suo id
    Parametri:
        clienti: la hashtable in cui effettuare la ricerca
        id_cliente: identificativo del cliente di cui si vuole ottenere lo stato dell'abbonamento
        size_tabella: dimensione della tabella hash, per poter iterare all'interno di essa
*/

// Restituisce il codice dell'abbonamento di un cliente dato il suo ID.
int get_abbonamento(hashtable clienti, int id_cliente, int size_tabella);

/*
    Funzione: get_size
    Restituisce la dimensione della hashtable, intero
    Parametri:
        clienti: la hashtable di cui si vuole ottenere la dimensione

*/

int get_size(hashtable clienti);

/*
    Funzione: destroy_hashtable
    Dealloca la memoria per la hashtable
    Parametri:
        clienti: la hashtable da deallocare

*/

void destroy_hashtable(hashtable h);

/*
    Funzione: delete_list
    Dealloca la memoria per la lista collegata di ogni entry della tabella hash
    Parametri:
        p: il puntatore alla lista collegata di cui si vuole deallocare la memoria
*/

void delete_list(struct Cliente *p);