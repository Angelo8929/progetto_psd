#include "clienti.h"
#include "lezioni.h"
#include "list.h" // Tipo astratto per la lista di prenotazioni
typedef struct Prenotazione *Prenotazione;
typedef list PrenotazioniList; // Tipo astratto per una prenotazione

// ===============================
// Funzioni per la gestione delle prenotazioni
// ===============================

// Crea una nuova lista di prenotazioni

// Verifica se la lista di prenotazioni è vuota

// Crea una nuova prenotazione
Prenotazione crea_prenotazione(
    PrenotazioniList prenotazioni,
    LezioniList lezioni,
    hashtable clienti,
    int size_tabella,
    int id_cliente,
    int id_lezione,
    char orario[]);

// Aggiunge una prenotazione alla lista

// Conta il numero di prenotazioni attive per una lezione specifica dato il suo ID e ne restituisce il conteggio

// Funzione per visualizzare le prenotazioni di un cliente specifico

// Funzione per visualizzare tutte le prenotazioni nella lista di prenotazioni
void visualizza_prenotazioni(PrenotazioniList prenotazioni);

void visualizza_prenotazioni_file(PrenotazioniList prenotazioni, char *nome_file);

// Funzione per liberare la memoria occupata dalla lista di prenotazioni
void libera_prenotazioni(PrenotazioniList prenotazioni);
