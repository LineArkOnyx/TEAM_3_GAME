#pragma once

#include "DxLib.h"

#include "../../Collision/Manager/CollisionManager.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"


#include "../../Effect/Effect.h"

const int PHASE_NUM = 3;	//ÉQÅ[ÉWÇÃêî

const char _Path[256] = {
	"data/File/data.bin",
};

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

	EffectManager Effectmanager;

	void ReadStageNumber();

	int num;

public:
	PlayScene();
	~PlayScene();

	int Loop();
	void Draw();
};