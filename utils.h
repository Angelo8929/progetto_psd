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

lezioni_list carica_lezioni_file(char *nome_file, lezioni_list lezioni);

/*
    Funzione: carica_prenotazioni_file
    Restituisce la lista contenente le prenotazioni caricate da file
    Parametri:
        nome_file: nome del file in cui saranno contenute le prenotazioni da caricare
        prenotazioni: lista collegata dove verranno caricate le prenotazioni
        h: la tabella hash dei clienti, dove verranno effettuati i controlli relativi a abbonamento valido e cliente già prenotato
        lezioni: la lista delle lezioni, dove verrà effettuato il controllo relativo a lezione non esistente
*/

prenotazioni_list carica_prenotazioni_file(char *filename, prenotazioni_list prenotazioni, hashtable h, lezioni_list lezioni);

/*
    Funzione: cerca_lezione
    Restituisce l'istanza della struct Lezione tale che lezione->id_lezione = id_lezione specificato nei parametri
    Parametri:
        lezioni: lista collegata delle lezioni su cui iterare
        id_lezione: identificativo della lezione da ricercare

*/

Lezione cerca_lezione(lezioni_list lezioni, int id_lezione);

/*
    Funzione: visuaizza_disponibilita_lezioni_file
    Stampa sul file nome_file la disponibilità delle lezioni dopo una serie di prenotazioni
    Parametri:
        lezioni: la lista collegata delle lezioni da stampare su file
        nome_file: il file in cui verranno inserite le informazioni sulla disponibilità delle lezioni
*/

void visualizza_disponibilita_lezioni_file(lezioni_list lezioni, char *nome_file);

/*
    Funzione: visualizza_prenotazioni_file
    Stampa sul file nome_file le prenotazioni effettuate
    Parametri:
        prenotazioni: la lista collegata delle prenotazioni
        nome_file: il nome del file in cui verranno inserite le prenotazioni effettuate

*/

void visualizza_prenotazioni_file(prenotazioni_list prenotazioni, char *nome_file);

/*
    ---- funzione visualizza_lezione_piu_frequentata(prenotazioni_list prenotazioni, char* nome_file)
    Stampa i dati della lezione più frequentata, ovvero quella con il valore del campo di posti_occupati più alto
    Parametri:
        lezioni: la lista collegata da esaminare

*/
void visualizza_lezione_piu_frequentata(lezioni_list lezioni);