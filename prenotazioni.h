#include "clienti.h"
#include "lezioni.h"

typedef struct PrenotazioneNode *PrenotazioniList; // Tipo astratto per la lista di prenotazioni
typedef struct Prenotazione *Prenotazione; // Tipo astratto per una prenotazione

// ===============================
// Funzioni per la gestione delle prenotazioni
// ===============================

// Crea una nuova lista di prenotazioni
    PrenotazioniList newPrenotazioniList();

//Verifica se la lista di prenotazioni è vuota
    int emptyPrenotazioniList(PrenotazioniList list);

// Crea una nuova prenotazione
    Prenotazione creaPrenotazione(
        PrenotazioniList head_prenotazioni,
        LezioniList head_lista,
        hashtable h,
        int size_tabella,
        int id_cliente,
        int id_lezione,
        char orario[]);

// Aggiunge una prenotazione alla lista
    PrenotazioniList aggiungiPrenotazione(PrenotazioniList head_prenotazioni, Prenotazione prenotazione);

// Conta il numero di prenotazioni attive per una lezione specifica dato il suo ID e ne restituisce il conteggio
    int contaPrenotazioniAttivePerLezione(PrenotazioniList head_prenotazioni, int id_lezione);

// Funzione per visualizzare le prenotazioni di un cliente specifico
    void visualizzaPrenotazioniCliente(PrenotazioniList head_prenotazioni, int id_cliente);

// Funzione per visualizzare tutte le prenotazioni nella lista di prenotazioni    
void visualizzaTutteLePrenotazioni(PrenotazioniList head_prenotazioni);

// Funzione per liberare la memoria occupata dalla lista di prenotazioni
void liberaListaPrenotazioni(PrenotazioniList head_prenotazioni);
