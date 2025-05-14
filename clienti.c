#define MAX 100
#include "abbonamenti.h"
#include "clienti.h"
#include <stdlib.h>
#include <string.h>
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
    int i;
    hashtable h = (struct hash *)malloc(sizeof(struct hash));
    h->size = size;
    h->table = (struct Cliente **)calloc(size, sizeof(struct Cliente *));
    for (i = 0; i < size; i++)
    {
        h->table[i] = NULL;
    }
    return h;
}

int aggiungiCliente(hashtable h, struct Cliente cliente)
{
    int idx;
    struct Cliente *head, *curr;
    idx = hashFun(cliente.id, h->size);
    curr = head = h->table[idx];
    while (curr)
    {
        if (curr->id == cliente.id)
            return (0);
        curr = curr->next;
    }
    h->table[idx] = newCliente(cliente.id, cliente.nome,
                               cliente.cognome, cliente.abbonamento);
    h->table[idx]->next = head;
    return (1);
}

int hashFun(int k, int m)
{
    return k % m;
}

struct Cliente *newCliente(int id, char nome[], char cognome[], int abbonamento)
{
    struct Cliente *nuovo = malloc(sizeof(struct Cliente));
    nuovo->id = id;
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    nuovo->abbonamento = abbonamento;
    nuovo->next;

    return nuovo;
}

static void deleteList(struct Cliente *p)
{
    if (p == NULL)
        return;
    deleteList(p->next);
    free(p);
    return;
}
