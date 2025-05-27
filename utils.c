#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX 100

// Funzione per caricare i dati delle lezioni da un file e aggiungerli alla lista
LezioniList carica_lezioni_file(char *nome_file, LezioniList lezioni)
{

    // Definzione delle variabili
    int id_lezione;
    char nome[MAX];
    char istruttore[MAX];
    int capacita_massima;
    char orario[6];

    // Apertura del file in lettura
    FILE *fp = fopen(nome_file, "r");
    if (fp == NULL) // Se il file non può essere aperto
    {
        perror("Errore nell'apertura del file"); // Stampa l'errore
        exit(1);
    }

    while (fscanf(fp, "%d %d %s %s %s", &id_lezione, &capacita_massima, nome, istruttore, orario) == 5) // Legge i dati dal file, il file deve contenere 5 campi
    {
        Lezione lezione = crea_lezione(id_lezione, capacita_massima, nome, istruttore, orario); // Crea una nuova lezione
        lezioni = consList(lezione, lezioni);                                                   // Aggiunge la lezione alla lista di lezioni
    }

    fclose(fp); // Chiude il file
    lezioni = reverseList(lezioni);
    return lezioni; // Restituisce la lista di lezioni
}

// Funzione per caricare i clienti da un file e aggiungerli alla hashtable
void carica_clienti_file(char *nome_file, hashtable clienti)
{
    // Definizione delle variabili
    int id_cliente;
    char nome[MAX];
    char cognome[MAX];
    int abbonamento;

    // Apertura del file in lettura
    FILE *fp = fopen(nome_file, "r");
    if (fp == NULL)
    {
        perror("Errore nell'apertura del file"); // Stampa l'errore se il file non può essere aperto
        exit(1);
    }

    while (fscanf(fp, "%d %s %s %d", &id_cliente, nome, cognome, &abbonamento) == 4) // Legge i dati dal file, il file deve contenere 4 campi
    {
        Cliente cliente = crea_cliente(id_cliente, nome, cognome, abbonamento); // Crea un nuovo cliente
        insert_hash(clienti, cliente);                                          // Aggiunge il cliente alla hashtable
    }

    fclose(fp); // Chiude il file
}

// Funzione per caricare le prenotazioni da un file e aggiungerle alla lista di prenotazioni
PrenotazioniList carica_prenotazioni_file(char *nome_file, PrenotazioniList prenotazioni, hashtable h, LezioniList lezioni)
{
    // Definizione delle variabili
    int id_cliente, id_lezione;
    char orario[6];

    // Apertura del file in lettura
    FILE *fp = fopen(nome_file, "r");
    if (fp == NULL)
    {
        perror("Errore nell'apertura del file"); // Stampa l'errore se il file non può essere aperto
        exit(1);
    }

    while (fscanf(fp, "%d %d %s", &id_cliente, &id_lezione, orario) == 3) // Legge i dati dal file, il file deve contenere 3 campi
    {
        Prenotazione prenotazione = crea_prenotazione(prenotazioni, lezioni, h, get_size(h), id_cliente, id_lezione, orario); // Crea una nuova prenotazione
        if (prenotazione == NULL)                                                                                             // Se la prenotazione non è valida
        {
            printf("Prenotazione non effettuata\n"); // Stampa un messaggio di errore
        }
        else
        {

            prenotazioni = consList(prenotazione, prenotazioni); // Aggiunge la prenotazione alla lista di prenotazioni altrimenti
        }
    }

    fclose(fp); // Chiude il file
    prenotazioni = reverseList(prenotazioni);
    return prenotazioni; // Restituisce la lista di prenotazioni
}

Lezione cerca_lezione(LezioniList lezioni, int id_lezione)
{
    LezioniList temp = lezioni;
    while (temp != NULL)
    {
        Lezione l = get_lezione_from_node(temp);
        if (get_id_lezione(l) == id_lezione)
        {
            return l;
        }
        temp = go_next(temp);
    }
    return NULL;
}

void visualizza_disponibilita_lezioni_file(LezioniList lezioni, char *nome_file)
{
    FILE *fp = fopen(nome_file, "a"); // "a" per aggiungere in fondo al file
    if (fp == NULL)
    {
        perror("Errore in apertura del file\n");
        exit(1);
    }

    if (lezioni == NULL)
    {
        fprintf(fp, "Nessuna lezione programmata.\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "--- Disponibilità lezioni dopo le prenotazioni ---\n");

    LezioniList curr = lezioni;
    while (curr != NULL)
    {
        Lezione l = get_lezione_from_node(curr);
        int posti_occupati = get_posti_occupati(l);
        int capacita = get_capacita(l);
        int posti_disponibili = capacita - posti_occupati;

        fprintf(fp, "ID Lezione: %d | Occupati: %d | Disponibili: %d | Capacita: %d\n",
                get_id_lezione(l), posti_occupati, posti_disponibili, capacita);

        curr = go_next(curr);
    }
    fclose(fp);
}