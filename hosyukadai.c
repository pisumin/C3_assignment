#include <stdio.h>
#include "game.h"

void title_draw();
void manual_draw();

int num; // 配られる手札の枚数
card playerCard[(int)(EVENUM/2)]; // プレイヤーの手札
card npcCard[(int)(EVENUM/2)]; // コンピュータの手札
int quitGame = 0; // ゲームの終了判定．0:継続，1:終了

dict dictionary[WORDNUM]; // 辞書データ
event eve[EVENUM]; // 出来事を保存

int main()
{
    // 辞書データ，出来事データをテキストファイルより読み込み
    if(read_dict(dictionary)!=0 || read_event(eve)!=0)
    {
        printf("failed to open\n");
    }
    char input[CHARBUFF]; // 入力を保存するための変数

    while(1)
    {
        title_draw(); //タイトル画面の描画
        scanf("%s",input);
        switch(input[0])
        {
            case 'D': // はじめからスタート
                start_game(dictionary, eve, num, playerCard, npcCard);
                continue;
            case 'S': //辞典を開く
                draw_dict(dictionary);
                continue;
            case 'A': // 遊び方表示
                manual_draw();
                continue;
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
    printf("S：用語集を開く\n");
    printf("A：遊び方を見る\n");
    printf("Q：ゲーム終了\n");
    line_draw();
}

void manual_draw()
{
    line_draw();
    printf("～遊び方～\n\n");
    printf("このゲームは、江戸時代・幕末期に活躍した新撰組にまつわる出来事を年代順に並べ替えるゲームです。\n");
    printf("数ある史実上の出来事より、20個をピックアップしました。\n");
    printf("ゲームは、次の手順で進みます。\n\n");
    printf("1:まず難易度を選択します。\n　(初級は6個、中級は10個、上級は20個の出来事を並べ替えます。)\n");
    printf("2:選んだ難易度に応じて、手札がコンピュータとプレイヤーに配られます。\n　手札はコンピュータ→プレイヤー→コンピュータのように、交互に連続するように配られます。\n");
    printf("3:先攻、後攻が表\示されるので、時系列が早いものから交互に出していきます。\n");
    printf("4:手札を出し切ったらゲームクリアとなります。\n\n");
    printf("プレイ中は、出された出来事の説明をその場で見ることができますので、ぜひご活用ください。\n\n");
    printf("(S：タイトルに戻る)\n");
    line_draw();

    char input[CHARBUFF];
    scanf("%s",input);
    while(1)
    {
        if(input[0]=='S')
        {
            break;
        } else {
            printf("入力が正しくありません。\n");
            scanf("%s",input);
        }
    }
}