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
    if (argc != 2)
    {
        printf("Uso: %s <clienti.txt>\n", argv[0]);
        return 1;
    }

    hashtable clienti = newHashtable(100);
    caricaClienti(clienti, argv[1]);

    stampaClienti(clienti);

    return 0;
}
