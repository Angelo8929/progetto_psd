#define MAX 100
#include "abbonamenti.h"
#include "clienti.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct Cliente
{
    int id;
    char nome[MAX];
    char cognome[MAX];
    int abbonamento;
    struct Cliente *next;
};

struct hash
{
    int size;
    struct Cliente **table;
};

hashtable newHashtable(int size)
{

    hashtable h = (struct hash *)malloc(sizeof(struct hash));
    h->size = size;
    h->table = (struct Cliente **)calloc(size, sizeof(struct Cliente *));

    return h;
}

int aggiungiCliente(hashtable h, Cliente cliente)
{

    if (cliente == NULL)
    {
        fprintf(stderr, "Errore: il cliente non è valido.\n");
        return 0; // O un valore di errore appropriato
    }
    int idx;
    struct Cliente *head, *curr;
    idx = hashFun(cliente->id, h->size);
    head = h->table[idx];
    curr = head;
    while (curr)
    {
        if (curr->id == cliente->id)
            return (0);
        curr = curr->next;
    }
    h->table[idx] = cliente;
    h->table[idx]->next = head;
    return (1);
}

int hashFun(int k, int m)
{
    return k % m;
}

Cliente newCliente(int id, char nome[], char cognome[], int abbonamento)
{
    Cliente nuovo = malloc(sizeof(struct Cliente));
    nuovo->id = id;
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    nuovo->abbonamento = abbonamento;
    nuovo->next = NULL;
    return nuovo;
}

void deleteList(struct Cliente *p)
{
    struct Cliente *nextNode;
    while (p != NULL)
    {
        nextNode = p->next; // Salva il riferimento al nodo successivo.
        free(p);            // Libera il nodo corrente.
        p = nextNode;       // Passa al nodo successivo.
    }
}

void destroyHashtable(hashtable h)
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

int getIdCliente(Cliente cliente)
{
    return cliente->id;
}

Cliente cercaCliente(hashtable h, int id_cliente, int size_tabella)
{
    if (h == NULL || h->table == NULL)
        return NULL;
    int idx = hashFun(id_cliente, size_tabella);
    struct Cliente *curr = h->table[idx];
    while (curr != NULL)
    {
        if (curr->id == id_cliente)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void stampaClienti(hashtable h)
{
    if (h == NULL)
    {
        printf("Hashtable non inizializzata.\n");
        return;
    }

    printf("\n--- Elenco Clienti ---\n");
    for (int i = 0; i < h->size; i++)
    {
        struct Cliente *curr = h->table[i];
        while (curr != NULL)
        {
            printf("ID: %d | Nome: %s | Cognome: %s | Abbonamento: %d\n",
                   curr->id, curr->nome, curr->cognome, curr->abbonamento);
            curr = curr->next;
        }
    }
    printf("----------------------\n");
}

int getAbbonamento(hashtable h, int id_cliente, int size_tabella)
{
    Cliente cliente = cercaCliente(h, id_cliente, size_tabella);
    if (cliente == NULL)
        return -1; // Cliente non trovato
    return cliente->abbonamento;
}

int getSize(hashtable h)
{
    return h->size;
}