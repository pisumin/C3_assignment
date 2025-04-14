## 概要
江戸時代・幕末に活躍した「新選組」について，
コンピュータと交互に手を出しながら，
最大20個の出来事を時系列で並べ替えるゲームのCプログラム．

大学3年の秋に，講義の課題のために作成したもの．

## 使い方
.exeファイルを実行することで，ターミナル上で動作する．

## 仕様
- **タイトル画面**
    1. タイトル画面を表示して，入力を受け付ける．

        D : ゲームをはじめからスタート
       
        S : 用語集を開く
       
        A : 遊び方を見る
       
        Q : ゲーム終了

- **遊び方の表示**
    1. 一定時間ごとにゲームプレイの手順を表示
    2. 入力を受け付ける
        S : タイトル画面に戻る

- **用語集**
    1. 事前に用意した用語名を10個ずつ表示．
       
        開放済みの用語は用語名で，未開放の用語は”？？？？？？”と表示．
    2. 入力を受け付ける
       
        A : 前の10項目を表示
       
        D : 次の10項目を表示
       
        0 ~ 9 : 開放済みの用語の場合は用語の説明を表示．
        未開放の場合はもう一度入力を促す
       
        S : タイトル画面へ戻る．
    3. 一定時間ごとに用語の説明を表示して，入力を受け付ける

        S : 項目のリストへ戻る

- **はじめからゲームをスタート**
    1. 難易度選択画面を表示し，入力を受け付ける
  
        0 : 初級 (6個の出来事を並べ替える．) を選択
       
        1 : 中級 (10個の出来事を並べ替える．) を選択
       
        2 : 上級 (20個の出来事を並べ替える．) を選択
       
        S : タイトル画面へ戻る
    2. 乱数によって先攻・後攻をきめ，プレイヤーがどちらかを表示する．
    3. ゲーム終了まで以下を繰り返す
       
        a. コンピュータのターンの場合
       
            1. コンピュータの出した手を表示し，入力を受け付ける
       
                W : 出された用語の説明を表示 (表示後はSを入力で戻る)
                D : 次のターンに進む
                S : タイトル画面へ戻る


        b. プレイヤーのターンの場合
       
            1. プレイヤーの手札を表示し，出す手の入力を促す
       
                数字 : 出す手を選ぶ
            2. 選択した出来事を表示して，正解か不正解かを表示する．正解の場合は入力を促し，不正解の場合はタイトル画面へ戻る．
       
                W : 出した用語の説明を表示 (表示後はSで戻る)
       
                D : 次のターンに進む
       
                S : タイトル画面へ戻る

## 各ファイルについて
- **hosyukadai.exe**
  
    実行ファイル．
    このファイルを実行することで，ゲームをプレイする．

- **hosyukadai.c**
  
    main関数を含むファイル．
    画面の遷移やゲームプレイの状況など，全体の制御を行う．

    - **dict.h**
      
        dict,cに対応するヘッダファイル．
        用語集の各用語に対応する構造体 dict を定義．

    - **dict,c**
      
        用語集に関する関数を定義．
        * int read_dict(dict dictionary[WORDNUM])
          
          用語の一覧を記述したファイル (word.txt) の読み込み．読み込みに成功すると0を返す．
        * void draw_dict(dict dictionary[WORDNUM])
          
          用語集を表示する
        * print_item(dict dictionary[WORDNUM], int init)
          
          init番から10項目を表示する関数
        * ptiny_info(dict dictionary[WORDNUM], int number)
          
          number番目の項目の説明を表示する関数．
        * void line_draw()
          
          描画時に使用．横線を表示．

    - **game.h**
      
        game.cに対応するヘッダファイル．
        並べ替える対象となる出来事の構造体 event，プレイヤーの手札の構造体 cardを定義．

    - **game.c**
      
        ゲームを実装．以下の関数を含む．
        * int read_event(event eve[EVENUM])
          
          出来事の一覧を記述したファイル (event.txt) の読み込み．読み込みに成功すると0を返す．
        * int start_game(dict dictionary[WORDNUM], event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)], card npcCard[(int)(EVENUM/2)])
          
          ゲーム開始までの処理を実装．ゲーム終了により0を返す．
        * void handout(event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)], card npcCard[(int)(EVENUM/2)], int turn, int *init)
          
          プレイヤー，NPCに手札を配布する
        * int play_game(dict dictionary[WORDNUM], event eve[EVENUM], int num, card playerCard[(int)(EVENUM/2)], card npcCard[(int)(EVENUM/2)], int turn, int init)
          
          ゲームプレイの流れを実装

    - **event.txt**
      
        ゲームプレイ時に使用する出来事の一覧を記述したテキストデータ．

    - **word.txt**
      
        用語の一覧を記述したテキストデータ．
