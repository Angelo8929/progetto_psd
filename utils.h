#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX 100

LezioniList carica_lezioni_file(char *nome_file)
{
    int id_lezione;
    char nome[MAX];
    char istruttore[MAX];
    int posti_occupati;
    char orario[6];
    FILE *fp = fopen(nome_file, "r");
}
#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "abbonamenti.h"

void caricaClienti(hashtable h, char *filename);
// LezioniList caricaLezioni(char *filename);
// PrenotazioniList caricaPrenotazioni(char *filename, PrenotazioniList pList,hashtable h,LezioniList lList);
