#define MAX 100

#include "clienti.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ===============================
// Definizione delle strutture dati
// ===============================

// Definizione della struttura Cliente
struct Cliente
{
    int id;
    char nome[MAX];
    char cognome[MAX];
    int abbonamento;
    struct Cliente *next; // Puntatore al prossimo cliente nella lista (per gestione collisioni nella hashtable)
};

struct hash
{
    int size;               // Dimensione della tabella
    struct Cliente **table; // Array di puntatori a clienti (liste concatenate)
};

/*
    --- funzione new_hashtable(int size) -----
    precondizioni: size > 0
    postcondizioni: restituisce una nuova hashtable di dimensione size, e inizializza le entry della tabella, ovvero i puntatori a ogni lista collegata, a NULL
*/

hashtable new_hashtable(int size)
{
    hashtable h = (struct hash *)malloc(sizeof(struct hash));
    h->size = size;
    h->table = (struct Cliente **)calloc(size, sizeof(struct Cliente *)); // Inizializza con NULL
    return h;
}

/*
    ---- funzione insert_hash(hashtable h, Cliente cliente)
    precondizione: cliente != NULL
    postcondizione: restituisce 1 se il cliente è stato inserito correttamente nala tabella hash, altrimenti 0 se è gia presente
*/

int insert_hash(hashtable h, Cliente cliente)
{
    if (cliente == NULL)
    {
        fprintf(stderr, "Errore: il cliente non è valido.\n");
        return 0;
    }

    int idx = hash_fun(cliente->id, h->size); // Calcola indice tramite funzione hash
    Cliente head = h->table[idx];             // Ottiene la lista corrente nella posizione calcolata
    Cliente curr = head;

    // Controlla se il cliente esiste già
    while (curr)
    {
        if (curr->id == cliente->id)
            return 0; // Cliente già presente
        curr = curr->next;
    }

    // Inserimento in testa alla lista (gestione collisioni con chaining)
    cliente->next = head;
    h->table[idx] = cliente;
    return 1;
}

/*
    ---- funzione hash_fun (int id_cliente, int size_tabella_hash)
        precondizione: size > 0
        postcondizione: restituisce il valore hash (indice della tabella) della chiave id_cliente, utilizzando l'operazione di modulo
*/

int hash_fun(int k, int m)
{
    return k % m;
}

/*
    ----- funzione crea_cliente(int id, char nome[], char cognome[], int abbonamento)
        precondizioni: nome e cognome != NULL
        postcondizioni: restituisce cliente = {id, nome, cognome, abbonamento}

*/

Cliente crea_cliente(int id, char nome[], char cognome[], int abbonamento)
{
    Cliente nuovo = malloc(sizeof(struct Cliente));
    nuovo->id = id;
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    nuovo->abbonamento = abbonamento;
    nuovo->next = NULL;
    return nuovo;
}

/*
    ---- funzione get_id_cliente(Cliente cliente)
        precondizioni: cliente != NULL
        postcondizioni: restituisce il campo id del cliente specificato
*/

int get_id_cliente(Cliente cliente)
{
    return cliente->id;
}

/*
    --- funzione cerca_cliente(hashtable clienti, int id_cliente, int size_tabella)
        precondizioni: clienti != NULL
        postcondizioni: ricerca e restituisce il cliente avente l'id specificato, ricercando nella lista collegata corrispondente al suo valore hash

*/

Cliente cerca_cliente(hashtable clienti, int id_cliente, int size_tabella)
{

    if (clienti == NULL || clienti->table == NULL) // Se la hashtable non è inizializzata o i clienti non sono stati caricati
        return NULL;                               // Restituisce NULL

    int idx = hash_fun(id_cliente, size_tabella); // calcola indice tramite funzione di hash
    struct Cliente *curr = clienti->table[idx];   // lista corrente nella posizione calcolata

    while (curr != NULL)
    {
        if (curr->id == id_cliente)
            return curr;
        curr = curr->next;
    }
    return NULL; // Cliente non trovato
}

/*
    --- funzione visualizza_clienti(hashtable clienti)
        precondizioni: clienti != NULL
        postcondizioni: stampa tutti i clienti presenti nella hashtable, scorrendo tutte le sue entry e le loro rispettive liste collegate

*/
// Stampa tutti i clienti presenti nella hashtable
void visualizza_clienti(hashtable clienti)
{
    if (clienti == NULL)
    {
        printf("Hashtable non inizializzata.\n");
        return;
    }

    printf("\n--- Elenco Clienti ---\n");
    for (int i = 0; i < clienti->size; i++) // itera fino alla size della tabella
    {
        struct Cliente *curr = clienti->table[i];
        while (curr != NULL)
        {
            printf("ID: %d | Nome: %s | Cognome: %s | Abbonamento: %svalido\n",
                   curr->id, curr->nome, curr->cognome, curr->abbonamento ? "" : "non "); // operatore ternario per stampare valido/non valido a seconda del valore di abbonamento
            curr = curr->next;
        }
    }
    printf("----------------------\n");
}

/*
    ---- funzione get_abbonamento(hashtable clienti, int id_cliente, int size_tabella)
        precondizione: clienti != NULL
        postcondizione: restituisce lo stato dell'abbonamento di un cliente dato il suo id, utilizzando la funzione cerca_cliente
*/

int get_abbonamento(hashtable clienti, int id_cliente, int size_tabella)
{
    Cliente cliente = cerca_cliente(clienti, id_cliente, size_tabella);
    if (cliente == NULL)
        return -1; // Cliente non trovato
    return cliente->abbonamento;
}

/*
    ---- funzione get_size(hashtable clienti)
        precondizioni: clienti != NULL
        postcondizioni: restituisce la dimensione della tabella hash

*/

// Restituisce la dimensione della hashtable
int get_size(hashtable clienti)
{
    return clienti->size;
}

/*
    ---- funzione destroy_hashtable(hashtable clienti)
        precondizione: clienti != NULL
        postcondizione: libera la memoria allocata per tutta la tabella hash, richiamando delete_list per la deallocazione delle liste collegate

*/
void destroy_hashtable(hashtable h)
{
    int i;
    // Ciclo attraverso ogni indice della tabella hash.
    for (i = 0; i < h->size; i++)
    {
        // Elimina la lista collegata in ogni indice della tabella.
        delete_list(h->table[i]);
    }
    // Libera la memoria allocata per l'array di puntatori della tabella.
    free(h->table);
    // Libera la memoria allocata per la struttura della tabella hash.
    free(h);
    return;
}

/*
    ---- funzione delete_list(Cliente cliente)
        precondizione: cliente != NULL
        postcondizione: libera la memoria allocata per la singola entry della tabella, scorrendo ed eliminando i nodi della sua lista collegata
*/

void delete_list(Cliente cliente)
{
    Cliente nextNode;
    while (cliente != NULL)
    {
        nextNode = cliente->next; // Salva il riferimento al nodo successivo.
        free(cliente);            // Libera il nodo corrente.
        cliente = nextNode;       // Passa al nodo successivo.
    }
}
