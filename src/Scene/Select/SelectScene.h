#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
#include "math.h"

#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定(デフォルト)
#define	SCREEN_SIZE_Y	720	// Y方向の画面サイズを指定(デフォルト)

#define STAGE_MAX	(5)

#define PLAYER_HANDLE ("data/Select/kari.png")
#define ISLAND_HANDLE ("data/Select/island.png")

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

	struct STAGE_DATA
	{
		float x;
		float y;

		int id;

		int BeforeStage;
		int AfterStage;
	};

	const STAGE_DATA m_eStageData[STAGE_MAX] =
	{

		{100.0f,300.0f,0,-1,1},
		{300.0f,200.0f,1,0,2},
		{500.0f,500.0f,2,1,3},
		{700.0f,400.0f,3,2,4},
		{900.0f,100.0f,4,3,-1},

	};

	SEQUENCE_ID SequenceID = INIT_SEQUENCE;

	void Init();
	void Load();
	int Step();
	void Exit();

	float PlayerPosX;
	float PlayerPosY;

	int CurrentStage;
	int NextStage;
	int DecisionStage;

	bool m_IsMove;

	bool m_IsOverX;
	bool m_IsOverY;

	int StageIconHandle;
	int PlayerIconHandle;

public:
	SelectScene() = default;
	~SelectScene() = default;

	int Loop();
	void Draw();
};