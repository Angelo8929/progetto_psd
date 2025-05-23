#define MAX_STR 50
#define MAX_POSTI 100
#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
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
struct LezioneNode
{
    struct Lezione lezione;   // Dati della lezione
    struct LezioneNode *next; // Puntatore al nodo successivo
};

// Crea e restituisce una lista di lezioni vuota.
LezioniList new_lezioni_list()
{
    return NULL;
}

// Verifica se la lista di lezioni è vuota.
int empty_lezioni_list(LezioniList lezioni)
{
    return lezioni == NULL;
}

// Aggiunge una lezione in testa alla lista.
LezioniList aggiungi_lezione(Lezione lezione, LezioniList lezioni)
{

    struct LezioneNode *newLezione = malloc(sizeof(struct LezioneNode)); // Alloca memoria per un nuovo nodo
    if (newLezione == NULL)
    {
        return lezioni;
    }
    newLezione->lezione = *lezione;
    newLezione->next = lezioni;
    lezioni = newLezione;
    return lezioni;
}

// Funzione per la visualizzazione della disponibilità delle lezioni
void visualizza_disponibilita_lezione(LezioniList lezioni)
{

    if (lezioni == NULL)
    {
        printf("Nessuna lezione programmata.\n");
        return;
    }

    printf("Disponibilita' Lezioni: \n");

    struct LezioneNode *curr = lezioni; // Inizializza il puntatore corrente alla testa della lista

    while (curr != NULL) // Itera attraverso la lista di lezioni
    {

        struct Lezione lezioneattuale = curr->lezione;    // Ottiene la lezione corrente
        int postiOccupati = lezioneattuale.postiOccupati; // Ottiene il numero di posti occupati per quella lezione
        int capacita = lezioneattuale.capacita_massima;   // Ottiene la capacità massima della lezione
        int postiDisponibili = capacita - postiOccupati;  // Calcola i posti disponibili

        // Stampa le informazioni della lezione corrente
        printf("\n");
        printf("Nome Lezione: %s\n", lezioneattuale.nome);
        printf("Nome Istruttore: %s\n", lezioneattuale.istruttore);
        printf("Posti Attualmente Occupati: %d\n", postiOccupati);
        printf("Capacità Totale Lezione: %d\n", capacita);
        printf("Posti Disponibili: %d\n", postiDisponibili);
        printf("\n");

        curr = curr->next;
    }
}

// Crea una nuova lezione e restituisce un puntatore ad essa
Lezione new_lezione(int id, int capacita_massima, char *nome, char *istruttore, char *orario)
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
void incrementa_posti_pccupati(LezioniList lezioni, int id_lezione)
{
    while (lezioni != NULL) // Itera attraverso la lista di lezioni
    {
        if (lezioni->lezione.id_lezione == id_lezione) // Se trova la lezione con l'ID specificato
        {
            lezioni->lezione.postiOccupati++; // Incrementa i posti occupati
            break;
        }
        lezioni = lezioni->next; // Se no, passa alla lezione successiva
    }
}

// Libera la memoria occupata dalla lista di lezioni
void libera_lezioni(LezioniList lezioni)
{

    while (lezioni != NULL)
    {
        LezioniList tmp = lezioni;
        lezioni = lezioni->next;
        free(tmp);
    }
}

// Restituisce la capacità massima di una lezione
int get_capacita(Lezione lezione)
{
    return lezione->capacita_massima;
}

// Cerca una lezione specifica nella lista di lezioni
Lezione cerca_lezione(LezioniList lezioni, int id_lezione)
{
    LezioniList temp = lezioni; // Inizializza un puntatore temporaneo alla testa della lista
    while (temp != NULL)
    {
        if (temp->lezione.id_lezione == id_lezione)
        {
            return &(temp->lezione); // Restituisce il puntatore alla lezione trovata
        }
        else
        {
            temp = temp->next; // Passa alla lezione successiva se non trovata
        }
    }
    return NULL;
}

// Restituisce il numero di posti occupati per una lezione
int get_posti_occupati(Lezione lezione)
{
    return lezione->postiOccupati;
}
