#define WORDBUFF 30
#define EVENUM 20

typedef struct event
{
    int eventNo; // 出来事のID
    char event[WORDBUFF]; // 出来事の名前
    int dictNum; // 辞典の番号
} event;

int read_event(event eve[EVENUM]); //出来事ファイルの読み込み
void start_game(); // ゲーム開始
void cont_game(); // 中断データからゲームを開始
