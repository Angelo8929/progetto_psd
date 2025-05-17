#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "abbonamenti.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void caricaClienti(hashtable h, char *filename){
    FILE *file=fopen(filename, "r");
    if(!file){
        perror("Errore nell'apertura del file");
        return;
    }

    int id,abbonamento;
    char nome[50],cognome[50];

    while(fscanf(file,"%d %s %s %d",&id,nome,cognome,&abbonamento)==4){
        Cliente nuovo = newCliente(id,nome,cognome,abbonamento);
        aggiungiCliente(h,nuovo);
    }
fclose(file);
}

