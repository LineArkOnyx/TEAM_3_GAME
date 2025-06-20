#pragma once

#include "DxLib.h"

#include "../../Collision/Manager/CollisionManager.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"

const int PHASE_NUM = 3;	//ÉQÅ[ÉWÇÃêî

class PlayScene
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

	CollisonManager coll;
	MapChip maps;
	Player  player;
	CInput  input;

public:
	PlayScene();
	~PlayScene();

	int Loop();
	void Draw();
};