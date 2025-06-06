#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
class ResultScene
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

	int imghndl = 0;

	void Init();
	void Load();
	int Step();
	void Exit();

public:
	ResultScene();
	~ResultScene();

	int Loop();
	void Draw();
};