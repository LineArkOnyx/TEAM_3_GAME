#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/Collision.h"
#include "../../Collision/Manager/CollisionManager.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"
#include "../../Font/Font.h"
#include "../../Effect/Effect.h"
#include "../../Sound/SoundManager.h"

// ★ トランジション演出を使うために追加
#include "Move.h"

class TitleScene
{
private:
	enum SEQUENCE_ID
	{
		INIT_SEQUENCE,
		LOAD_SEQUENCE,
		STEP_SEQUENCE,
		EXIT_SEQUENCE,

		SEQUENCE_NUM,
	};

	SEQUENCE_ID SequenceID = INIT_SEQUENCE;

	void Init();
	void Load();
	int Step();
	void Exit();

	// マウスカーソル座標
	int MousePosX;
	int MousePosY;

	// スタートボタン
	float m_fStartPosX;
	float m_fStartPosY;
	int m_iStartHndl;
	bool buttonReach;

	// タイトル画像
	int TitleHndl;
	double Exlate;

	// ★ トランジション演出が終わったかどうか
	bool isTransitionFinished;

	// タイトル文字位置・判定用
	float m_titleX = 640 - 150;       // X座標
	float m_titleY = 0.0f;            // Y座標（落下用）
	const int m_titleWidth = 300;     // 幅（当たり判定）
	const int m_titleHeight = 50;     // 高さ（当たり判定）
	bool m_isTitleFalling = false;    // 落下中フラグ

	bool m_titleTrapUsed = false;   // 罠が発動済みかどうか
	bool m_titleTrapActive = false; // 現在罠が動いているか（落下中か）

	bool m_bPlayedDeathSE = false;

	CollisonManager coll;
	MapChip maps;
	Player  player;
	CInput  input;

	EffectManager Effectmanager;

public:
	TitleScene();
	~TitleScene();

	int Loop();
	void Draw();
};