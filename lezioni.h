typedef struct LezioneNode *LezioniList;
typedef struct Lezione *Lezione;
LezioniList newLezioniList();
int emptyLezioniList(LezioniList);
Lezione newLezione(int id, int capacita_massima, char *nome, char *istruttore);
LezioniList aggiungiLezione(Lezione lezione, LezioniList l);
void visualizzaDisponibilitaLezione(LezioniList head);
void incrementaPostiOccupati(LezioniList head, int id_lezione);