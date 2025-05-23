#include "clienti.h"
#include "lezioni.h"

typedef struct PrenotazioneNode *PrenotazioniList; // Tipo astratto per la lista di prenotazioni
typedef struct Prenotazione *Prenotazione;         // Tipo astratto per una prenotazione

// ===============================
// Funzioni per la gestione delle prenotazioni
// ===============================

// Crea una nuova lista di prenotazioni
PrenotazioniList new_prenotazioni_list();

// Verifica se la lista di prenotazioni è vuota
int empty_prenotazioni_list(PrenotazioniList prenotazioni);

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
PrenotazioniList aggiungi_prenotazione(PrenotazioniList prenotazioni, Prenotazione prenotazione);

// Conta il numero di prenotazioni attive per una lezione specifica dato il suo ID e ne restituisce il conteggio
int contaPrenotazioniAttivePerLezione(PrenotazioniList prenotazioni, int id_lezione);

// Funzione per visualizzare le prenotazioni di un cliente specifico
void visualizza_prenotazioni_cliente(PrenotazioniList prenotazioni, int id_cliente);

// Funzione per visualizzare tutte le prenotazioni nella lista di prenotazioni
void visualizza_prenotazioni(PrenotazioniList prenotazioni);

// Funzione per liberare la memoria occupata dalla lista di prenotazioni
void libera_prenotazioni(PrenotazioniList prenotazioni);
