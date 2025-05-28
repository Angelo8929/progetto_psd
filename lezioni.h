#include "list.h" // Tipo astratto per la lista di lezioni
typedef struct Lezione *Lezione;
typedef list LezioniList; // Tipo astratto per una lezione
#define NULLITEM 0
// ===============================
// Funzioni per la gestione delle lezioni
// ===============================

/*
    Funzione: crea_lezione
    Restituisce lezione = {id, capacita_massima, nome, istruttore, orario}
    Parametri:
        id: identificativo della lezione, intero
        capacita_massima: numero massimo di posti prenotabili della lezione, intero
        nome: nome della lezione, stringa
        istruttore: istruttore che tiene la lezione, stringa
        orario: orario in cui si tiene la lezione, stringa
*/

Lezione crea_lezione(int id, int capacita_massima, char *nome, char *istruttore, char *orario);

/*
    Funzione: visualizza_lezioni
    Stampa a video la lista delle lezioni
    Parametri:
        lezioni: lista lezioni
*/

void visualizza_lezioni(LezioniList lezioni);

/*
    Funzione: incrementa_posti_occupati
    Incrementa il campo posti_occupati di una lezione specifica a seguito di una prenotazione
    Parametri:
        lezione: istanza della struct Lezione
*/

void incrementa_posti_occupati(Lezione lezione);

/*
    Funzione: get_capacita
    Restituisce il campo capacita_massima di un' istanza della struct Lezione, intero
    Parametri:
        lezione: istanza della struct Lezione
*/

int get_capacita(Lezione lezione);

/*
    Funzione: get_posti_occupati
    Restituisce il campo posti_occupati di un' istanza della struct Lezione, intero
    Parametri:
        lezione: istanza della struct Lezione
*/

int get_posti_occupati(Lezione lezione);
/*
    Funzione: get_id_lezione
    Restituisce il campo id_lezione di un' istanza della struct Lezione, intero
    Parametri:
        lezione: istanza della struct Lezione
*/
int get_id_lezione(Lezione lezione);
/*
    Funzione: get_orario
    Restituisce il campo orario di un'istanza della struct Lezione, stringa
    Parametri:
        lezione: istanza della struct Lezione
*/
char *get_orario(Lezione lezione);
