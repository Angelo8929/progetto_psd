

typedef struct LezioneNode *LezioniList; // Tipo astratto per la lista di lezioni
typedef struct Lezione *Lezione;         // Tipo astratto per una lezione

// ===============================
// Funzioni per la gestione delle lezioni
// ===============================

// Crea una nuova lista di lezioni
LezioniList new_lezioni_list();

// Verifica se la lista di lezioni è vuota
int empty_lezioni_list(LezioniList);

// Crea una nuova lezione
Lezione new_lezione(int id, int capacita_massima, char *nome, char *istruttore, char *orario);

// Aggiunge una lezione alla lista
LezioniList aggiungi_lezione(Lezione lezione, LezioniList lezioni);

// Stampa la disponibilità delle lezioni
void visualizza_disponibilita_lezione(LezioniList lezioni);

// Incrementa il numero di posti occupati per una lezione specifica
void incrementa_posti_occupati(LezioniList lezioni, int id_lezione);

// Libera la memoria occupata dalla lista di lezioni
void libera_lezioni(LezioniList lezioni);

// Restituisce la capacità massima di una lezione
int get_capacita(Lezione lezione);

// Cerca una lezione specifica nella lista di lezioni
Lezione cerca_lezione(LezioniList lezioni, int id_lezione);

// Restituisce il numero di posti occupati per una lezione
int get_posti_occupati(Lezione lezione);