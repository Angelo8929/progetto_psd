#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "abbonamenti.h"
#include "utils.h"

int main()
{
    hashtable clienti = newHashtable(100);
    int clienti_caricati = 0;
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
            if (lezioni == NULL)
            {

                lezioni = carica_lezioni_file("lezioni.txt", lezioni);
            }
            else
            {
                printf("Lezioni gia' caricate\n");
            }
            break;

        case 2:
            if (!clienti_caricati)
            {

                carica_clienti_file("clienti.txt", clienti);
                clienti_caricati = 1;
            }
            else
            {
                printf("Clienti gia' caricati\n");
            }
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

    return 0;
}
