

#include "list.h" // Tipo astratto per la lista di lezioni
typedef struct Lezione *Lezione;
typedef list LezioniList; // Tipo astratto per una lezione
#define NULLITEM 0
// ===============================
// Funzioni per la gestione delle lezioni
// ===============================

// Crea una nuova lista di lezioni

// Crea una nuova lezione
Lezione crea_lezione(int id, int capacita_massima, char *nome, char *istruttore, char *orario);

// Aggiunge una lezione alla lista

// Stampa la disponibilità delle lezioni
void visualizza_lezioni(LezioniList lezioni);

// Incrementa il numero di posti occupati per una lezione specifica
void incrementa_posti_occupati(Lezione lezione);

// Libera la memoria occupata dalla lista di lezioni
void libera_lezioni(LezioniList lezioni);

// Restituisce la capacità massima di una lezione
int get_capacita(Lezione lezione);

// Cerca una lezione specifica nella lista di lezioni
// Lezione cerca_lezione(list lezioni, int id_lezione);

// Restituisce il numero di posti occupati per una lezione
int get_posti_occupati(Lezione lezione);
int get_id_lezione(Lezione lezione);

LezioniList go_next(LezioniList nodo);
Lezione get_lezione_from_node(LezioniList nodo);