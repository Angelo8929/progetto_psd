#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "abbonamenti.h"

void caricaClienti(hashtable h, char *filename);
LezioniList caricaLezioni(char *filename);
PrenotazioniList caricaPrenotazioni(char *filename, PrenotazioniList prenotazioni, hashtable h, LezioniList lezioni);
