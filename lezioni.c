#define MAX_STR 50
#define MAX_POSTI 100
#include "clienti.h"
struct Lezione
{
    char nome[MAX_STR];
    char istruttore[MAX_STR];
    int posti_occupati[MAX_POSTI];
    struct ClienteNode *clienti;
};

struct LezioneNode
{
    struct Lezione lezione;
    struct Lezione *next;
};

struct ClienteNode
{
    int id;
    struct ClienteNode *next;
};