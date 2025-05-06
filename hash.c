#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

// Definizione della struttura per un elemento della tabella hash.
// Assumiamo che 'item' sia un tipo definito altrove nel codice.
struct item
{
    // Qui potrebbero essere definiti vari campi, come chiavi, valori, ecc.
};

// Definizione della struttura della tabella hash.
struct hash
{
    int size;            // Dimensione della tabella hash.
    struct item **table; // Puntatore a un array di puntatori a 'item'.
};

// Funzione per creare una nuova tabella hash.
hashtable newHashtable(int size)
{
    int i;
    // Allocazione della memoria per la struttura hash.
    hashtable h = (struct hash *)malloc(sizeof(struct hash));
    if (h == NULL)
    { // Controlla se l'allocazione della memoria è fallita.
        return NULL;
    }

    h->size = size; // Imposta la dimensione della tabella hash.

    // Allocazione della memoria per gli elementi della tabella,
    // inizializzando tutti i puntatori a NULL utilizzando calloc.
    h->table = (struct item **)calloc(size, sizeof(struct item *));
    if (h->table == NULL)
    {            // Controlla se l'allocazione della memoria per la tabella è fallita.
        free(h); // Libera la memoria allocata per la struttura hash se la tabella non può essere creata.
        return NULL;
    }

    // Il ciclo commentato qui sotto è superfluo poiché calloc inizializza già la memoria a NULL.
    // for(i=0; i<size; i++) {
    //     h->table[i] = NULL;
    // }

    return h; // Ritorna il puntatore alla nuova tabella hash.
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assumiamo che 'struct item' sia definito da qualche parte nel tuo codice, simile a questo:
struct item
{
    char *key;         // Chiave dell'elemento.
    int intero1;       // Un intero, per esempio.
    int intero2;       // Un altro intero.
    struct item *next; // Puntatore al prossimo elemento nella stessa lista della tabella hash.
};

// Prototipi per funzioni ausiliarie (da definire altrove nel codice).
int hashFun(char *key, int size);                // Funzione hash che calcola l'indice basato sulla chiave e sulla dimensione della tabella.
struct item *newItem(char *key, int i1, int i2); // Funzione per creare un nuovo 'item'.

// Funzione per inserire un elemento in una tabella hash.
int InsertHash(hashtable h, struct item elem)
{
    int idx;
    struct item *head, *curr;

    // Calcola l'indice nella tabella hash usando la funzione hash.
    idx = hashFun(elem.key, h->size);

    // Imposta 'curr' e 'head' al primo elemento della lista in questo indice.
    curr = head = h->table[idx];

    // Scorri la lista per controllare se esiste già un elemento con la stessa chiave.
    while (curr)
    {
        if (strcmp(curr->key, elem.key) == 0)
        {
            return 0; // Elemento già presente, ritorna 0.
        }
        curr = curr->next;
    }

    // Crea un nuovo elemento e inseriscilo all'inizio della lista.
    h->table[idx] = newItem(elem.key, elem.intero1, elem.intero2);
    h->table[idx]->next = head;

    return 1; // Inserimento riuscito, ritorna 1.
}

// Funzione per eliminare un elemento da una tabella hash basandosi sulla chiave fornita.
struct item *hashDelete(hashtable h, char *key)
{
    int idx;
    struct item *prev, *curr, *head, *temp;

    // Calcola l'indice nella tabella hash utilizzando la funzione hash sulla chiave fornita.
    idx = hashFun(key, h->size);

    // Inizializza i puntatori per scorrere la lista alla posizione calcolata.
    prev = curr = head = h->table[idx];

    // Scorri la lista per trovare l'elemento con la chiave corrispondente.
    while (curr)
    {
        if (!strcmp(curr->key, key))
        { // Se trova l'elemento
            if (curr == head)
            {
                // Se l'elemento da eliminare è il primo della lista, aggiorna il puntatore della tabella.
                h->table[idx] = curr->next;
            }
            else
            {
                // Se non è il primo, aggancia il nodo precedente al nodo successivo di quello corrente.
                prev->next = curr->next;
            }
            return (curr); // Ritorna il puntatore all'elemento eliminato.
        }
        // Aggiorna i puntatori 'prev' e 'curr' per continuare a scorrere.
        prev = curr;
        curr = curr->next;
    }
    return NULL; // Se non trova l'elemento, ritorna NULL.
}

// Funzione per distruggere (eliminare completamente) una tabella hash.
void DestroyHashtable(hashtable h)
{
    int i;
    // Ciclo attraverso ogni indice della tabella hash.
    for (i = 0; i < h->size; i++)
    {
        // Elimina la lista collegata in ogni indice della tabella.
        deleteList(h->table[i]);
    }
    // Libera la memoria allocata per l'array di puntatori della tabella.
    free(h->table);
    // Libera la memoria allocata per la struttura della tabella hash.
    free(h);
    return;
}

// Versione iterativa di deleteList per evitare l'overflow dello stack su liste lunghe.
static void deleteList(struct item *p)
{
    struct item *nextNode;
    while (p != NULL)
    {
        nextNode = p->next; // Salva il riferimento al nodo successivo.
        free(p);            // Libera il nodo corrente.
        p = nextNode;       // Passa al nodo successivo.
    }
}