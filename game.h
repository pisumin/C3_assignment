#define WORDBUFF 30
#define EVENUM 20
#include "dict.h"

typedef struct event
{
    int eventNo; // ?øΩo?øΩ?øΩ?øΩ?øΩ?øΩ?øΩID
    char event[WORDBUFF]; // ?øΩo?øΩ?øΩ?øΩ?øΩ?øΩÃñÔøΩ?øΩO
    int dictNum; // ?øΩ?øΩ?øΩT?øΩÃî‘çÔøΩ
} event;

typedef struct card
{
    int eventNo;
    char event[WORDBUFF];
    int ishaving;
} card;

int read_event(event eve[EVENUM]); //?øΩo?øΩ?øΩ?øΩ?øΩ?øΩt?øΩ@?øΩC?øΩ?øΩ?øΩÃì«Ç›çÔøΩ?øΩ?øΩ
int start_game(dict dictionary[WORDNUM], event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int *contFlag); // ?øΩQ?øΩ[?øΩ?øΩ?øΩJ?øΩn
void cont_game(); // ?øΩ?øΩ?øΩf?øΩf?øΩ[?øΩ^?øΩ?øΩ?øΩ?øΩ?øΩQ?øΩ[?øΩ?øΩ?øΩ?øΩ?øΩJ?øΩn
void handout(event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int turn, int *init); // ?øΩ?øΩ?øΩD?øΩ?øΩ?øΩz?øΩ?øΩ
void play_game(dict dictionary[WORDNUM], event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int *contFlag, int turn, int init);
