#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX 100

/*
    ----- funzione carica_lezioni_file(char* nome file, lezioni_list lezioni)
        Precondizioni: nome_file != NULL
        Postcondizioni: La funzione, leggendo il file riga per riga mediante fscanf,
                        leggerà tutti i campi della lezione, che saranno dati in pasto alla funzione crea_lezione per creare l’istanza della struct,
                        e infine chiamerà la funzione cons_list per aggiungere la lezione nella lista collegata,
                        che sarà il valore restituito dalla funzione

*/

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

    fclose(fp);                      // Chiude il file
    lezioni = reverse_list(lezioni); // con la funzione di reverse, facciamo in modo che in testa alla lista ci sia la prima lezione inserita
    return lezioni;                  // Restituisce la lista di lezioni
}

/*
    ---- funzione carica_clienti_file(char* nome_file, hashtable clienti)
        Precondizione: nome_file != NULL
        Postcondizione: la funzione leggerà il file riga per riga tramite fscanf.
                        Cosi facendo otterrà i campi della struct Cliente
                        che saranno dati in pasto alla funzione crea_cliente per creare la relativa istanza
                        Infine verrà chiamata insert_hash per aggiungere il cliente alla tabella hash

*/

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

/*
    ---- funzione carica_prenotazioni_file(char* nome_file, prenotazioni_list prenotazioni, hashtable clienti, lezioni_list lezioni)
        Precondizioni: nome_file != NULL
        Postcondizioni: la funzione leggerà il file riga per riga tramite fscanf.
                        Cosi facendo otterrà i campi della struct prenotazione
                        che saranno dati in pasto alla funzione crea_prenotazione (insieme a lezioni e clienti per i vari controlli)
                        per creare la relativa istanza.
                        Infine verrà chiamata insert_hash per aggiungere il cliente alla tabella hash


*/

prenotazioni_list carica_prenotazioni_file(char *nome_file, prenotazioni_list prenotazioni, hashtable clienti, lezioni_list lezioni)
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
        Prenotazione prenotazione = crea_prenotazione(prenotazioni, lezioni, clienti, get_size(clienti), id_cliente, id_lezione, orario); // Crea una nuova prenotazione
        if (prenotazione == NULL)                                                                                                         // Se la prenotazione non è valida
        {
            printf("Prenotazione non effettuata\n"); // Stampa un messaggio di errore
        }
        else
        {
            printf("Prenotazione effettuata con successo per cliente %d alla lezione %d\n", id_cliente, id_lezione);
            prenotazioni = cons_list(prenotazione, prenotazioni); // Aggiunge la prenotazione alla lista di prenotazioni altrimenti
        }
    }

    fclose(fp);                                // Chiude il file
    prenotazioni = reverse_list(prenotazioni); // per far si che l'elemento in testa alla lista sia effettivamente il primo inserito
    return prenotazioni;                       // Restituisce la lista di prenotazioni
}

/*
    ---- funzione cerca_lezione(lezioni_list lezioni, int id_lezione)
        Precondizioni: lezioni != NULL
        Postcondizioni: restituisce la lezione con id_lezione specificato tra i parametri,
                        scorrendo la lista collegata. Se la lezione non viene trovata,
                        restituisce NULL

*/

Lezione cerca_lezione(lezioni_list lezioni, int id_lezione)
{
    lezioni_list temp = lezioni;
    while (temp != NULL)
    {
        Lezione l = get_first(temp);         // ottiene lezione in testa alla lista
        if (get_id_lezione(l) == id_lezione) // se i due identificativi combaciano
        {
            return l; // restituisce la lezione corrente
        }
        temp = tail_list(temp); // scorre la lista collegata, perchè viene rimosso il primo elemento
    }
    return NULL; // se la lezione non viene trovata, oppure se la lista è vuota
}

/*
    ---- funzione visualizza_disponibilita_lezioni_file(lezioni_list lezioni, char* nome_file)
                    Precondizioni: nome_file != NULL
                    Postcondizioni: stampa sul file nome_file la disponibilità aggiornata delle lezioni dopo ogni test case,
                                    scorrendo la lista collegata

*/

void visualizza_disponibilita_lezioni_file(lezioni_list lezioni, char *nome_file)
{
    FILE *fp = fopen(nome_file, "a"); // "a" per aggiungere in fondo al file
    if (fp == NULL)                   // gestione apertura file non andata a buon fine
    {
        perror("Errore in apertura del file\n");
        exit(1);
    }

    if (lezioni == NULL) // gestione lista lezioni vuota
    {
        fprintf(fp, "Nessuna lezione programmata.\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "--- Disponibilità lezioni dopo le prenotazioni ---\n");

    lezioni_list curr = lezioni;
    while (curr != NULL)
    {
        Lezione l = get_first(curr); // ottiene la lezione in testa alla lista

        // ottiene i campi
        int posti_occupati = get_posti_occupati(l);
        int capacita = get_capacita(l);
        int posti_disponibili = capacita - posti_occupati;
        char *orario = get_orario(l);

        fprintf(fp, "ID Lezione: %d | Occupati: %d | Disponibili: %d | Capacita: %d | Orario: %s\n",
                get_id_lezione(l), posti_occupati, posti_disponibili, capacita, orario);

        curr = tail_list(curr); // scorre la lista
    }
    fclose(fp);
}

/*
    ---- funzione visualizza_prenotazioni_file(prenotazioni_list prenotazioni, char* nome_file)
        Precondizioni: nome_file != NULL
        Postcondizioni: stampa sul file nome_file le prenotazioni correttamente registrate sul file output di ogni test case
*/

void visualizza_prenotazioni_file(prenotazioni_list prenotazioni, char *nome_file)
{
    FILE *fp = fopen(nome_file, "w"); // gestione apertura file non andata a buon fine
    if (fp == NULL)
    {
        perror("Errore in apertura del file\n");
        exit(1);
    }
    prenotazioni_list current = prenotazioni;
    if (current == NULL) // gestione lista prenotazioni vuota
    {
        fprintf(fp, "Nessuna prenotazione nel sistema\n");
    }
    else
    {
        fprintf(fp, "Prenotazioni: \n");
        while (current != NULL)
        {
            Prenotazione p = (Prenotazione)get_first(current); // ottiene la prenotazione in testa alla lista
            fprintf(fp, "\n");
            fprintf(fp, "ID prenotazione: %d\n", get_id_prenotazione(p));
            fprintf(fp, "ID cliente: %d\n", get_id_cliente_prenotazione(p));
            fprintf(fp, "ID lezione: %d\n", get_id_lezione_prenotazione(p));
            fprintf(fp, "Orario: %s", get_orario_prenotazione(p));
            fprintf(fp, "\n");
            current = tail_list(current); // scorre la lista
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/*
    ---- funzione visualizza_lezione_piu_frequentata(lezioni_list lezioni)
        Precondizione: lezioni != NULL
        Postcondizione: stampa a video i dati dell lezione più frequentata,
                        confrontando il campo posti_occupati di ciascuna lezione con una variabile posti_max
                        Se i posti occupati della lezione attuale sono maggiori di posti_max, li assegna a quest'ultima,
                        e lezione_max che conterrà i dati della lezione più frequentata, si aggiornerà di conseguenza

*/

void visualizza_lezione_piu_frequentata(lezioni_list lezioni)
{
    if (lezioni == NULL) // gestione lista lezioni vuota
    {
        printf("La lista di lezioni e' vuota\n");
        return;
    }

    lezioni_list curr = lezioni;
    int posti_max = 0;
    Lezione lezione_max = NULL; // inizialmente lezione max rappresenta la lezione vuota
    while (curr != NULL)
    {
        Lezione l = get_first(curr);                         // viene entratto il primo elemento
        if (get_posti_occupati(get_first(curr)) > posti_max) // se i posti occupati della lezione attuale sono maggiori di posti max
        {
            posti_max = get_posti_occupati(get_first(curr)); // li assegna a posti_max
            lezione_max = l;                                 // la lezione attuale è la nuova lezione_max
        }
        curr = tail_list(curr); // scorre la lista
    }

    if (lezione_max != NULL) // se viene trovata almeno una lezione con posti_occupati > 0
    {
        printf("La lezione piu'frequentata e': \n");
        printf("Nome: %s\n", get_nome(lezione_max));
        printf("ID: %d\n", get_id_lezione(lezione_max));
        printf("Posti occupati: %d\n", get_posti_occupati(lezione_max));
    }
    else
    {
        printf("Nessuna lezione ha posti occupati. \n"); // se nessuna lezione risulta prenotata
    }
}