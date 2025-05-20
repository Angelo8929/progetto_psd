#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "abbonamenti.h"

void carica_clienti_file(char *nome_file, hashtable h);
LezioniList carica_lezioni_file(char *nome_file, LezioniList lezioni);
PrenotazioniList carica_prenotazioni_file(char *filename, PrenotazioniList prenotazioni, hashtable h, LezioniList lezioni);
