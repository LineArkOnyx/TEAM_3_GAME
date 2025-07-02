#pragma once
#include "DxLib.h"

class Move {
public:
    static void Init();           // 初期化（画像ロード・位置設定）
    static void Update();         // 状態更新（アニメーション進行）
    static void Draw();           // 描画（画像の表示）
    static bool IsFinished();     // 終了確認（演出が終わったか）

private:
    enum class State {
        Entering,    // 中央へ移動中
        Holding,     // 中央で停止
        Reversing,   // 元の方向に戻る（Uターン）
        Finished     // 終了
    };

    static int imageTop;
    static int imageBottom;
    static int yTop;
    static int yBottom;
    static int holdCounter;
    static State currentState;
};
