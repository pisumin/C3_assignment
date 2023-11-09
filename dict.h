#define WORDBUFF 30
#define STRBUFF 1000
#define WORDNUM 40
#define CHARBUFF 256

typedef struct dict
{
    int wordNo; // 用語のID
    char word[WORDBUFF]; // 用語
    char info[STRBUFF]; // 用語の説明
} dict;

int read_dict(dict dictionary[WORDNUM]); //辞典ファイルの読み込み
void draw_dict(dict dictionary[WORDNUM]); // 辞典の表示
void print_item(dict dictionary[WORDNUM], int init); // init番から10個項目を列挙
void print_info(dict dictionary[WORDNUM], int number); // 項目の説明を表示
void line_draw();
