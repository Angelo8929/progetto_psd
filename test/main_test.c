#include <stdio.h>
#include "../clienti.h"
#include "../lezioni.h"
#include "../prenotazioni.h"
#include "../utils.h"
#include <string.h>
#define M 30

int confronta_file(const char *file1, const char *file2)
{
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2)
        return 0;
    char riga1[M], riga2[M];
    int uguali = 1;
    while (fgets(riga1, M, f1) && fgets(riga2, M, f2))
    {
        if (strcmp(riga1, riga2) != 0)
        {
            uguali = 0;
            break;
        }
    }
    // Controlla se uno dei due file ha ancora righe
    if ((fgets(riga1, M, f1) != NULL) || (fgets(riga2, M, f2) != NULL))
        uguali = 0;
    fclose(f1);
    fclose(f2);
    return uguali;
}

int run_test_case(char *tc_id)
{
    char input_fname[M], output_fname[M], oracle_fname[M];

    // costruiamo i nomi dei file
    sprintf(input_fname, "%s_input.txt", tc_id);
    sprintf(output_fname, "%s_output.txt", tc_id);
    sprintf(oracle_fname, "%s_oracle.txt", tc_id);

    hashtable clienti = new_clienti_hashtable(100);          // Crea una hashtable per i clienti vuota di 100 elementi
    LezioniList lezioni = new_lezioni_list();                // Crea una lista di lezioni vuota
    PrenotazioniList prenotazioni = new_prenotazioni_list(); // Crea una lista di prenotazioni vuota

    lezioni = carica_lezioni_file("../lezioni.txt", lezioni);
    carica_clienti_file("../clienti.txt", clienti);
    prenotazioni = carica_prenotazioni_file(input_fname, prenotazioni, clienti, lezioni);

    visualizza_prenotazioni_file(prenotazioni, output_fname);

    if (confronta_file(oracle_fname, output_fname))
    {
        printf("Test %s SUPERATO\n", tc_id);
        return 1;
    }
    else
    {
        printf("Test %s FALLITO\n", tc_id);
        return 0;
    }
}

int main()
{
    run_test_case("TC1");
    run_test_case("TC2");
    run_test_case("TC3");
    run_test_case("TC4");
}