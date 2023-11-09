#include <stdio.h>
#include "dict.h"
#include "game.h"

// できればechoオフにしたいね

void title_draw();
void manual_draw();

// 中断状況を保存するための外部変数
int num; // 配られる手札の枚数
int playerCard[(int)(EVENUM/2)]; // プレイヤーの手札
int npcCard[(int)(EVENUM/2)]; // コンピュータの手札
int contFlag; // 中断データがあるかどうか．0:中断データがない，1:中断データがある

dict dictionary[WORDNUM] = {}; // 辞書データ
event eve[EVENUM] = {}; // 出来事を保存

int main()
{
    // 辞書データ，出来事データをテキストファイルより読み込み
    if(read_dict(dictionary)!=0)
    {
        printf("failed to open\n");
    }
//    read_event(eve);
    char input; // 入力を保存するための変数

/*    int i;
    for(i=0;i<WORDNUM;i++)
    {
        printf("%d:%s\n%s\n\n",dictionary[i].wordNo,dictionary[i].word,dictionary[i].info);
    }
*/
    while(1)
    {
        title_draw(); //タイトル画面の描画
        scanf("%c",input);
        switch(input)
        {
            case 'D': // はじめからスタート
                start_game();
                continue;
            case 'W': // 続きからスタート
                if(contFlag) // 中断データがあればそこからスタート
                {
                    cont_game();
                } else {
                    printf("もう一度入力してください\n");
                }
                continue;
            case 'S': //辞典を開く
                draw_dict(dictionary);
                continue;
            case 'A': // 遊び方表示
                manual_draw();
                continue;
            case 'Q': // ゲーム終了
                break;
        }
    }
    printf("梅の花　一輪咲いても　梅は梅\n");
}

void title_draw()
{

}

void manual_draw()
{

}
