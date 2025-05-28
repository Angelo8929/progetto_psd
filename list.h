// file list.h
typedef struct node *list; // tipo opaco per la lista
typedef void *item;        // tipo opaco per far adattare item a Prenotazione e Lezione
// prototipi

/*
    ---- funzione new_list()
    Restituisce una nuova lista collegata inizializzata a NULL
    Parametri: nessuno

*/

list newList();

/*
    --- funzione empty_list
    Restituisce 1 se la lista è vuota, 0 altrimenti
    Parametri:
        l: la lista collegata da esaminare, di tipo list

*/

int emptyList(list l);

/*
    ---- funzione tail_list
    Restituisce la lista, privata del suo primo elemento
    Parametri:
        l: la lista collegata

*/
list tailList(list l);

/*
    ---- funzione cons_list
    Aggiunge un elemento in testa alla lista
    Parametri:
        val: l'elemento da aggiungere, di tipo item
        l: la lista nella quale verrà aggiunto l'elemento
*/
list consList(item val, list l);

/*
    ---- funzione reverse_list
        Restituisce la lista con gli elementi in ordine inverso
        Parametri:
            l: la lista collegata da invertire

*/

list reverseList(list l);

/*
    ---- funzione get_first
    Restituisce il primo elemento della lista
    Parametri:
        l: la lista collegata da cui restituire il primo elemento
*/

item getFirst(list l);

/*

    ---- funzione libera_lista
    Libera la memoria allocata per la lista collegata
    Parametri:
        l: la lista collegata di cui liberare la memoria occupata

*/
void libera_lista(list l);