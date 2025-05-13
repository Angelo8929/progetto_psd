main: main.o abbonamenti.o lezioni.o clienti.o prenotazioni.o
	gcc main.o abbonamenti.o lezioni.o clienti.o prenotazioni.o -Wall -W -o main

abbonamenti.o: abbonamenti.c
	gcc -c -Wall -Wextra -pedantic abbonamenti.c

lezioni.o: lezioni.c clienti.h prenotazioni.h
	gcc -c -Wall -Wextra -pedantic lezioni.c

clienti.o: clienti.c abbonamenti.h
	gcc -c -Wall -Wextra -pedantic clienti.c

prenotazioni.o: prenotazioni.c clienti.h lezioni.h
	gcc -c -Wall -Wextra -pedantic prenotazioni.c

main.o: main.c abbonamenti.h lezioni.h clienti.h prenotazioni.h
	gcc -c -Wall -Wextra -pedantic main.c

clean:
	rm *.o
	rm *.exe