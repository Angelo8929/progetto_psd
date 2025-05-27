#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "abbonamenti.h"

// ===============================
// Funzioni per il caricamento dei dati da File
// ===============================

// Carica i clienti da un file e li aggiunge alla hashtable
void carica_clienti_file(char *nome_file, hashtable h);

// Carica le lezioni da un file e le aggiunge alla lista di lezioni
LezioniList carica_lezioni_file(char *nome_file, LezioniList lezioni);

// Carica le prenotazioni da un file e le aggiunge alla lista di prenotazioni
PrenotazioniList carica_prenotazioni_file(char *filename, PrenotazioniList prenotazioni, hashtable h, LezioniList lezioni);

Lezione cerca_lezione(LezioniList lezioni, int id_lezione);

void visualizza_disponibilita_lezioni_file(LezioniList lezioni, char *nome_file);
