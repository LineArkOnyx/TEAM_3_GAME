#pragma once
#include "DxLib.h"

#define KEY_BUF_LEN		(256)
#define MOUSE_BUF_LEN	(5)


static class CInput {
private:
	//現在のフレームのキー情報
	static char currentKeyBuf[KEY_BUF_LEN];
	//前フレームのキー情報
	static char preKeyBuf[KEY_BUF_LEN];

	//現在のフレームのマウス情報
	static int currentMouseBuf[MOUSE_BUF_LEN];
	//前フレームのマウス情報
	static int preMouseBuf[MOUSE_BUF_LEN];

	static int JoypadNum;
public:
	//何を入力されたか
	static const int MOUSE_LEFT = 0;
	static const int MOUSE_RIGHT = 1;
	static const int MOUSE_MIDLE = 2;

	//入力制御初期化
	static void InitInput();

	//入力制御ステップ
	//ほかのStepより早く呼ぶ
	static void StepInput();


	//キーボード関連
	//今押された
	static bool IsKeyPush(int key_code);
	//押し続ける
	static bool IsKeyKeep(int key_code);
	//離したとき
	static bool IsKeyRelease(int key_code);

	static bool IsKeyDown(int key_code);

	//マウス関連
	//今押された
	static bool IsMousePush(int Mouse_code);
	//押し続ける
	static bool IsMouseKeep(int Mouse_code);
	//離したとき
	static bool IsMouseRelease(int Mouse_code);

	//マウスの状態を得る
	static void GetHitMouseStateAll();
};


