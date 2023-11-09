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
            switch(c++) // 順にNo.,用語,説明
            {
                case 0:
                    dictionary[r-1].wordNo = atoi(token);
                    break;
                case 1:
                    strcpy(dictionary[r-1].word, token);
                    break;
                case 2:
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

} // 辞典の表示
