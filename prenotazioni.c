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

/*
    ---- funzione visualizza_prenotazioni(prenotazioni_list prenotazioni)
        Precondizione: sempre verificata
        Postcondizioni: stampa a video tutte le prenotazioni, scorrendo la lista collegata


*/

void visualizza_prenotazioni(prenotazioni_list head_prenotazioni)
{
    prenotazioni_list current = head_prenotazioni;
    if (current == NULL)
    {
        printf("Nessuna prenotazione nel sistema.\n");
        return;
    }

    printf("\n--- Tutte le Prenotazioni nel Sistema ---\n");
    printf("ID Pren. | ID Cliente | ID Lezione | Orario\n");
    printf("----------------------------------------------------------------------\n");

    while (current != NULL)
    {
        Prenotazione p = (Prenotazione)get_first(current);
        printf("%-8d | %-10d | %-10d | %-8s\n",
               p->id_prenotazione,
               p->id_cliente,
               p->id_lezione,
               p->orario);
        current = tail_list(current);
    }
    printf("----------------------------------------------------------------------\n\n");
}

/*
    --- funzione crea_prenotazione(prenotazioni_list prenotazioni,
                                   lezioni_list lezioni,
                                   hashtable clienti,
                                   int size_tabella_hash,
                                   int id_cliente,
                                   int id_lezione,
                                   char[] orario)

                Precondizioni: lezioni != NULL, clienti != NULL, size_tabella_hash > 0, orario != NULL
                Postcondizioni: restituisce prenotazione = {id_prenotazione, id_cliente, id_lezione}

*/
Prenotazione crea_prenotazione(
    prenotazioni_list prenotazioni,
    lezioni_list head_lista,
    hashtable h,
    int size_tabella_hash,
    int id_cliente,
    int id_lezione,
    char orario[])
{
    static int count_id_prenotazione = 0; // variabile statica per mantenere il conteggio delle prenotazioni

    // Verifica se il cliente e la lezione esistono
    if (cerca_cliente(h, id_cliente, size_tabella_hash) == NULL)
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
    if (!get_abbonamento(h, id_cliente, size_tabella_hash))
    {
        fprintf(stderr, "Errore: Il cliente %d non ha un abbonamento valido.\n", id_cliente);
        return NULL;
    }

    int posti_occupati = get_posti_occupati(lezione_attuale); // Otteniamo il numero di posti occupati

    int capacita_max_lezione = get_capacita(lezione_attuale); // Otteniamo la capacità massima della lezione

    // Verifica se la lezione non accetta più prenotazioni
    if (posti_occupati >= capacita_max_lezione)
    {
        fprintf(stderr, "Errore: La lezione %d e' piena (Occupati: %d, Capacita': %d).\n",
                id_lezione, posti_occupati, capacita_max_lezione);
        return NULL;
    }

    // Verifica se il cliente è già prenotato per questa lezione
    prenotazioni_list temp = prenotazioni;
    while (temp != NULL)
    {
        Prenotazione p = (Prenotazione)get_first(temp);
        if (p->id_cliente == id_cliente &&
            p->id_lezione == id_lezione)
        {
            printf("Errore: Il cliente %d e' gia' prenotato per la lezione %d.\n", id_cliente, id_lezione);
            return NULL;
        }
        temp = tail_list(temp);
    }

    Prenotazione prenotazione = malloc(sizeof(struct Prenotazione)); // Alloca memoria per una nuova prenotazione
    if (prenotazione == NULL)
    {
        perror("Errore malloc per PrenotazioneNode");
        exit(1); // uscita forzata
    }

    prenotazione->id_prenotazione = count_id_prenotazione++;
    prenotazione->id_cliente = id_cliente;
    prenotazione->id_lezione = id_lezione;
    strcpy(prenotazione->orario, orario);
    incrementa_posti_occupati(lezione_attuale);

    return prenotazione; // Restituisce la nuova testa della lista
}

/*
    ---- funzione get_id_prenotazione(Prenotazione p)
        Precondizioni: p != NULL
        Postcondizioni: restituisce p->id_prenotazione

*/
int get_id_prenotazione(Prenotazione p)
{
    return p->id_prenotazione;
}

/*
    ---- funzione get_id_cliente_prenotazione(Prenotazione p)
        Precondizioni: p != NULL
        Postcondizioni: restituisce p->id_cliente

*/

int get_id_cliente_prenotazione(Prenotazione p)
{
    return p->id_cliente;
}

/*
    ---- funzione get_id_lezione_prenotazione(Prenotazione p)
        Precondizioni: p != NULL
        Postcondizioni: restituisce p->id_lezione

*/

int get_id_lezione_prenotazione(Prenotazione p)
{
    return p->id_lezione;
}

/*
    ---- funzione get_orario_prenotazione(Prenotazione p)
        Precondizioni: p != NULL
        Postcondizioni: restituisce p->orario

*/

char *get_orario_prenotazione(Prenotazione p)
{
    return p->orario;
}