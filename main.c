#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "abbonamenti.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    hashtable clienti = newHashtable(100);
    LezioniList lezioni = newLezioniList();
    PrenotazioniList prenotazioni = newPrenotazioniList();
    int scelta;
    do
    {
        printf("\n1. Carica lezioni da file");
        printf("\n2. Carica clienti da file");
        printf("\n3. Carica prenotazioni da file");
        printf("\n4. Visualizza prenotazioni effettuate");
        printf("\n5. Visualizza lezioni");
        printf("\n6. Visualizza clienti");
        printf("\n0. Esci dal programma ");
        printf("\n Scelta: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
        case 1:
            lezioni = carica_lezioni_file("lezioni.txt", lezioni);
            break;

        case 2:
            carica_clienti_file("clienti.txt", clienti);
            break;

        case 3:
            prenotazioni = carica_prenotazioni_file("prenotazioni.txt", prenotazioni, clienti, lezioni);
            break;

        case 4:
            visualizzaTutteLePrenotazioni(prenotazioni);
            break;

        case 5:
            visualizzaDisponibilitaLezione(lezioni);
            break;

        case 6:
            stampaClienti(clienti);
            break;

        case 0:
            destroyHashtable(clienti);
            liberaLezioni(lezioni);
            liberaListaPrenotazioni(prenotazioni);

            printf("Uscita...");
            break;

        default:
            printf("Scelta non valida");
        }
    } while (scelta != 0);

    stampaClienti(clienti);

    return 0;
}
