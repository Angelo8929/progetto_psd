#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "abbonamenti.h"

int main() {
    // === 1. Inizializzazione hashtable per i clienti ===
    hashtable clientiHash = newHashtable(10);
     Cliente c1 =newCliente(1, "Mario", "Rossi", 1);
     Cliente c2 =newCliente(2, "Luigi", "Verdi", 1);
    InsertHash(clientiHash, c1);
    InsertHash(clientiHash, c2);

    // === 2. Inizializzazione lista lezioni ===
    LezioniList lezioni = newLezioniList();
    Lezione l1 = newLezione(100, 3, "Yoga", "Anna");
    Lezione l2 = newLezione(200, 2, "Pilates", "Giulia");

    lezioni = aggiungiLezione(l1, lezioni); // * perché newLezione restituisce un puntatore
    lezioni = aggiungiLezione(l2, lezioni);

    // === 3. Inizializzazione lista prenotazioni ===
    PrenotazioniList prenotazioni = NULL;

    // === 4. Aggiunta prenotazioni ===
    prenotazioni = creaPrenotazione(prenotazioni, 1, 100, "10:00", verificaValiditaAbbonamento(1), 3);
    prenotazioni = creaPrenotazione(prenotazioni, 2, 100, "10:00", verificaValiditaAbbonamento(1), 3);
    prenotazioni = creaPrenotazione(prenotazioni, 1, 200, "11:00", verificaValiditaAbbonamento(1), 2);

    // === 5. Visualizzazione prenotazioni per cliente ===
    visualizzaPrenotazioniCliente(prenotazioni, 1);

    // === 6. Visualizzazione disponibilità lezioni ===
    visualizzaDisponibilitaLezione(lezioni, prenotazioni);

    // === 7. Cleanup ===
    liberaListaPrenotazioni(prenotazioni);
    destroyHashtable(clientiHash);

    // free per lezioni (non richiesto ora, ma buona pratica)
    LiberaLezioni(lezioni);

    return 0;
}
