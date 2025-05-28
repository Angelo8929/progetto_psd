#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"

// ===============================
// Funzioni di utilità
// ===============================

/*
    Funzione: carica_clienti_file
    Carica i clienti da un file e li aggiunge alla hashtable
    Parametri:
        nome_file: nome del file in cui saranno contenuti i clienti da caricare
        h: hashtable in cui verranno caricati i clienti

*/

void carica_clienti_file(char *nome_file, hashtable h);

/*
    Funzione: carica_lezioni_file
    Restituisce la lista contenente le lezioni caricate da file
    Parametri:
        nome_file: nome del file in cui saranno contenute le lezioni da caricare
        lezioni: lista collegata dove verranno caricate le lezioni
*/

LezioniList carica_lezioni_file(char *nome_file, LezioniList lezioni);

/*
    Funzione: carica_prenotazioni_file
    Restituisce la lista contenente le prenotazioni caricate da file
    Parametri:
        nome_file: nome del file in cui saranno contenute le prenotazioni da caricare
        prenotazioni: lista collegata dove verranno caricate le prenotazioni
        h: la tabella hash dei clienti, dove verranno effettuati i controlli relativi a abbonamento valido e cliente già prenotato
        lezioni: la lista delle lezioni, dove verrà effettuato il controllo relativo a lezione non esistente
*/

PrenotazioniList carica_prenotazioni_file(char *filename, PrenotazioniList prenotazioni, hashtable h, LezioniList lezioni);

/*
    Funzione: cerca_lezione
    Restituisce l'istanza della struct Lezione tale che lezione->id_lezione = id_lezione specificato nei parametri
    Parametri:
        lezioni: lista collegata delle lezioni su cui iterare
        id_lezione: identificativo della lezione da ricercare

*/

Lezione cerca_lezione(LezioniList lezioni, int id_lezione);

/*
    Funzione: visuaizza_disponibilita_lezioni_file
    Stampa sul file nome_file la disponibilità delle lezioni dopo una serie di prenotazioni
    Parametri:
        lezioni: la lista collegata delle lezioni da stampare su file
        nome_file: il file in cui verranno inserite le informazioni sulla disponibilità delle lezioni
*/

void visualizza_disponibilita_lezioni_file(LezioniList lezioni, char *nome_file);

/*
    Funzione: visualizza_prenotazioni_file
    Stampa sul file nome_file le prenotazioni effettuate
    Parametri:
        prenotazioni: la lista collegata delle prenotazioni
        nome_file: il nome del file in cui verranno inserite le prenotazioni effettuate

*/

void visualizza_prenotazioni_file(PrenotazioniList prenotazioni, char *nome_file);
