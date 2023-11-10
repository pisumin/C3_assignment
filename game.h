#define WORDBUFF 30
#define EVENUM 20

typedef struct event
{
    int eventNo; // 出来事のID
    char event[WORDBUFF]; // 出来事の名前
    int dictNum; // 辞典の番号
} event;

typedef struct card
{
    int eventNo;
    char event[WORDBUFF];
} card;

int read_event(event eve[EVENUM]); //出来事ファイルの読み込み
int start_game(event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int contFlag); // ゲーム開始
void cont_game(); // 中断データからゲームを開始
void handout(event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int turn); // 手札を配る
