#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX 100

// Funzione per caricare i dati delle lezioni da un file e aggiungerli alla lista
lezioni_list carica_lezioni_file(char *nome_file, lezioni_list lezioni)
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
        lezioni = cons_list(lezione, lezioni);                                                  // Aggiunge la lezione alla lista di lezioni
    }

    fclose(fp); // Chiude il file
    lezioni = reverse_list(lezioni);
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
prenotazioni_list carica_prenotazioni_file(char *nome_file, prenotazioni_list prenotazioni, hashtable h, lezioni_list lezioni)
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
            printf("Prenotazione effettuata con successo per cliente %d alla lezione %d\n", id_cliente, id_lezione);
            prenotazioni = cons_list(prenotazione, prenotazioni); // Aggiunge la prenotazione alla lista di prenotazioni altrimenti
        }
    }

    fclose(fp); // Chiude il file
    prenotazioni = reverse_list(prenotazioni);
    return prenotazioni; // Restituisce la lista di prenotazioni
}

Lezione cerca_lezione(lezioni_list lezioni, int id_lezione)
{
    lezioni_list temp = lezioni;
    while (temp != NULL)
    {
        Lezione l = get_first(temp);
        if (get_id_lezione(l) == id_lezione)
        {
            return l;
        }
        temp = tail_list(temp);
    }
    return NULL;
}

void visualizza_disponibilita_lezioni_file(lezioni_list lezioni, char *nome_file)
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

    lezioni_list curr = lezioni;
    while (curr != NULL)
    {
        Lezione l = get_first(curr);
        int posti_occupati = get_posti_occupati(l);
        int capacita = get_capacita(l);
        int posti_disponibili = capacita - posti_occupati;
        char *orario = get_orario(l);

        fprintf(fp, "ID Lezione: %d | Occupati: %d | Disponibili: %d | Capacita: %d | Orario: %s\n",
                get_id_lezione(l), posti_occupati, posti_disponibili, capacita, orario);

        curr = tail_list(curr);
    }
    fclose(fp);
}

void visualizza_prenotazioni_file(prenotazioni_list prenotazioni, char *nome_file)
{
    FILE *fp = fopen(nome_file, "w");
    if (fp == NULL)
    {
        perror("Errore in apertura del file\n");
        exit(1);
    }
    prenotazioni_list current = prenotazioni;
    if (current == NULL)
    {
        fprintf(fp, "Nessuna prenotazione nel sistema\n");
    }
    else
    {
        fprintf(fp, "Prenotazioni: \n");
        while (current != NULL)
        {
            Prenotazione p = (Prenotazione)get_first(current);
            fprintf(fp, "\n");
            fprintf(fp, "ID prenotazione: %d\n", get_id_prenotazione(p));
            fprintf(fp, "ID cliente: %d\n", get_id_cliente_prenotazione(p));
            fprintf(fp, "ID lezione: %d\n", get_id_lezione_prenotazione(p));
            fprintf(fp, "Orario: %s", get_orario_prenotazione(p));
            fprintf(fp, "\n");
            current = tail_list(current);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}