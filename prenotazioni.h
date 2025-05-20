#include "clienti.h"
#include "lezioni.h"

typedef struct PrenotazioneNode *PrenotazioniList;
typedef struct Prenotazione *Prenotazione;
PrenotazioniList newPrenotazioniList();
int emptyPrenotazioniList(PrenotazioniList list);
Prenotazione creaPrenotazione(
    PrenotazioniList head_prenotazioni,
    LezioniList head_lista,
    hashtable h,
    int size_tabella,
    int id_cliente,
    int id_lezione,
    char orario[]);

PrenotazioniList aggiungiPrenotazione(PrenotazioniList head_prenotazioni, Prenotazione prenotazione);
int contaPrenotazioniAttivePerLezione(PrenotazioniList head_prenotazioni, int id_lezione);
void visualizzaPrenotazioniCliente(PrenotazioniList head_prenotazioni, int id_cliente);
void visualizzaTutteLePrenotazioni(PrenotazioniList head_prenotazioni);
void liberaListaPrenotazioni(PrenotazioniList head_prenotazioni);
