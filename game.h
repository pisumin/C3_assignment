#define WORDBUFF 30
#define EVENUM 20
#include "dict.h"

typedef struct event
{
    int eventNo; // 出来事のID
    char event[WORDBUFF]; // 出来事名
    int dictNum; // 関連する辞書のID
} event;

typedef struct card
{
    int eventNo; // 出来事のID
    char event[WORDBUFF]; // 出来事名
    int ishaving; // 手元にあるカードか
} card;

int read_event(event eve[EVENUM]); //出来事ファイルの読み込み
int start_game(dict dictionary[WORDNUM], event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)]); // ゲームの開始
void handout(event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int turn, int *init); // カードの配布
int play_game(dict dictionary[WORDNUM], event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int turn, int init); // ゲームプレイを実装