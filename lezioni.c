#define MAX_STR 50
#define MAX_POSTI 100
#include "clienti.h"
#include "lezioni.h"
#include <stdlib.h>
struct Lezione
{
    char nome[MAX_STR];
    char istruttore[MAX_STR];
};

struct LezioneNode
{
    struct Lezione lezione;
    struct Lezione *next;
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

void visualizzaDisponibilitaLezione(struct LezioneNode *head)
{

    if (head == NULL)
    {
        printf("Nessuna lezione programmata.\n");
        return;
    }

    printf("Disponibilita' Lezioni: \n");

    struct LezioneNode *curr = head;

    while (curr != NULL)
    {

        struct Lezione lezioneattuale = curr->lezione;
        int postiOccupati = ContaPartecipanti(lezioneattuale.clienti);
        int capacita = lezioneattuale.capacita_massima;
        int postiDisponibili = capacita - postiOccupati;

        printf("Nome Lezione: %s\n", lezioneattuale.nome);
        printf("Nome Istruttore: %s\n", lezioneattuale.istruttore);
        printf("Posti Attualmente Occupati: %d\n", postiOccupati);
        printf("Capacità Totale Lezione: %d\n", capacita);
        printf("Posti Disponibili: %d\n", postiDisponibili);

        curr = curr->next;
    }
}
