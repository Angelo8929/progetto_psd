#include "lezioni.h"
#include "clienti.h"
#include "prenotazioni.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STR 100
struct Prenotazione
{
    int id_prenotazione;
    int id_cliente;
    int id_lezione;
    char orario[6];
};

struct PrenotazioneNode
{
    struct Prenotazione prenotazione;
    struct PrenotazioneNode *next;
};

PrenotazioniList newPrenotazioniList()
{
    return NULL;
}

int emptyPrenotazioniList(PrenotazioniList list)
{
    return list == NULL;
}

int contaPrenotazioniAttivePerLezione(PrenotazioniList head_prenotazioni, int id_lezione)
{
    int conteggio = 0;
    PrenotazioniList current = head_prenotazioni;
    while (current != NULL)
    {
        if (current->prenotazione.id_lezione == id_lezione)
        {
            conteggio++;
        }
        current = current->next;
    }
    return conteggio;
}

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
            // Per convertire time_t in stringa leggibile:

            // Qui potresti usare id_lezione per cercare il nome della lezione dalla lista delle lezioni
            // e stamparlo invece dell'ID.
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

    // if (cercaCliente(h, id_cliente, size_tabella) == NULL)
    // {
    //     printf("Errore: Il cliente con ID %d non esiste.\n", id_cliente);
    //     return head_prenotazioni;
    // }
    Lezione lezione_attuale = cercaLezione(head_lista, id_lezione);
    if (lezione_attuale == NULL)
    {

        printf("Errore: La lezione con id %d non esiste.\n", id_lezione);
        return NULL;
    }

    // --- 1. Verifiche Preliminari ---
    // Nella realtà, qui interrogheresti i moduli Cliente e Lezione
    // Esempio:
    if (!getAbbonamento(h, id_cliente, size_tabella))
    {
        printf("Errore: Il cliente %d non ha un abbonamento valido.\n", id_cliente);
        return NULL;
    }

    // if (!getAbbonamento(h, id_cliente, size_tabella))
    // {
    //     printf("Errore: Il cliente %d non ha un abbonamento valido.\n", id_cliente);
    //     return head_prenotazioni;
    // }

    int posti_occupati = getPostiOccupati(lezione_attuale);
    // Esempio:
    int capacita_max_lezione = getCapacita(lezione_attuale);

    if (posti_occupati >= capacita_max_lezione)
    {
        printf("Errore: La lezione %d è piena (Occupati: %d, Capacità: %d).\n",
               id_lezione, posti_occupati, capacita_max_lezione);
        return NULL;
    }

    // (Opzionale) Verifica se il cliente è già prenotato per questa lezione
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

    Prenotazione prenotazione = malloc(sizeof(struct Prenotazione));
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

    // Ora corrente

    // --- 3. Aggiungi in testa alla lista (più semplice) ---

    return prenotazione; // Restituisce la nuova testa della lista
}

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