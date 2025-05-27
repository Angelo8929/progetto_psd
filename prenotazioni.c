#include "lezioni.h"
#include "clienti.h"
#include "prenotazioni.h"
#include "utils.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STR 100

// ===============================
// Definizione delle strutture dati
// ===============================

// Struttura che rappresenta una singola prenotazione
struct Prenotazione
{
    int id_prenotazione;
    int id_cliente;
    int id_lezione;
    char orario[6];
};

// Nodo per la lista concatenata di prenotazioni

// Crea e restituisce una lista di prenotazioni vuota

// Conta il numero di prenotazioni attive per una lezione specifica dato il suo ID e ne restituisce il conteggio

// Funzione per visualizzare le prenotazioni di un cliente specifico

// Funzione per visualizzare tutte le prenotazioni nella lista di prenotazioni
void visualizza_prenotazioni(PrenotazioniList head_prenotazioni)
{
    PrenotazioniList current = head_prenotazioni;
    if (current == NULL)
    {
        printf("Nessuna prenotazione nel sistema.\n");
        return;
    }

    printf("\n--- Tutte le Prenotazioni nel Sistema ---\n");
    printf("ID Pren. | ID Cliente | ID Lezione \n");
    printf("----------------------------------------------------------------------\n");

    while (current != NULL)
    {
        Prenotazione p = (Prenotazione)getFirst(current);
        printf("%-8d | %-10d | %-10d |\n",
               p->id_prenotazione,
               p->id_cliente,
               p->id_lezione);
        current = tailList(current);
    }
    printf("----------------------------------------------------------------------\n\n");
}

void visualizza_prenotazioni_file(PrenotazioniList prenotazioni, char *nome_file)
{
    FILE *fp = fopen(nome_file, "w");
    if (fp == NULL)
    {
        perror("Errore in apertura del file\n");
        exit(1);
    }
    PrenotazioniList current = prenotazioni;
    if (current == NULL)
    {
        fprintf(fp, "Nessuna prenotazione nel sistema\n");
    }
    else
    {
        fprintf(fp, "Prenotazioni: \n");
        while (current != NULL)
        {
            Prenotazione p = (Prenotazione)getFirst(current);
            fprintf(fp, "\n");
            fprintf(fp, "ID prenotazione: %d\n", p->id_prenotazione);
            fprintf(fp, "ID cliente: %d\n", p->id_cliente);
            fprintf(fp, "ID lezione: %d", p->id_lezione);
            fprintf(fp, "\n");
            current = tailList(current);
        }
    }
    fclose(fp);
}

// Funzione per liberare la memoria occupata dalla lista di prenotazioni
void libera_prenotazioni(PrenotazioniList prenotazioni)
{
    while (prenotazioni != NULL)
    {
        Prenotazione p = (Prenotazione)getFirst(prenotazioni);
        free(p);
        prenotazioni = tailList(prenotazioni);
    }
}

// Funzione per creare una nuova prenotazione
// Restituisce un puntatore alla nuova prenotazione
Prenotazione crea_prenotazione(
    PrenotazioniList prenotazioni,
    LezioniList head_lista,
    hashtable h,
    int size_tabella,
    int id_cliente,
    int id_lezione,
    char orario[]
    // int abbonamento_cliente_valido, // Semplificazione
    // int capacita_lezione_attuale    // Semplificazione
)
{
    static int count_id_prenotazione = 0;

    // Verifica se il cliente e la lezione esistono
    if (cerca_cliente(h, id_cliente, size_tabella) == NULL)
    {
        fprintf(stderr, "Errore: Il cliente con ID %d non esiste.\n", id_cliente);
        return NULL;
    }
    Lezione lezione_attuale = cerca_lezione(head_lista, id_lezione);
    if (lezione_attuale == NULL)
    {

        fprintf(stderr, "Errore: La lezione con id %d non esiste.\n", id_lezione);
        return NULL;
    }

    // Verifica se il cliente ha un abbonamento valido
    if (!get_abbonamento(h, id_cliente, size_tabella))
    {
        fprintf(stderr, "Errore: Il cliente %d non ha un abbonamento valido.\n", id_cliente);
        return NULL;
    }

    int posti_occupati = get_posti_occupati(lezione_attuale); // Otteniamo il numero di posti occupait

    int capacita_max_lezione = get_capacita(lezione_attuale); // Otteniamo la capacità massima della lezione

    // Verifica se la lezione non accetta più prenotazioni
    if (posti_occupati >= capacita_max_lezione)
    {
        printf("Errore: La lezione %d è piena (Occupati: %d, Capacità: %d).\n",
               id_lezione, posti_occupati, capacita_max_lezione);
        return NULL;
    }

    // Verifica se il cliente è già prenotato per questa lezione
    PrenotazioniList temp = prenotazioni;
    while (temp != NULL)
    {
        Prenotazione p = (Prenotazione)getFirst(prenotazioni);
        if (p->id_cliente == id_cliente &&
            p->id_lezione == id_lezione)
        {
            printf("Errore: Il cliente %d è già prenotato per la lezione %d.\n", id_cliente, id_lezione);
            return NULL;
        }
        temp = tailList(temp);
    }

    Prenotazione prenotazione = malloc(sizeof(struct Prenotazione)); // Alloca memoria per una nuova prenotazione
    if (prenotazione == NULL)
    {
        perror("Errore malloc per PrenotazioneNode");
        exit(1); // o exit
    }

    prenotazione->id_prenotazione = count_id_prenotazione++;
    prenotazione->id_cliente = id_cliente;
    prenotazione->id_lezione = id_lezione;
    strcpy(prenotazione->orario, orario);
    incrementa_posti_occupati(lezione_attuale);

    return prenotazione; // Restituisce la nuova testa della lista
}

// Funzione per aggiungere una prenotazione alla lista di prenotazioni
// Restituisce la nuova lista di prenotazioni
