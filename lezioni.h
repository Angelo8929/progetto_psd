typedef struct LezioneNode *LezioniList;

LezioniList newLezioniList();
int emptyLezioniList(LezioniList);
LezioniList aggiungiLezione(struct Lezione, LezioniList);
void visualizzaDisponibilitaLezione(LezioniList head);