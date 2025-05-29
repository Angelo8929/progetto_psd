#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clienti.h"
#include "lezioni.h"
#include "prenotazioni.h"
#include "utils.h"
#include "list.h"

int main()
{
    hashtable clienti = new_hashtable(TABLE_SIZE); // Crea una hashtable per i clienti vuota di 100 elementi
    lezioni_list lezioni = new_list();             // Crea una lista di lezioni vuota
    prenotazioni_list prenotazioni = new_list();   // Crea una lista di prenotazioni vuota
    int clienti_caricati = 0;

    int scelta; // Variabile per la scelta dell'utente

    // Menù Principale per l'utente
    do
    {
        printf("=================MENU====================\n");
        printf("\n1. Carica lezioni da file");
        printf("\n2. Carica clienti da file");
        printf("\n3. Carica prenotazioni da file (racchiude tutti i test case)");
        printf("\n4. Visualizza prenotazioni effettuate");
        printf("\n5. Visualizza lezioni");
        printf("\n6. Visualizza clienti");
        printf("\n0. Esci dal programma ");
        printf("\n======================================");
        printf("\n Scelta: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
        case 1:
            if (lezioni == NULL)
            {

                lezioni = carica_lezioni_file("lezioni.txt", lezioni);

                printf("----------------------------------\n");
                printf("Lezioni caricate con successo\n");
                printf("----------------------------------\n");
                printf("\n");
            }
            else
            {
                printf("Lezioni gia' caricate\n");
                printf("\n");
            }
            break;

        case 2:
            if (!clienti_caricati)
            {

                carica_clienti_file("clienti.txt", clienti);
                clienti_caricati = 1;
                printf("----------------------------------\n");
                printf("Clienti caricati con successo\n");
                printf("----------------------------------\n");
                printf("\n");
            }
            else
            {
                printf("----------------------------------\n");
                printf("Clienti gia' caricati\n");
                printf("----------------------------------\n");
                printf("\n");
            }
            break;

        case 3:
            if (prenotazioni == NULL)
            {

                prenotazioni = carica_prenotazioni_file("prenotazioni.txt", prenotazioni, clienti, lezioni);
                printf("----------------------------------\n");
            }
            else
            {
                printf("----------------------------------\n");
                printf("Prenotazioni gia' caricate\n");
                printf("----------------------------------\n");
                printf("\n");
            }
            break;

        case 4:
            visualizza_prenotazioni(prenotazioni);
            break;

        case 5:
            visualizza_lezioni(lezioni);
            break;

        case 6:
            visualizza_clienti(clienti);
            break;

        case 0:
            destroy_hashtable(clienti);
            libera_lista(lezioni);
            libera_lista(prenotazioni);

            printf("Uscita...");
            break;

        default:
            printf("Scelta non valida\n");
            printf("\n");
        }
    } while (scelta != 0);

    return 0;
}
