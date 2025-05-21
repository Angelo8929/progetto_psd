#include "lezioni.h"
#include "clienti.h"
#include "prenotazioni.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STR 100

// ===============================
// Definizione delle strutture dati
// ===============================

// Struttura che rappresenta una singola prenotazione
struct Prenotazione
{
    int id_prenotazione;
    int id_cliente;
    int id_lezione;
    char orario[6];
};

// Nodo per la lista concatenata di prenotazioni
struct PrenotazioneNode
{
    struct Prenotazione prenotazione;
    struct PrenotazioneNode *next;
};

// Crea e restituisce una lista di prenotazioni vuota
PrenotazioniList newPrenotazioniList()
{
    return NULL;
}

// Verifica se la lista di prenotazioni è vuota
int emptyPrenotazioniList(PrenotazioniList list)
{
    return list == NULL;
}

// Conta il numero di prenotazioni attive per una lezione specifica dato il suo ID e ne restituisce il conteggio
int contaPrenotazioniAttivePerLezione(PrenotazioniList head_prenotazioni, int id_lezione)
{
    int conteggio = 0;
    PrenotazioniList current = head_prenotazioni; // Inizializza il puntatore corrente alla testa della lista

    while (current != NULL) // Itera attraverso la lista di prenotazioni
    {
        if (current->prenotazione.id_lezione == id_lezione) // Se trova la prenotazione con l'ID lezione
        {
            conteggio++; // Incrementa il conteggio
        }
        current = current->next; // Passa alla prenotazione successiva altrimenti
    }
    return conteggio; 
}

// Funzione per visualizzare le prenotazioni di un cliente specifico
void visualizzaPrenotazioniCliente(PrenotazioniList head_prenotazioni, int id_cliente /*, LessonNode* head_lezioni per i nomi delle lezioni */)
{
    PrenotazioniList current = head_prenotazioni;
    int trovate = 0;

    printf("\n--- Prenotazioni per Cliente ID %d ---\n", id_cliente);
    printf("ID Prenotazione | ID Lezione | Data Prenotazione\n");
    printf("--------------------------------------------------\n");

    while (current != NULL)
    {
        if (current->prenotazione.id_cliente == id_cliente)
        {
           
            printf("%-15d | %-10d | %s\n", 
                   current->prenotazione.id_prenotazione,
                   current->prenotazione.id_lezione,
                   current->prenotazione.orario);
            trovate++;
        }
        current = current->next;
    }

    if (trovate == 0)
    {
        printf("Nessuna prenotazione attiva trovata per il cliente ID %d.\n", id_cliente);
    }
    printf("--------------------------------------------------\n\n");
}

// Funzione per visualizzare tutte le prenotazioni nella lista di prenotazioni
void visualizzaTutteLePrenotazioni(PrenotazioniList head_prenotazioni)
{
    PrenotazioniList current = head_prenotazioni;
    if (current == NULL)
    {
        printf("Nessuna prenotazione nel sistema.\n");
        return;
    }

    printf("\n--- Tutte le Prenotazioni nel Sistema ---\n");
    printf("ID Pren. | ID Cliente | ID Lezione | Stato     | Data Prenotazione\n");
    printf("----------------------------------------------------------------------\n");

    while (current != NULL)
    {

        printf("%-8d | %-10d | %-10d | %-9s |\n",
               current->prenotazione.id_prenotazione,
               current->prenotazione.id_cliente,
               current->prenotazione.id_lezione,
               current->prenotazione.orario);
        current = current->next;
    }
    printf("----------------------------------------------------------------------\n\n");
}

// Funzione per liberare la memoria occupata dalla lista di prenotazioni
void liberaListaPrenotazioni(PrenotazioniList head_prenotazioni)
{
    PrenotazioniList current = head_prenotazioni; 
    PrenotazioniList next_node;
    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

// Funzione per creare una nuova prenotazione
// Restituisce un puntatore alla nuova prenotazione
Prenotazione creaPrenotazione(
    PrenotazioniList head_prenotazioni,
    LezioniList head_lista,
    hashtable h,
    int size_tabella,
    int id_cliente,
    int id_lezione,
    char orario[]
    // int abbonamento_cliente_valido, // Semplificazione
    // int capacita_lezione_attuale    // Semplificazione
)
{
    static int count_id_prenotazione = 0;

    // Verifica se il cliente e la lezione esistono
    if (cercaCliente(h, id_cliente, size_tabella) == NULL)
    {
        printf("Errore: Il cliente con ID %d non esiste.\n", id_cliente);
        return NULL;
    }
    Lezione lezione_attuale = cercaLezione(head_lista, id_lezione);
    if (lezione_attuale == NULL)
    {

        printf("Errore: La lezione con id %d non esiste.\n", id_lezione);
        return NULL;
    }


    // Verifica se il cliente ha un abbonamento valido
    if (!getAbbonamento(h, id_cliente, size_tabella))
    {
        printf("Errore: Il cliente %d non ha un abbonamento valido.\n", id_cliente);
        return NULL;
    }


    int posti_occupati = getPostiOccupati(lezione_attuale); // Otteniamo il numero di posti occupait
    
    int capacita_max_lezione = getCapacita(lezione_attuale); // Otteniamo la capacità massima della lezione

    // Verifica se la lezione non accetta più prenotazioni
    if (posti_occupati >= capacita_max_lezione)
    {
        printf("Errore: La lezione %d è piena (Occupati: %d, Capacità: %d).\n",
               id_lezione, posti_occupati, capacita_max_lezione);
        return NULL;
    }

    // Verifica se il cliente è già prenotato per questa lezione
    PrenotazioniList temp = head_prenotazioni;
    while (temp != NULL)
    {
        if (temp->prenotazione.id_cliente == id_cliente &&
            temp->prenotazione.id_lezione == id_lezione)
        {
            printf("Errore: Il cliente %d è già prenotato per la lezione %d.\n", id_cliente, id_lezione);
            return NULL;
        }
        temp = temp->next;
    }

    Prenotazione prenotazione = malloc(sizeof(struct Prenotazione)); // Alloca memoria per una nuova prenotazione
    if (prenotazione == NULL)
    {
        perror("Errore malloc per PrenotazioneNode");
        exit(1); // o exit
    }

    prenotazione->id_prenotazione = count_id_prenotazione++; 
    prenotazione->id_cliente = id_cliente;
    prenotazione->id_lezione = id_lezione;
    strcpy(prenotazione->orario, orario);
    incrementaPostiOccupati(head_lista, id_lezione);

    return prenotazione; // Restituisce la nuova testa della lista
}

// Funzione per aggiungere una prenotazione alla lista di prenotazioni
// Restituisce la nuova lista di prenotazioni
PrenotazioniList aggiungiPrenotazione(PrenotazioniList prenotazioni, Prenotazione prenotazione)
{

    struct PrenotazioneNode *newPrenotazione = malloc(sizeof(struct PrenotazioneNode));
    if (newPrenotazione == NULL)
    {
        return prenotazioni;
    }
    newPrenotazione->prenotazione = *prenotazione;
    newPrenotazione->next = prenotazioni;
    prenotazioni = newPrenotazione;
    printf("Prenotazione ID %d creata con successo per cliente %d alla lezione %d.\n",
           prenotazioni->prenotazione.id_prenotazione, prenotazioni->prenotazione.id_cliente, prenotazioni->prenotazione.id_lezione);
    return prenotazioni;
}