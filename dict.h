#define WORDBUFF 30
#define STRBUFF 1000
#define WORDNUM 40

typedef struct dict
{
    int wordNo; // 用語のID
    char word[WORDBUFF]; // 用語
    char info[STRBUFF]; // 用語の説明
} dict;

int read_dict(dict dictionary[WORDNUM]); //辞典ファイルの読み込み
void draw_dict(dict dictionary[WORDNUM]); // 辞典の表示
