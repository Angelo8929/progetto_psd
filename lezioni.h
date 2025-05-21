


typedef struct LezioneNode *LezioniList; // Tipo astratto per la lista di lezioni
typedef struct Lezione *Lezione; // Tipo astratto per una lezione


// ===============================
// Funzioni per la gestione delle lezioni
// ===============================

// Crea una nuova lista di lezioni
    LezioniList newLezioniList();

// Verifica se la lista di lezioni è vuota
    int emptyLezioniList(LezioniList);

// Crea una nuova lezione
    Lezione newLezione(int id, int capacita_massima, char *nome, char *istruttore, char *orario);

// Aggiunge una lezione alla lista
    LezioniList aggiungiLezione(Lezione lezione, LezioniList l);

// Stampa la disponibilità delle lezioni
    void visualizzaDisponibilitaLezione(LezioniList head);

// Incrementa il numero di posti occupati per una lezione specifica
    void incrementaPostiOccupati(LezioniList head, int id_lezione);

// Libera la memoria occupata dalla lista di lezioni
    void liberaLezioni(LezioniList lezioni);

// Restituisce la capacità massima di una lezione
    int getCapacita(Lezione lezione);

// Cerca una lezione specifica nella lista di lezioni    
    Lezione cercaLezione(LezioniList lezioni, int id_lezione);

// Restituisce il numero di posti occupati per una lezione
    int getPostiOccupati(Lezione lezione);