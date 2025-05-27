main: main.o abbonamenti.o lezioni.o clienti.o prenotazioni.o utils.o list.o
	gcc main.o abbonamenti.o lezioni.o clienti.o prenotazioni.o utils.o list.o -Wall -W -o main

main_test: test/main_test.o abbonamenti.o lezioni.o clienti.o prenotazioni.o utils.o list.o
	gcc test/main_test.o abbonamenti.o lezioni.o clienti.o prenotazioni.o utils.o list.o -Wall -W -o test/main_test

list.o: list.c lezioni.h
	gcc -c list.c

abbonamenti.o: abbonamenti.c
	gcc -c -Wall -Wextra -pedantic abbonamenti.c

lezioni.o: lezioni.c clienti.h prenotazioni.h
	gcc -c -Wall -Wextra -pedantic lezioni.c

clienti.o: clienti.c abbonamenti.h
	gcc -c -Wall -Wextra -pedantic clienti.c

prenotazioni.o: prenotazioni.c clienti.h lezioni.h
	gcc -c -Wall -Wextra -pedantic prenotazioni.c

utils.o: utils.c clienti.h lezioni.h prenotazioni.h abbonamenti.h
	gcc -c -Wall -Wextra -pedantic utils.c

test/main_test.o: test/main_test.c abbonamenti.h lezioni.h clienti.h prenotazioni.h utils.h
	gcc -c -Wall -Wextra -pedantic test/main_test.c -o test/main_test.o

main.o: main.c abbonamenti.h lezioni.h clienti.h prenotazioni.h utils.h
	gcc -c -Wall -Wextra -pedantic main.c


clean:
	rm *.o
	rm *.exe

clean_test:
	rm test/*.o
	rm test/*.exe