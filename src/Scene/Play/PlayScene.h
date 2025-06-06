#pragma once

#include "DxLib.h"

#include "../../MapChip/MapChip.h"

const int PHASE_NUM = 3;	//�Q�[�W�̐�

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

	MapChip maps;
	CInput  input;

public:
	PlayScene();
	~PlayScene();

	int Loop();
	void Draw();
};