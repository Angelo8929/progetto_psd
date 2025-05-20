#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX 100

LezioniList carica_lezioni_file(char *nome_file, LezioniList lezioni)
{
    int id_lezione;
    char nome[MAX];
    char istruttore[MAX];
    int capacita_massima;
    char orario[6];
    FILE *fp = fopen(nome_file, "r");
    while (fscanf(fp, "%d %d %s %s %s", &id_lezione, &capacita_massima, nome, istruttore, orario) != 5)
    {
        Lezione lezione = newLezione(id_lezione, capacita_massima, nome, istruttore, orario);
        lezioni = aggiungiLezione(lezione, lezioni);
    }
    fclose(fp);
    return lezioni;
}

void carica_clienti_file(char *nome_file, hashtable h)
{
    int id_cliente;
    char nome[MAX];
    char cognome[MAX];
    int abbonamento;
    FILE *fp = fopen(nome_file, "r");
    while (fscanf(fp, "%d %s %s %d", &id_cliente, nome, cognome, &abbonamento) == 4)
    {
        Cliente cliente = newCliente(id_cliente, nome, cognome, abbonamento);
        aggiungiCliente(h, cliente);
    }
    fclose(fp);
}

PrenotazioniList carica_prenotazioni_file(char *nome_file, PrenotazioniList prenotazioni, hashtable h, LezioniList lezioni)
{
    int id_cliente, id_lezione;
    char orario[6];
    FILE *fp = fopen(nome_file, "r");
    while (fscanf(fp, "%d %d %s", &id_cliente, &id_lezione, orario) != 3)
    {
        Prenotazione prenotazione = creaPrenotazione(prenotazioni, lezioni, id_cliente, id_lezione, orario);
        prenotazioni = aggiungiPrenotazione(prenotazioni, prenotazione);
    }
    fclose(fp);
    return prenotazioni;
}