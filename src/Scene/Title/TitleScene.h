#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/Collision.h"
#include "../../Collision/Manager/CollisionManager.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"
#include "../../Font/Font.h"

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

public:
	TitleScene();
	~TitleScene();

	int Loop();
	void Draw();
};
