//ウィンドウを表示するプログラム

#include "DxLib.h"	//DXライブラリのインクルード
#include <math.h>

#include "Scene/SceneManager.h"
#include "Input/Input.h"
#include "VirtualButton/VirtualButton.h"

// define
#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定(デフォルト)
#define	SCREEN_SIZE_Y	720	// Y方向の画面サイズを指定(デフォルト)

//円周率 DX_PI_F;

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// 画面サイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く
	
	SceneManager cScene;
	CInput::InitInput();
	CVirtualButton_Square::GetInstance()->Init();
	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//エスケープキーが押されたら終了
			break;
		}

		//画面に表示されたものを初期化
		ClearDrawScreen();

		//-----------------------------------------
		//ここからゲームの本体を書くことになる
		//-----------------------------------------
		
		// 計算処理
		CInput::StepInput();
		CVirtualButton_Square::GetInstance()->Step();
		cScene.Loop();

		// 描画処理
		cScene.Draw();
		CVirtualButton_Square::GetInstance()->Draw();
		//-----------------------------------------
		//ループの終わりに
		//フリップ関数
		ScreenFlip();

	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く
	CVirtualButton_Square::DeleteInstance();
	
	//-----------------------------------------
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

