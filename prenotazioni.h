#include "clienti.h"
#include "lezioni.h"

typedef struct PrenotazioneNode *PrenotazioniList;
typedef struct Prenotazione Prenotazione;
PrenotazioniList newPrenotazioniList();
int emptyPrenotazioniList(PrenotazioniList list);
int aggiungiPrenotazione(PrenotazioniList list, struct Prenotazione prenotazione);
int contaPrenotazioniPerLezione(PrenotazioniList head_prenotazioni, int id_lezione);
void visualizzaPrenotazioniCliente(PrenotazioniList head_prenotazioni, int id_cliente);
void visualizzaTutteLePrenotazioni(PrenotazioniList head_prenotazioni);
void liberaListaPrenotazioni(PrenotazioniList head_prenotazioni);
