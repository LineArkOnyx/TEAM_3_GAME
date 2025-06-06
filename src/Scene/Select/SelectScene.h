#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
class SelectScene
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

public:
	SelectScene();
	~SelectScene();

	int Loop();
	void Draw();
};