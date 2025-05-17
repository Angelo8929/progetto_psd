#include "clienti.h"
#include "lezioni.h"

typedef struct PrenotazioneNode *PrenotazioniList;
typedef struct Prenotazione Prenotazione;
PrenotazioniList newPrenotazioniList();
int emptyPrenotazioniList(PrenotazioniList list);
PrenotazioniList creaPrenotazione(
    PrenotazioniList head_prenotazioni,
    LezioniList head_lista,
    hashtable h,
    int size_tabella,
    int id_cliente,
    int id_lezione,
    char orario[],
    int abbonamento_cliente_valido, // Semplificazione
    int capacita_lezione_attuale    // Semplificazione
);
int contaPrenotazioniAttivePerLezione(PrenotazioniList head_prenotazioni, int id_lezione);
void visualizzaPrenotazioniCliente(PrenotazioniList head_prenotazioni, int id_cliente);
void visualizzaTutteLePrenotazioni(PrenotazioniList head_prenotazioni);
void liberaListaPrenotazioni(PrenotazioniList head_prenotazioni);
