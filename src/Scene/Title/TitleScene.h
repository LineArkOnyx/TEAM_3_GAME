#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/Collision.h"
#include "../../Collision/Manager/CollisionManager.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"
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

	//マウスカーソル
	int MousePosX;
	int MousePosY;

	//スタートボタン
	float m_fStartPosX;
	float m_fStartPosY;
	int m_iStartHndl;

	bool buttonReach;

	int TitleHndl;
	double Exlate;

public:
	TitleScene();
	~TitleScene();

	int Loop();
	void Draw();
};