#pragma once
#include "DxLib.h"

#define EFFECT_MAX_HNDL (16)

#define EFFECT_NAX_NUM (16)

enum Effect_ID {

	EFFECT_ID_DEAD = 0,
	EFFECT_ID_POINT,

	EFFECT_ID_MAX,
};



struct EFFECT_DATA {
	int E_ID;				// ID
	char E_IMG_PATH[128];	// ファイルパス
	int E_MAX_FLAME;		// 最大フレーム
	int E_SIZE;				// ピクセル数
	int E_NUM_X;			// 横の分割数
	int E_NUM_Y;			// 縦の分割数
};



class Effect {

private:
	int m_ID;				// ID
	int m_Hndl[EFFECT_MAX_HNDL];			// 画像ハンドル(一応最大値を16に)
	float m_Pos_X;			// 表示位置
	float m_Pos_Y;			// 表示位置
	int m_CurrentFlame;		// 現在フレーム
	bool m_IsActive;		// 発生中フラグ

	int m_MaxFlame;			// 最大フレーム
	int m_Size;				// ピクセル数
	int m_Num_X;			// 横の分割数
	int m_Num_Y;			// 縦の分割数
public:
	Effect();
	~Effect();

	//初期化
	void Init();
	//読みこみ
	void Load(EFFECT_DATA _EffectData);
	//通常処理
	void Step();
	//描画処理
	void Draw();
	//終了処理
	void Fin();
	//更新処理
	void Update();

	//呼び出し
	void Request(int _Pos_X, int _Pos_Y);

	int GetID() { return m_ID; }
};



class EffectManager {

private:

	Effect m_cEffect[EFFECT_NAX_NUM];

	EFFECT_DATA m_EffectData[EFFECT_ID_MAX] = {
		{EFFECT_ID_DEAD,"data/Effect/Dead.png",4,32,2,2 },
		{EFFECT_ID_POINT,"data/Effect/Dead_2.png",4,32,2,2 },
	};

public:

	EffectManager();
	~EffectManager();

	//初期化
	void Init();
	//読みこみ
	void Load();
	//通常処理
	void Step();
	//描画処理
	void Draw();
	//終了処理
	void Fin();
	//更新処理
	void Update();

	//呼び出し
	void Request(int _Pos_X, int _Pos_Y,int _ID);
};