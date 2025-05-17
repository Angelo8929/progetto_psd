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

PrenotazioniList newPrenotazioniList(){
    return NULL;
}

int emptyPrenotazioniList(PrenotazioniList list){
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

PrenotazioniList creaPrenotazione(
    PrenotazioniList head_prenotazioni,
    LezioniList head_lista,
    hashtable h,
    int size_tabella,
    int id_cliente,
    int id_lezione,
    char orario[],
    int abbonamento_cliente_valido, // Semplificazione
    int capacita_lezione_attuale    // Semplificazione
)
{
    static int count_id_prenotazione = 0;

    if (cercaCliente(h, id_cliente, size_tabella) == NULL)
    {
        printf("Errore: Il cliente con ID %d non esiste.\n", id_cliente);
        return head_prenotazioni;
    }
    if (!cercaLezione(head_lista, id_lezione))
    {
        printf("Errore: La lezione con id %d non esiste.\n", id_lezione);
        return head_prenotazioni;
    }

    // --- 1. Verifiche Preliminari ---
    // Nella realtà, qui interrogheresti i moduli Cliente e Lezione
    // Esempio:
    // if (!cliente_ha_abbonamento_valido(id_cliente)) {
    //     printf("Errore: Il cliente %d non ha un abbonamento valido.\n", id_cliente);
    //     return head_prenotazioni;
    // }
    if (!abbonamento_cliente_valido)
    {
        printf("Errore: Il cliente %d non ha un abbonamento valido.\n", id_cliente);
        return head_prenotazioni;
    }

    int posti_occupati = contaPrenotazioniAttivePerLezione(head_prenotazioni, id_lezione);
    // Esempio:
    // int capacita_max_lezione = get_capacita_lezione(id_lezione);
    // if (posti_occupati >= capacita_max_lezione) {
    //    printf("Errore: La lezione %d è piena.\n", id_lezione);
    //    return head_prenotazioni;
    // }
    if (posti_occupati >= capacita_lezione_attuale)
    {
        printf("Errore: La lezione %d è piena (Occupati: %d, Capacità: %d).\n",
               id_lezione, posti_occupati, capacita_lezione_attuale);
        return head_prenotazioni;
    }

    // (Opzionale) Verifica se il cliente è già prenotato per questa lezione
    PrenotazioniList temp = head_prenotazioni;
    while (temp != NULL)
    {
        if (temp->prenotazione.id_cliente == id_cliente &&
            temp->prenotazione.id_lezione == id_lezione)
        {
            printf("Errore: Il cliente %d è già prenotato per la lezione %d.\n", id_cliente, id_lezione);
            return head_prenotazioni;
        }
        temp = temp->next;
    }

    // --- 2. Crea il nuovo nodo prenotazione ---
    struct PrenotazioneNode *nuovo_nodo = malloc(sizeof(struct PrenotazioneNode));
    if (nuovo_nodo == NULL)
    {
        perror("Errore malloc per PrenotazioneNode");
        return head_prenotazioni; // o exit
    }

    nuovo_nodo->prenotazione.id_prenotazione = count_id_prenotazione++;
    nuovo_nodo->prenotazione.id_cliente = id_cliente;
    nuovo_nodo->prenotazione.id_lezione = id_lezione;
    strcpy(nuovo_nodo->prenotazione.orario, orario);
    incrementaPostiOccupati(head_lista, id_lezione);

    // Ora corrente

    // --- 3. Aggiungi in testa alla lista (più semplice) ---
    nuovo_nodo->next = head_prenotazioni;

    printf("Prenotazione ID %d creata con successo per cliente %d alla lezione %d.\n",
           nuovo_nodo->prenotazione.id_prenotazione, id_cliente, id_lezione);

    return nuovo_nodo; // Restituisce la nuova testa della lista
}