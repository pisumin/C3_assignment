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
int quitGame = 0; // ゲームの終了判定．0:継続，1:終了

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
    char input[CHARBUFF]; // 入力を保存するための変数

/*    int i;
    for(i=0;i<WORDNUM;i++)
    {
        printf("%d:%s\n%s\n\n",dictionary[i].wordNo,dictionary[i].word,dictionary[i].info);
    }
*/
    while(1)
    {
        title_draw(); //タイトル画面の描画
        scanf("%s",input);
        switch(input[0])
        {
            case 'D': // はじめからスタート
                start_game();
                break;
            case 'W': // 続きからスタート
                if(contFlag) // 中断データがあればそこからスタート
                {
                    cont_game();
                } else {
                    printf("もう一度入力してください\n");
                    scanf("%s",input);
                    continue;
                }
                break;
            case 'S': //辞典を開く
                draw_dict(dictionary);
                break;
            case 'A': // 遊び方表示
                manual_draw();
                break;
            case 'Q': // ゲーム終了
                quitGame = 1;
                break;
            default:
                printf("もう一度入力してください\n");
                scanf("%s",input);
                continue;
        }
        if(quitGame) break;
    }
    printf("ゲームを終了します．\n");
    return 0;
}

// タイトル画面
void title_draw()
{
    line_draw();
    printf("～新撰組の軌跡～\n\n");
    printf("D：はじめからスタート\n");
    if(contFlag) printf("W：続きからスタート\n");
    printf("S：用語集を開く\n");
    printf("A：遊び方を見る\n");
    printf("Q：ゲーム終了\n");
    line_draw();
}

void manual_draw()
{

}
