#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
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


// ゲーム開始
int start_game(dict dictionary[WORDNUM], event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)])
{
    char input[CHARBUFF];
    // 難易度選択
    line_draw();
    printf("～難易度選択～\n\n");
    printf("0：初級(6個)\n1：中級(10個)\n2：上級(20個)\n\n");
    printf("(0,1,2：難易度選択,S：タイトルに戻る)\n");
    line_draw();
    scanf("%s", input);
    int isend = 0;
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
                isend = 1; break;
            default:
                printf("入力が正しくありません。\n");
                scanf("%s", input);
                continue;
        }
        break;
    }
    if(isend) return 0;

    // 手札を配る
    // 先攻、後攻を決める　0:プレイヤー先攻、1:コンピュータ先攻
    // 乱数SEED設定
    srand((int)time(NULL));
    int turn = rand()%2;
    while(1)
    {
        line_draw();
        printf("あなたは");
        if(turn)
        {
            printf("後攻です。\n\n");
        } else {
            printf("先攻です。\n\n");
        }
        printf("(D：次に進む)\n");
        line_draw();
        scanf("%s", input);
        if(input[0]=='D') break;
    }

    // 手札の配布
    int init;
    handout(eve, num, playerCard, npcCard, turn, &init);

    // ゲームの開始
    play_game(dictionary, eve, num, playerCard,npcCard, turn, init);

    line_draw();
    printf("ゲームを終了しました\nタイトルに戻ります\n");
    line_draw();
    return 0;
}

void handout(event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int turn, int *init)
{
    // 枚数によって開始位置を決める必要がある．
    *init = 0;
    // 乱数SEED
    srand((int)time(NULL));
    if(num == 6)
    {
        // 0~14の間でランダム
        int tmp = rand();
        *init = tmp%15;
    } else if(num == 10) {
        // 0~10の間でランダム
        *init = rand()%11;
    }

    int i;
    // 先攻に配られるのは，initから1つ空きでnum/2個
    int tmp = *init;
    for(i=0;i<num/2;i++)
    {
        if(turn)
        {
            npcCard[i].eventNo = eve[tmp].eventNo; //コンピュータ先攻
            strcpy(npcCard[i].event, eve[tmp].event);
            npcCard[i].ishaving = 1;
        } else {
            playerCard[i].eventNo = eve[tmp].eventNo; // プレイヤー先攻
            strcpy(playerCard[i].event, eve[tmp].event);
            playerCard[i].ishaving = 1;
        }
        tmp += 2;
    }
    // 後攻に配られるのは，init+1から1つ空きでnum/2個
    tmp = *init+1;
    for(i=0;i<num/2;i++)
    {
        if(turn)
        {
            playerCard[i].eventNo = eve[tmp].eventNo; //コンピュータ先攻
            strcpy(playerCard[i].event, eve[tmp].event);
            playerCard[i].ishaving = 1;
        } else {
            npcCard[i].eventNo = eve[tmp].eventNo; // プレイヤー先攻
            strcpy(npcCard[i].event, eve[tmp].event);
            npcCard[i].ishaving = 1;
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

int play_game(dict dictionary[WORDNUM], event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)],card npcCard[(int)(EVENUM/2)], int turn, int init)
{
    char input[CHARBUFF];
    int isend = 0; // ゲームの終了を判定
    int cnt = 0; // ターン数を数える
    int npc = 0; // NPCが何枚目のカードを出すか
    int precard = -1; // 1手前に出されたカードのIDを覚えておく
    int currentcard; // 現在出されたカードのID
    while(cnt < num)
    {
        // 手札を表示
        line_draw();
        int i;
        printf("～手札～\n\n");
        for(i=0;i<num/2;i++)
        {
            if(playerCard[i].ishaving)
            {
                printf("%d:%s\n",i,playerCard[i].event);
            }
        }
        // turnが0ならプレイヤーのターン，turnが1ならコンピュータのターン
        if(turn) // コンピュータのターン
        {
            printf("「%s」が出されました。\n\n",npcCard[npc].event);
            currentcard = npcCard[npc].eventNo;
            dictionary[eve[currentcard].dictNum].open = 1;
            printf("(W：説明を見る,D：次に進む,S：タイトルに戻る)\n");
            line_draw();
            scanf("%s", input);
            while(1)
            {
                switch(input[0])
                {
                    case 'W':
                        print_info(dictionary, eve[currentcard].dictNum);
                        printf("(W：説明を見る,D：次に進む,S：タイトルに戻る)\n");
                        line_draw();
                        scanf("%s", input);
                        continue;
                    case 'D':
                        turn = 0;
                        precard = npcCard[npc++].eventNo;
                        cnt++;
                        break;
                    case 'S':
                        isend = 1;
                        break;
                    default:
                        printf("もう一度入力してください。\n");
                        break;
                }
                break;
            }
        } else  {// プレイヤーのターン
            printf("手札を選んでください。\n");
            scanf("%s", input);
            while(1)
            {
                if(!(input[0]>='0'&& input[0]<(num/2)+'0')||(!playerCard[input[0]-'0'].ishaving)) // 数字以外の入力
                {
                    printf("もう一度入力してください。\n");
                    scanf("%s", input);
                    continue;
                }
                break;
            }

            printf("「%s」が出されました。\n\n",playerCard[input[0]-'0'].event);
            playerCard[input[0]-'0'].ishaving = 0;
            currentcard = playerCard[input[0]-'0'].eventNo;
            dictionary[eve[currentcard].dictNum].open = 1;

            if(precard == -1)
            {
                if(currentcard == init) printf("正解です。\n\n");
                else {
                    printf("不正解です。\n\n");
                    break;
                }
            } else if(currentcard == precard+1) { // 次のカードを出せた
                printf("正解です。\n\n");
            } else {
                printf("不正解です。\n\n");
                break;
            }

            printf("(W：説明を見る,D：次に進む,S：タイトルに戻る)\n");
            line_draw();
            scanf("%s", input);
            while(1)
            {
                switch(input[0])
                {
                    case 'W':
                        print_info(dictionary, eve[currentcard].dictNum);
                        printf("(W：説明を見る,D：次に進む,S：タイトルに戻る)\n");
                        line_draw();
                        scanf("%s", input);
                        continue;
                    case 'D':
                        turn = 1;
                        precard = currentcard;
                        cnt++;
                        break;
                    case 'S':
                        isend = 1;
                        break;
                    default:
                        printf("もう一度入力してください。\n");
                        break;
                }
                break;
            }
        }
        if(isend)
        {
            printf("タイトルに戻ります\n");
            break;
        }
    }
    return 0;
}