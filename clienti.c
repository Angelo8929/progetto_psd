#define MAX 100

#include "abbonamenti.h"
#include "clienti.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ===============================
// Definizione delle strutture dati
// ===============================

// Definizione della struttura Cliente
struct Cliente
{
    int id;
    char nome[MAX];
    char cognome[MAX];
    int abbonamento;
    struct Cliente *next; // Puntatore al prossimo cliente nella lista (per gestione collisioni nella hashtable)
};

struct hash
{
    int size;               // Dimensione della tabella
    struct Cliente **table; // Array di puntatori a clienti (liste concatenate)
};

hashtable new_hashtable(int size)
{
    hashtable h = (struct hash *)malloc(sizeof(struct hash));
    h->size = size;
    h->table = (struct Cliente **)calloc(size, sizeof(struct Cliente *)); // Inizializza con NULL
    return h;
}
// Definizione della struttura hash (hashtable)
int insert_hash(hashtable h, Cliente cliente)
{
    if (cliente == NULL)
    {
        fprintf(stderr, "Errore: il cliente non è valido.\n");
        return 0;
    }

    int idx = hash_fun(cliente->id, h->size); // Calcola indice tramite funzione hash
    Cliente head = h->table[idx];             // Ottiene la lista corrente nella posizione calcolata
    Cliente curr = head;

    // Controlla se il cliente esiste già
    while (curr)
    {
        if (curr->id == cliente->id)
            return 0; // Cliente già presente
        curr = curr->next;
    }

    // Inserimento in testa alla lista (gestione collisioni con chaining)
    cliente->next = head;
    h->table[idx] = cliente;
    return 1;
}
// Crea una nuova hashtable con dimensione specificata

// Funzione di hash: restituisce l'indice per una chiave (id cliente)
int hash_fun(int k, int m)
{
    return k % m;
}

// Crea un nuovo cliente e restituisce il puntatore
Cliente crea_cliente(int id, char nome[], char cognome[], int abbonamento)
{
    Cliente nuovo = malloc(sizeof(struct Cliente));
    nuovo->id = id;
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    nuovo->abbonamento = abbonamento;
    nuovo->next = NULL;
    return nuovo;
}

// Aggiunge un cliente alla hashtable

// Elimina tutti i nodi di una lista di clienti

// Libera la memoria allocata per la hashtable e i suoi elementi

// Restituisce l'ID di un cliente
int get_id_cliente(Cliente cliente)
{
    return cliente->id;
}

// Cerca un cliente nella hashtable dato il suo id
Cliente cerca_cliente(hashtable clienti, int id_cliente, int size_tabella)
{

    if (clienti == NULL || clienti->table == NULL) // Se la hashtable non è inizializzata o i clienti non sono stati caricati
        return NULL;                               // Restituisce NULL

    int idx = hash_fun(id_cliente, size_tabella);
    struct Cliente *curr = clienti->table[idx];

    while (curr != NULL)
    {
        if (curr->id == id_cliente)
            return curr;
        curr = curr->next;
    }
    return NULL; // Cliente non trovato
}

// Stampa tutti i clienti presenti nella hashtable
void visualizza_clienti(hashtable clienti)
{
    if (clienti == NULL)
    {
        printf("Hashtable non inizializzata.\n");
        return;
    }

    printf("\n--- Elenco Clienti ---\n");
    for (int i = 0; i < clienti->size; i++)
    {
        struct Cliente *curr = clienti->table[i];
        while (curr != NULL)
        {
            printf("ID: %d | Nome: %s | Cognome: %s | Abbonamento: %svalido\n",
                   curr->id, curr->nome, curr->cognome, curr->abbonamento ? "" : "non ");
            curr = curr->next;
        }
    }
    printf("----------------------\n");
}

// Restituisce il numero dell'abbonamento di un cliente dato l'id
int get_abbonamento(hashtable clienti, int id_cliente, int size_tabella)
{
    Cliente cliente = cerca_cliente(clienti, id_cliente, size_tabella);
    if (cliente == NULL)
        return -1; // Cliente non trovato
    return cliente->abbonamento;
}

// Restituisce la dimensione della hashtable
int get_size(hashtable clienti)
{
    return clienti->size;
}

void destroy_hashtable(hashtable h)
{
    int i;
    // Ciclo attraverso ogni indice della tabella hash.
    for (i = 0; i < h->size; i++)
    {
        // Elimina la lista collegata in ogni indice della tabella.
        delete_list(h->table[i]);
    }
    // Libera la memoria allocata per l'array di puntatori della tabella.
    free(h->table);
    // Libera la memoria allocata per la struttura della tabella hash.
    free(h);
    return;
}

void delete_list(struct Cliente *p)
{
    struct Cliente *nextNode;
    while (p != NULL)
    {
        nextNode = p->next; // Salva il riferimento al nodo successivo.
        free(p);            // Libera il nodo corrente.
        p = nextNode;       // Passa al nodo successivo.
    }
}
