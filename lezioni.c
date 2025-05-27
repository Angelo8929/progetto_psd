#define MAX_STR 50
#define MAX_POSTI 100
#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ===============================
// Definizione delle strutture dati
// ===============================

// Struttura che rappresenta una singola lezione
struct Lezione
{
    int id_lezione;           // ID univoco della lezione
    int capacita_massima;     // Numero massimo di posti disponibili
    char nome[MAX_STR];       // Nome della lezione
    char istruttore[MAX_STR]; // Nome dell'istruttore
    int postiOccupati;        // Numero attuale di posti occupati
    char orario[6];           // Orario nel formato "HH:MM"
};

// Nodo per la lista concatenata di lezioni

// Crea e restituisce una lista di lezioni vuota.

// Aggiunge una lezione in testa alla lista.

// Funzione per la visualizzazione della disponibilità delle lezioni
void visualizza_lezioni(LezioniList lezioni)
{

    if (lezioni == NULL)
    {
        printf("Nessuna lezione programmata.\n");
        return;
    }

    printf("Disponibilita' Lezioni: \n");

    list curr = lezioni; // Inizializza il puntatore corrente alla testa della lista

    while (curr != NULL) // Itera attraverso la lista di lezioni
    {

        struct Lezione lezioneattuale = *(Lezione)getFirst(lezioni); // Ottiene la lezione corrente
        int postiOccupati = lezioneattuale.postiOccupati;            // Ottiene il numero di posti occupati per quella lezione
        int capacita = lezioneattuale.capacita_massima;              // Ottiene la capacità massima della lezione
        int postiDisponibili = capacita - postiOccupati;             // Calcola i posti disponibili

        // Stampa le informazioni della lezione corrente
        printf("\n--- Dettagli Lezione ---\n");
        printf("-----------------------------------------------\n");
        printf(" ID Lezione                    | %d\n", lezioneattuale.id_lezione);
        printf(" Nome Lezione                  | %s\n", lezioneattuale.nome);
        printf(" Nome Istruttore               | %s\n", lezioneattuale.istruttore);
        printf(" Posti Attualmente Occupati    | %d\n", postiOccupati);
        printf(" Capacita' Totale Lezione      | %d\n", capacita);
        printf(" Posti Disponibili             | %d\n", postiDisponibili);
        printf("-----------------------------------------------\n\n");

        curr = tailList(curr);
    }
}

// Crea una nuova lezione e restituisce un puntatore ad essa
Lezione crea_lezione(int id, int capacita_massima, char *nome, char *istruttore, char *orario)
{
    Lezione lezione = malloc(sizeof(struct Lezione)); // Alloca memoria per una nuova lezione
    if (lezione == NULL)
    {
        printf("Memoria non allocata correttamente.\n");
        exit(1);
    }

    // Inizializza i campi della lezione

    lezione->id_lezione = id;
    lezione->capacita_massima = capacita_massima;
    strcpy(lezione->nome, nome);
    strcpy(lezione->istruttore, istruttore);
    lezione->postiOccupati = 0;
    strcpy(lezione->orario, orario);
    strcpy(lezione->orario, orario);
    return lezione;
}

// Incrementa il numero di posti occupati per una lezione specifica
void incrementa_posti_occupati(Lezione lezione)
{
    lezione->postiOccupati++;
}

// Libera la memoria occupata dalla lista di lezioni
void libera_lezioni(LezioniList lezioni)
{

    while (lezioni != NULL)
    {
        LezioniList tmp = lezioni;
        lezioni = tailList(lezioni);
        free(tmp);
    }
}

// Restituisce la capacità massima di una lezione
int get_capacita(Lezione lezione)
{
    return lezione->capacita_massima;
}

// Cerca una lezione specifica nella lista di lezioni
// Lezione cerca_lezione(list lezioni, int id_lezione)
// {
//     list temp = lezioni; // Inizializza un puntatore temporaneo alla testa della lista
//     while (temp != NULL)
//     {
//         if (temp->lezione.id_lezione == id_lezione)
//         {
//             return &(temp->lezione); // Restituisce il puntatore alla lezione trovata
//         }
//         else
//         {
//             temp = temp->next; // Passa alla lezione successiva se non trovata
//         }
//     }
//     return NULL;
// }

// Restituisce il numero di posti occupati per una lezione
int get_posti_occupati(Lezione lezione)
{
    return lezione->postiOccupati;
}

int get_id_lezione(Lezione lezione)
{
    return lezione->id_lezione;
}

Lezione get_lezione_from_node(LezioniList nodo)
{
    if (nodo == NULL)
        return NULL;
    return (getFirst(nodo));
}

LezioniList go_next(LezioniList nodo)
{
    return tailList(nodo);
}
