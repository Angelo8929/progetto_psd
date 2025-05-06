#define MAX_STR 50
#define MAX_POSTI 100
#include "clienti.h"
#include "lezioni.h"
#include <stdlib.h>
struct Lezione
{
    char nome[MAX_STR];
    char istruttore[MAX_STR];
    int posti_occupati[MAX_POSTI];
    struct ClienteNode *clienti;
};

struct LezioneNode
{
    struct Lezione lezione;
    struct Lezione *next;
};

struct ClienteNode
{
    int id;
    struct ClienteNode *next;
};

LezioniList newLezioniList()
{
    return NULL;
}

int emptyLezioniList(LezioniList l)
{
    return l == NULL;
}

LezioniList aggiungiLezione(struct Lezione lezione, LezioniList l)
{
    if (l == NULL)
    {
        return NULL;
    }

    struct LezioneNode *newLezione = malloc(sizeof(struct LezioneNode));
    if (newLezione == NULL)
    {
        return l;
    }
    newLezione->lezione = lezione;
    newLezione->next = l;
    l = newLezione;
    return l;
}