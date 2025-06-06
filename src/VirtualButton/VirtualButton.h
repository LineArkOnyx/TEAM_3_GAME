#pragma once

#include <math.h>
#include <vector>
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Input/Input.h"

using namespace std;

class CVirtualButton_Square {
private:

	static CVirtualButton_Square* m_Instance;//インスタンス

	struct ButtonData {

		bool m_CurrentStance;		//前フレームの押されているかいないか
		bool m_NextStance;			//次フレームの押されているかいないか

		float m_fPos_X;		
		float m_fPos_Y;
		float m_fSize_W;	
		float m_fSize_H;

		int m_ButtonColor_R;		//ボタンの赤さ
		int m_ButtonColor_G;		//ボタンの緑さ
		int m_ButtonColor_B;		//ボタンの青さ

		int ActiveID;			//ID
	};
	
	vector<ButtonData> vList_ButtonData;//ボタンのリスト

public:
	//インスタンス取得
	static CVirtualButton_Square* GetInstance();
	//インスタンス破棄
	static void DeleteInstance();

	void Init();//初期化用
	void Step();//更新などを行う
	void Exit();//念のための破棄用
	void Draw();//ボタン描画

	int RequestVirtualButton(float Pos_X, float Pos_Y, float Size_W, float Size_H, int _R,int _G,int _B);//ボタンのリクエスト

	//今押された
	bool IsKeyPush(int _ID);
	//押し続ける
	bool IsKeyKeep(int _ID);
	//離したとき
	bool IsKeyRelease(int _ID);
	//単純に押されてるか否か
	bool IsKeyDown(int _ID);
};