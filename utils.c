#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX 100

LezioniList carica_lezioni_file(char *nome_file, LezioniList head)
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
        head = aggiungiLezione(lezione, head);
    }
    return head;
}

int carica_clienti_file(char *nome_file, hashtable h)
{
    int id_cliente;
    char nome[MAX];
    char cognome[MAX];
    int abbonamento;
    FILE *fp = fopen(nome_file, "r");
    while (fscanf(fp, "%d %s %s %d", &id_cliente, nome, cognome, &abbonamento) != 4)
    {
        Cliente cliente = newCliente(id_cliente, nome, cognome, abbonamento);
        aggiungiCliente(h, cliente);
    }
}
