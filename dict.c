#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dict.h"
#define DICTFILE "word.txt"

//辞典ファイルを読み込み，配列に格納
int read_dict(dict dictionary[WORDNUM])
{
    // ファイルを開く
    FILE *fp = fopen(DICTFILE, "r");
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
            switch(c++) // 順にNo.,開放状況,用語,説明
            {
                case 0:
                    dictionary[r-1].wordNo = atoi(token);
                    break;
                case 1:
                    dictionary[r-1].open = atoi(token);
                    break;
                case 2:
                    strcpy(dictionary[r-1].word, token);
                    break;
                case 3:
                    strcpy(dictionary[r-1].info, token);
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

void draw_dict(dict dictionary[WORDNUM])
{
    int initnum = 0; // 各ページの先頭の用語の番号
    int returnTitle = 0; // 0:用語集を見る，1:タイトルへ戻る
    char input[CHARBUFF];
    while(1)
    {
        // 五十音順に10個ずつ項目を表示
        print_item(dictionary, initnum);
        // 入力受付
        scanf("%s",input);
        switch(input[0])
        {
            case 'A': // 前ページへ移動
                if(initnum==0)  initnum = 30;
                else initnum -= 10;
                break;
            case 'S': // タイトルへ戻る
                returnTitle = 1;
                break;
            case 'D': // 次ページへ移動
                if(initnum==30) initnum = 0;
                else initnum += 10;
                break;
            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7':
            case '8': case '9':
                if(dictionary[input[0]-'0'+initnum].open)
                {
                    print_info(dictionary, input[0]-'0'+initnum);
                    break;
                }
            default:
                printf("入力が正しくありません．\n");
                break;
        }
        if(returnTitle) break;
    }
}

// init番から10個項目を列挙
void print_item(dict dictionary[WORDNUM], int init)
{
    line_draw();
    printf("～辞典～\n");
    printf("　(？？？はゲームをプレイすることで開放されます．)\n\n");
    int i;
    for(i=0;i<10;i++)
    {
        if(dictionary[init+i].open)
        {
            printf("%d：%s\n", i, dictionary[init+i].word);
        } else {
            printf("%d：？？？？？？\n",i);
        }
    }
    printf("\n(A：前ページへ　D：次ページへ　0～9：項目選択　S：タイトル画面へ)\n");
    line_draw();
}

// 項目の説明を表示
void print_info(dict dictionary[WORDNUM], int number)
{
    char input[CHARBUFF];
    char str[STRBUFF];
    while(1)
    {
        line_draw();
        printf("～%s～\n\n", dictionary[number].word);
        strcpy(str, dictionary[number].info);

        char delim[] = " ";
        char *token;
        token = strtok(str, delim);
        while(token != NULL)
        {
            printf("　%s\n", token);
            token = strtok(NULL, delim);
        }

        printf("(S：戻る)\n");
        line_draw();
        scanf("%s", input);
        if(input[0]=='S') break;
        else printf("もう一度入力してください\n");
    }
}

void line_draw()
{
    printf("\n----------------------------------------------------------------------------------------------\n");
}
