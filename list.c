#include "list.h"
#include "lezioni.h"
#include <stdlib.h>

struct node // definizione del singolo nodo della lista
{
    item value;
    struct node *next;
};

/*
    funzione new_list
    Precondizione: sempre verificata, la funzione non ha parametri
    Postcondizione: restituisce una lista vuota
*/

list newList()
{
    return NULL; // Restituisce NULL, indicando una lista vuota
}

/*
    funzione empty_list(list l)
    Precondizione: sempre verificata
    Postcondizione: restituisce 1 se la lista è vuota, 0 altrimenti

*/

int emptyList(list l)
{
    return l == NULL; // Restituisce 1 se la lista è vuota (NULL), altrimenti restituisce 0
}

/*
    funzione cons_list(item val, list l)
    Precondizione: item != NULL
    Postcondizione: restituisce l' = (val, a1, a2, ..., an)
*/

list consList(item val, list l)
{
    struct node *nuovo;                  // Dichiarazione di un puntatore a un nuovo nodo
    nuovo = malloc(sizeof(struct node)); // Allocazione della memoria per il nuovo nodo

    if (nuovo != NULL)
    {                       // Verifica se l'allocazione della memoria è riuscita
        nuovo->value = val; // Assegna il valore val al campo value del nuovo nodo
        nuovo->next = l;    // Collega il nuovo nodo al nodo successivo, che è la lista l

        l = nuovo; // Aggiorna il puntatore alla testa della lista in modo che punti al nuovo nodo
    }

    return l; // Restituisce il puntatore alla lista aggiornata
}

/*
    funzione tail_list(list l)
    Precondizione: sempre verificata
    Postcondizione: se l = (a1, a2, ..., an), allora restituisce l' = (a2, a3, ..., an)
*/

list tailList(list l)
{
    list temp; // Dichiarazione di un puntatore temporaneo a lista

    if (l != NULL)      // Verifica se la lista non è vuota
        temp = l->next; // Se l'elemento corrente non è l'ultimo, assegna il puntatore al prossimo elemento alla variabile temporanea
    else
        temp = NULL; // Se la lista è vuota, la coda sarà anche vuota

    return temp; // Restituisce la coda della lista (una nuova lista)
}

/*
    funzione reverse_list(list l)
    Precondizioni: l != NULL
    Postcondizione: restituisce la lista con gli elementi in ordine inverso

*/

list reverseList(list l)
{
    list rev;        // Dichiarazione di un puntatore a una nuova lista invertita
    item val;        // Dichiarazione di una variabile temporanea per memorizzare il valore degli elementi
    rev = newList(); // Inizializzazione della nuova lista vuota
    // Ciclo finché la lista originale non è vuota
    while (!emptyList(l))
    {
        val = getFirst(l);        // Ottiene il valore del primo elemento della lista originale
        rev = consList(val, rev); // Aggiunge il valore alla testa della lista invertita
        l = tailList(l);          // Passa al prossimo elemento della lista originale
    }
    return rev; // Restituisce la lista invertita
}

/*
    funzione get_first(list l)
    Precondizione: l != NULL
    Postcondizione: restituisce il primo elemento della lista


*/
item getFirst(list l)
{
    item e; // Dichiarazione di una variabile temporanea per memorizzare il primo elemento della lista

    if (l != NULL)    // Verifica se la lista non è vuota
        e = l->value; // Se la lista non è vuota, assegna il valore del primo elemento alla variabile temporanea
    else
        e = NULLITEM; // Se la lista è vuota, assegna un valore speciale NULLITEM alla variabile temporanea

    return e; // Restituisce il primo elemento della lista
}

/*
    funzione libera_lista(list l)
    Precondizione: l != NULL
    Postcondizione: dealloca la memoria occupata dalla lista

*/

void libera_lista(list l)
{
    while (l != NULL) // finchè la lista non si svuota
    {
        list tmp = l;     // salva il puntatore al nodo corrente
        free(tmp->value); // libera la memoria dell'elemento puntato da value
        l = tailList(l);  // passa al nodo successivo
        free(tmp);        // libera la memoria del nodo corrente
    }
}