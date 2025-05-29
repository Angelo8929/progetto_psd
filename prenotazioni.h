

#include "clienti.h"
#include "lezioni.h"
#include "list.h"
typedef struct Prenotazione *Prenotazione; // Tipo astratto per una prenotazione
typedef list prenotazioni_list;            // Tipo astratto per la lista di prenotazioni

/*
    Funzione: crea_prenotazione
    Restituisce una prenotazione con id_prenotazione autoincrementante, e id_cliente e id_lezione indicati nei parametri
    Parametri:
        prenotazioni: lista prenotazioni
        lezioni: lista lezioni
        clienti: tabella hash clienti
        size_tabella_hash: dimensione tabella hash
        id_cliente: identificativo del cliente prenotante
        id_lezione: identificativo della lezione prenotata
        orario: orario in cui si tiene la lezione


*/
Prenotazione crea_prenotazione(
    prenotazioni_list prenotazioni,
    lezioni_list lezioni,
    hashtable clienti,
    int size_tabella_hash,
    int id_cliente,
    int id_lezione,
    char orario[]);

/*
    Funzione: visualizza_prenotazioni
    Stampa a video la lista delle prenotazioni
    Parametri:
        prenotazioni: la lista delle prenotazioni
*/
// Funzione per visualizzare tutte le prenotazioni nella lista di prenotazioni
void visualizza_prenotazioni(prenotazioni_list prenotazioni);

/*
    Funzione: get_id_prenotazione
    Restituisce l'id della prenotazione
    Parametri:
        p: istanza della struct Prenotazione

*/
int get_id_prenotazione(Prenotazione p);
/*
    Funzione: get_id_cliente_prenotazione
    Restituisce l'id del cliente prenotante, di tipo intero
    Parametri:
        p: istanza della struct Prenotazione

*/

int get_id_cliente_prenotazione(Prenotazione p);

/*
    Funzione: get_id_lezione_prenotazione
    Restituisce l'id della lezione prenotata, di tipo intero
    Parametri:
        p: istanza della struct Prenotazione

*/
int get_id_lezione_prenotazione(Prenotazione p);

/*
    Funzione: get_orario_prenotazione
    Restituisce l'orario della lezione prenotata, di tipo stringa
    Parametri:
        p: istanza della struct Prenotazione

*/
char *get_orario_prenotazione(Prenotazione p);
