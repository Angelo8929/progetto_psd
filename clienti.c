#define MAX 100
#include "abbonamenti.h"
#include "clienti.h"
#include <stdlib.h>
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
    h->table = (struct Cliente **)calloc(size, sizeof(struct item *));
    for (i = 0; i < size; i++)
    {
        h->table[i] = NULL;
    }
    return h;
}

int InsertHash(hashtable h, struct Cliente cliente)
{
    int idx;
    struct Cliente *head, *curr;
    idx = hashFun(cliente.id, h->size);
    curr = head = h->table[idx];
    while (curr)
    {
        if (strcmp(curr->id, cliente.id) == 0)
            return (0);
        curr = curr->next;
    }
    h->table[idx] = newCliente(cliente.id, cliente.nome,
                               cliente.cognome, cliente.abbonamento);
    h->table[idx]->next = head;
    return (1);
}

int hash(int k, int m)
{
    return k % m;
}
