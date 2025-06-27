#include "Effect.h"


EffectManager::EffectManager() {

}
EffectManager::~EffectManager() {

}

//初期化
void EffectManager::Init() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Init();
	}
}
//読みこみ
void EffectManager::Load() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Load(m_EffectData[0]);
	}
}
//通常処理
void EffectManager::Step() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Step();
	}
}
//描画処理
void EffectManager::Draw() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Draw();
	}
}
//終了処理
void EffectManager::Fin() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Fin();
	}
}
//更新処理
void EffectManager::Update() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Update();
	}
}

//呼び出し
void EffectManager::Request(int _Pos_X, int _Pos_Y, int _ID) {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		if (m_cEffect[i].GetID() == _ID) {

			m_cEffect[i].Request(_Pos_X, _Pos_Y);
		}
	}
}




Effect::Effect() {
	m_ID = -1;			// ID
	for (int i = 0; i < EFFECT_MAX_HNDL; i++) {
		m_Hndl[i] = -1;	// 画像ハンドル(一応最大値を16に)
	}
	m_Pos_X = 0.0f;		// 表示位置
	m_Pos_Y = 0.0f;		// 表示位置
	m_CurrentFlame = 0;	// 現在フレーム
	m_IsActive = false;	// 発生中フラグ

	m_MaxFlame = 0;		// 最大フレーム
	m_Size = 0;			// ピクセル数
	m_Num_X = 0;		// 横の分割数
	m_Num_Y = 0;		// 縦の分割数
}
Effect::~Effect() {

}

//初期化
void Effect::Init() {
	m_ID = -1;			// ID
	for (int i = 0; i < EFFECT_MAX_HNDL; i++) {
		m_Hndl[i] = -1;	// 画像ハンドル(一応最大値を16に)
	}
	m_Pos_X = 0.0f;		// 表示位置
	m_Pos_Y = 0.0f;		// 表示位置
	m_CurrentFlame = 0;	// 現在フレーム
	m_IsActive = false;	// 発生中フラグ

	m_MaxFlame = 0;		// 最大フレーム
	m_Size = 0;			// ピクセル数
	m_Num_X = 0;		// 横の分割数
	m_Num_Y = 0;		// 縦の分割数
}
//読みこみ
void Effect::Load(EFFECT_DATA _EffectData) {
	m_ID = _EffectData.E_ID;				// ID
	m_MaxFlame = _EffectData.E_MAX_FLAME;	// 最大フレーム
	m_Size = _EffectData.E_SIZE;			// ピクセル数
	m_Num_X = _EffectData.E_NUM_X;			// 横の分割数
	m_Num_Y = _EffectData.E_NUM_Y;			// 縦の分割数
	LoadDivGraph(_EffectData.E_IMG_PATH, m_MaxFlame, m_Num_X, m_Num_Y, m_Size, m_Size, m_Hndl);// 画像
}
//通常処理
void Effect::Step() {

	if (m_IsActive && m_CurrentFlame < m_MaxFlame) {
		m_CurrentFlame++;
	}
	else if (m_CurrentFlame >= m_MaxFlame) {
		m_IsActive = false;
	}
}
//描画処理
void Effect::Draw() {
	if (m_IsActive) {
		DrawGraph(m_Pos_X, m_Pos_Y, m_Hndl[m_CurrentFlame], true);
	}
}
//終了処理
void Effect::Fin() {
	m_ID = -1;			// ID
	for (int i = 0; i < EFFECT_MAX_HNDL; i++) {
		m_Hndl[i] = { -1 };		// 画像ハンドル(一応最大値を16に)
	}
	m_Pos_X = 0.0f;		// 表示位置
	m_Pos_Y = 0.0f;		// 表示位置
	m_CurrentFlame = 0;	// 現在フレーム
	m_IsActive = false;		// 発生中フラグ

	m_MaxFlame = 0;		// 最大フレーム
	m_Size = 0;			// ピクセル数
	m_Num_X = 0;		// 横の分割数
	m_Num_Y = 0;		// 縦の分割数
}
//更新処理
void Effect::Update() {

}

//呼び出し
void Effect::Request(int _Pos_X, int _Pos_Y) {
	m_Pos_X = _Pos_X;
	m_Pos_Y = _Pos_Y;
	m_CurrentFlame = 0;
	m_IsActive = true;
}