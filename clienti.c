#define MAX 100

#include "abbonamenti.h"
#include "clienti.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// ===============================
// Definizione delle strutture dati
// ===============================


// Definizione della struttura Cliente
struct Cliente {
    int id;
    char nome[MAX];
    char cognome[MAX];
    int abbonamento;
    struct Cliente *next;  // Puntatore al prossimo cliente nella lista (per gestione collisioni nella hashtable)
};

// Definizione della struttura hash (hashtable)
struct hash {
    int size;                  // Dimensione della tabella
    struct Cliente **table;    // Array di puntatori a clienti (liste concatenate)
};

// Crea una nuova hashtable con dimensione specificata
hashtable newHashtable(int size) {
    hashtable h = (struct hash *)malloc(sizeof(struct hash));
    h->size = size;
    h->table = (struct Cliente **)calloc(size, sizeof(struct Cliente *)); // Inizializza con NULL
    return h;
}

// Funzione di hash: restituisce l'indice per una chiave (id cliente)
int hashFun(int k, int m) {
    return k % m;
}

// Crea un nuovo cliente e restituisce il puntatore
Cliente newCliente(int id, char nome[], char cognome[], int abbonamento) {
    Cliente nuovo = malloc(sizeof(struct Cliente));
    nuovo->id = id;
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    nuovo->abbonamento = abbonamento;
    nuovo->next = NULL;
    return nuovo;
}

// Aggiunge un cliente alla hashtable
int aggiungiCliente(hashtable h, Cliente cliente) {
    if (cliente == NULL) {
        fprintf(stderr, "Errore: il cliente non è valido.\n");
        return 0;
    }

    int idx = hashFun(cliente->id, h->size);     // Calcola indice tramite funzione hash
    struct Cliente *head = h->table[idx];        // Ottiene la lista corrente nella posizione calcolata
    struct Cliente *curr = head;

    // Controlla se il cliente esiste già
    while (curr) {
        if (curr->id == cliente->id)
            return 0; // Cliente già presente
        curr = curr->next;
    }

    // Inserimento in testa alla lista (gestione collisioni con chaining)
    cliente->next = head;
    h->table[idx] = cliente;
    return 1;
}

// Elimina tutti i nodi di una lista di clienti
void deleteList(struct Cliente *p) {
    struct Cliente *nextNode;
    while (p != NULL) {
        nextNode = p->next;
        free(p);
        p = nextNode;
    }
}

// Libera la memoria allocata per la hashtable e i suoi elementi
void destroyHashtable(hashtable h) {
    for (int i = 0; i < h->size; i++) {
        deleteList(h->table[i]);  // Elimina ciascuna lista nella tabella
    }
    free(h->table);  // Libera l'array di puntatori
    free(h);         // Libera la struttura hash stessa
}

// Restituisce l'ID di un cliente
int getIdCliente(Cliente cliente) {
    return cliente->id;
}

// Cerca un cliente nella hashtable dato il suo id
Cliente cercaCliente(hashtable h, int id_cliente, int size_tabella) {

    if (h == NULL || h->table == NULL) // Se la hashtable non è inizializzata o i clienti non sono stati caricati
        return NULL;                   // Restituisce NULL

    int idx = hashFun(id_cliente, size_tabella);
    struct Cliente *curr = h->table[idx];

    while (curr != NULL) {
        if (curr->id == id_cliente)
            return curr;
        curr = curr->next;
    }
    return NULL;  // Cliente non trovato
}

// Stampa tutti i clienti presenti nella hashtable
void stampaClienti(hashtable h) {
    if (h == NULL) {
        printf("Hashtable non inizializzata.\n");
        return;
    }

    printf("\n--- Elenco Clienti ---\n");
    for (int i = 0; i < h->size; i++) {
        struct Cliente *curr = h->table[i];
        while (curr != NULL) {
            printf("ID: %d | Nome: %s | Cognome: %s | Abbonamento: %d\n",
                   curr->id, curr->nome, curr->cognome, curr->abbonamento);
            curr = curr->next;
        }
    }
    printf("----------------------\n");
}

// Restituisce il numero dell'abbonamento di un cliente dato l'id
int getAbbonamento(hashtable h, int id_cliente, int size_tabella) {
    Cliente cliente = cercaCliente(h, id_cliente, size_tabella);
    if (cliente == NULL)
        return -1; // Cliente non trovato
    return cliente->abbonamento;
}

// Restituisce la dimensione della hashtable
int getSize(hashtable h) {
    return h->size;
}
