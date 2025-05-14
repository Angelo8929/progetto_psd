#define MAX_STR 50
#define MAX_POSTI 100
#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct Lezione
{
    int id_lezione;
    int capacita_massima;
    char nome[MAX_STR];
    char istruttore[MAX_STR];
    int postiOccupati;
};

struct LezioneNode
{
    struct Lezione lezione;
    struct LezioneNode *next;
};

LezioniList newLezioniList()
{
    return NULL;
}

int emptyLezioniList(LezioniList l)
{
    return l == NULL;
}

LezioniList aggiungiLezione(Lezione lezione, LezioniList l)
{

    struct LezioneNode *newLezione = malloc(sizeof(struct LezioneNode));
    if (newLezione == NULL)
    {
        return l;
    }
    newLezione->lezione = *lezione;
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
        int postiOccupati = lezioneattuale.postiOccupati;
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

Lezione newLezione(int id, int capacita_massima, char *nome, char *istruttore)
{
    Lezione lezione;

    lezione->id_lezione = id;
    lezione->capacita_massima = capacita_massima;
    strcpy(lezione->nome, nome);
    strcpy(lezione->istruttore, istruttore);
    lezione->postiOccupati = 0;
    return lezione;
}

void incrementaPostiOccupati(LezioniList head, int id_lezione)
{
    while (head != NULL)
    {
        if (head->lezione.id_lezione == id_lezione)
        {
            head->lezione.postiOccupati++;
            break;
        }
        head = head->next;
    }
}
