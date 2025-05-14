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

int InsertHash(hashtable h, Cliente cliente)
{

    if (h == NULL)
    {
        fprintf(stderr, "Errore: la tabella hash non è stata inizializzata.\n");
        return 0; // O un valore di errore appropriato
    }
    if (cliente == NULL)
    {
        fprintf(stderr, "Errore: il cliente non è valido.\n");
        return 0; // O un valore di errore appropriato
    }
    int idx;
    struct Cliente *head, *curr;
    idx = hashFun(cliente->id, h->size);
    printf("valore di idx: %d", idx);
    printf("h->size: %d", h->size);
    curr = head = h->table[idx];
    //  while (curr)
    //  {
    //      if (curr->id == cliente->id)
    //          return (0);
    //      curr = curr->next;
    //  }
    //  h->table[idx] = cliente;
    //  h->table[idx]->next = head;
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

static void deleteList(struct Cliente *p)
{
    if (p == NULL)
        return;
    deleteList(p->next);
    free(p);
    return;
}
