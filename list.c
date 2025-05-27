#include "list.h"
#include "lezioni.h"
#include <stdlib.h>

struct node
{
    item value;
    struct node *next;
};
list newList(void)
{
    return NULL; // Restituisce NULL, indicando una lista vuota
}

// Funzione per verificare se la lista è vuota
int emptyList(list l)
{
    return l == NULL; // Restituisce 1 se la lista è vuota (NULL), altrimenti restituisce 0
}
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
list tailList(list l)
{
    list temp; // Dichiarazione di un puntatore temporaneo a lista

    if (l != NULL)      // Verifica se la lista non è vuota
        temp = l->next; // Se l'elemento corrente non è l'ultimo, assegna il puntatore al prossimo elemento alla variabile temporanea
    else
        temp = NULL; // Se la lista è vuota, la coda sarà anche vuota

    return temp; // Restituisce la coda della lista (una nuova lista)
}
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

item getFirst(list l)
{
    item e; // Dichiarazione di una variabile temporanea per memorizzare il primo elemento della lista

    if (l != NULL)    // Verifica se la lista non è vuota
        e = l->value; // Se la lista non è vuota, assegna il valore del primo elemento alla variabile temporanea
    else
        e = NULLITEM; // Se la lista è vuota, assegna un valore speciale NULLITEM alla variabile temporanea

    return e; // Restituisce il primo elemento della lista
}