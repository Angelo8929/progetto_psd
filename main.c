#include <stdio.h>
#include "lezioni.h"
#include "prenotazioni.h"
#include "clienti.h"
#include "abbonamenti.h"

int main()
{
    LezioniList l = newLezioniList();
    hashtable h = newHashtable(100);
    Lezione lezione = newLezione(1, 100, "yoga", "mario");
    l = aggiungiLezione(lezione, l);
    Cliente cliente;
    cliente = newCliente(1, "giovanni", "verolla", 1);
    printf("%d", InsertHash(h, cliente));
    visualizzaDisponibilitaLezione(l);
}