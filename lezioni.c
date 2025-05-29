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
    int posti_occupati;       // Numero attuale di posti occupati
    char orario[6];           // Orario nel formato "HH:MM"
};

// Nodo per la lista concatenata di lezioni

// Crea e restituisce una lista di lezioni vuota.

// Aggiunge una lezione in testa alla lista.

/*
    ---- funzione visualizza_lezioni (lezioni_list lezioni)
        precondizione: sempre verificata
        postcondizione: stampa la lista delle lezioni, se != NULL, altrimenti il messaggio "nessuna lezione programmata"

*/

// Funzione per la visualizzazione della disponibilità delle lezioni
void visualizza_lezioni(lezioni_list lezioni)
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

        struct Lezione lezioneattuale = *(Lezione)get_first(curr); // Ottiene la lezione corrente
        int posti_occupati = lezioneattuale.posti_occupati;        // Ottiene il numero di posti occupati per quella lezione
        int capacita = lezioneattuale.capacita_massima;            // Ottiene la capacità massima della lezione
        int postiDisponibili = capacita - posti_occupati;          // Calcola i posti disponibili

        // Stampa le informazioni della lezione corrente
        printf("\n--- Dettagli Lezione ---\n");
        printf("-----------------------------------------------\n");
        printf(" ID Lezione                    | %d\n", lezioneattuale.id_lezione);
        printf(" Nome Lezione                  | %s\n", lezioneattuale.nome);
        printf(" Nome Istruttore               | %s\n", lezioneattuale.istruttore);
        printf(" Posti Attualmente Occupati    | %d\n", posti_occupati);
        printf(" Capacita' Totale Lezione      | %d\n", capacita);
        printf(" Posti Disponibili             | %d\n", postiDisponibili);
        printf("-----------------------------------------------\n\n");

        curr = tail_list(curr);
    }
}

/*
    ---- funzione crea_lezione(int id, int capacita_massima, char* nome, char* istruttore, char* orario)
        Precondizioni: nome e istruttore != NULL
        Postcondizioni: restituisce lezione = {id, capacita_massima, nome, istruttore, orario}
*/

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
    lezione->posti_occupati = 0;
    strcpy(lezione->orario, orario);
    strcpy(lezione->orario, orario);
    return lezione;
}

/*
    ---- funzione incrementa_posti_occupati
    Precondizione: lezione != NULL

*/

// Incrementa il numero di posti occupati per una lezione specifica
void incrementa_posti_occupati(Lezione lezione)
{
    lezione->posti_occupati++;
}

/*
    --- funzione get_capacita(Lezione lezione)
    Precondizione: lezione != NULL
    Postcondizione: restituisce lezione ->capacita_massima

*/

// Restituisce la capacità massima di una lezione
int get_capacita(Lezione lezione)
{
    return lezione->capacita_massima;
}

/*
    ----- funzione get_orario
        Precondizione: lezione !=NULL
        Postcondizione: restituisce lezione->orario
*/

char *get_orario(Lezione lezione)
{
    return lezione->orario;
}

/*
    ---- funzione get_posti_occupati(Lezione lezione)
        Precondizione: lezione != NULL
        Postcondizione: restituisce lezione->posti_occupati

*/

// Restituisce il numero di posti occupati per una lezione
int get_posti_occupati(Lezione lezione)
{
    return lezione->posti_occupati;
}

/*
    ---- funzione get_id_lezione(Lezione lezione)
        Precondizioni: lezione != NULL
        Postcondizioni: restituisce lezione->id_lezione

*/

int get_id_lezione(Lezione lezione)
{
    return lezione->id_lezione;
}
