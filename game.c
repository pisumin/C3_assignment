#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "dict.h"
#define EVENTFILE "event.txt"

//出来事ファイルの読み込み
int read_event(event eve[EVENUM])
{
    // ファイルを開く
    FILE *fp = fopen(EVENTFILE, "r");
    if(fp == NULL)
    {
        return -1;
    }

    char str[STRBUFF];
    char delim[] = ",";
    char *token;
    int r = 0, c; // r:行数をカウント，c:列数をカウント
    // ファイルを一行ずつ読み込む
    while(fgets(str, sizeof(str), fp) != NULL)
    {
        if(r==0)
        {
            r++;
            continue; // 1行目を読み飛ばす
        }
        c=0;

        // ,で分離
        token = strtok(str, delim);
        while(token != NULL)
        {
            switch(c++) // 順にNo.,出来事名，辞書No
            {
            case 0:
                eve[r-1].eventNo = atoi(token);
                break;
            case 1:
                strcpy(eve[r-1].event, token);
                break;
            case 2:
                eve[r-1].dictNum = atoi(token);
                break;
            default:
                break;
            }
            token = strtok(NULL, delim);
        }
        r++;
    }
    return 0;
}

/*
ゲーム開始
int num; // 配られる手札の枚数(NPCとプレイヤーの合計．初級6枚，中級10枚，上級20枚)
int playerCard[(int)(EVENUM/2)]; // プレイヤーの手札
int npcCard[(int)(EVENUM/2)]; // コンピュータの手札
int contFlag; // 中断データがあるかどうか．0:中断データがない，1:中断データがある
*/
int start_game(event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int contFlag)
{
    char input[CHARBUFF];
    // 難易度選択
    line_draw();
    printf("～難易度選択～\n\n");
    printf("0：初級(6個)\n1：中級(10個)\n2：上級(20個)\n\n");
    printf("(0,1,2：難易度選択,S：タイトルに戻る)\n");
    line_draw();
    scanf("%s", input);
    while(1)
    {
        switch(input[0])
        {
            case '0':
                num = 6; break;
            case '1':
                num = 10; break;
            case '2':
                num = 20; break;
            case 'S':
                return 0;
            default:
                printf("入力が正しくありません。\n");
                scanf("%s", input);
                continue;
        }
        break;
    }

    // 手札を配る
    // 先攻、後攻を決める　0:プレイヤー先攻、1:コンピュータ先攻
    int turn = rand()%2;
    printf("先攻：%d\n",turn);
    handout(eve, num, playerCard, npcCard, turn);
    int i;
    printf("プレイヤー：\n");
    for(i=0;i<num/2;i++)
    {
        printf("%d:%s\n",playerCard[i].eventNo,playerCard[i].event);
    }
    printf("コンピュータ：\n");
    for(i=0;i<num/2;i++)
    {
        printf("%d:%s\n",npcCard[i].eventNo,npcCard[i].event);
    }

    return 0;
}

// 中断データからゲームを開始
void cont_game()
{

}

void handout(event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int turn)
{
    // 枚数によって開始位置を決める必要がある．
    int init = 0;
    if(num == 6)
    {
        // 0~14の間でランダム
        init = rand()%15;
    } else if(num == 10) {
        // 0~10の間でランダム
        init = rand()%11;
    }
    printf("開始位置：%d\n",init);

    int i;
    // 先攻に配られるのは，initから1つ空きでnum/2個
    int tmp = init;
    for(i=0;i<num/2;i++)
    {
        if(turn)
        {
            npcCard[i].eventNo = eve[tmp].eventNo; //コンピュータ先攻
            strcpy(npcCard[i].event, eve[tmp].event);
        } else {
            playerCard[i].eventNo = eve[tmp].eventNo; // プレイヤー先攻
            strcpy(playerCard[i].event, eve[tmp].event);
        }
        tmp += 2;
    }
    // 後攻に配られるのは，init+1から1つ空きでnum/2個
    tmp = init+1;
    for(i=0;i<num/2;i++)
    {
        if(turn)
        {
            playerCard[i].eventNo = eve[tmp].eventNo; //コンピュータ先攻
            strcpy(playerCard[i].event, eve[tmp].event);
        } else {
            npcCard[i].eventNo = eve[tmp].eventNo; // プレイヤー先攻
            strcpy(npcCard[i].event, eve[tmp].event);
        }
        tmp += 2;
    }

    // プレイヤーの手札の順番をシャッフル
    for (i = num/2-1; i > 0; i--)
    {
        //ランダムなインデックスを生成
        int j = rand() % (i + 1);

        //ランダムに入れ替える
        tmp = playerCard[i].eventNo;
        playerCard[i].eventNo = playerCard[j].eventNo;
        playerCard[j].eventNo = tmp;

        char tmps[WORDBUFF];
        strcpy(tmps, playerCard[i].event);
        strcpy(playerCard[i].event, playerCard[j].event);
        strcpy(playerCard[j].event, tmps);
    }
}
