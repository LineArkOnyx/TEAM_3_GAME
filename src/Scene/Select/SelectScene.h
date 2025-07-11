#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
#include "math.h"

#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定(デフォルト)
#define	SCREEN_SIZE_Y	720	// Y方向の画面サイズを指定(デフォルト)

#define STAGE_MAX	(5)
#define ANIME_NUM_PLAYER (4)
#define ANIME_WALK_LOOP (2)

#define PLAYER_HANDLE ("data/Select/kari.png")
#define PLAYER_DIV_HANDLE ("data/Player/Player_debi_original.png")
#define PLAYER_SHADOW_HANDLE ("data/Select/Shadow.png")
#define ISLAND_HANDLE ("data/Select/溶けたかぼちゃプリン.png")

const char Path[256] = {
	"data/File/data.bin",
};

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

	struct ANIME_DATA
	{
		int AnimeFrame;

	};

	const STAGE_DATA m_eStageData[STAGE_MAX] =
	{

		{100.0f,300.0f,0,-1,1},
		{300.0f,200.0f,1,0,2},
		{500.0f,500.0f,2,1,3},
		{700.0f,400.0f,3,2,4},
		{900.0f,100.0f,4,3,-1},

	};

	const ANIME_DATA m_ePlayerData[ANIME_NUM_PLAYER] =
	{
		10,
		12,
		5,
		1,
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
	int kasoku;

	bool m_IsMove;
	bool m_Iskasoku;

	bool muki;
	bool m_IsOverX;
	bool m_IsOverY;

	int StageIconHandle;
	int PlayerIconDivHandle[ANIME_NUM_PLAYER];
	int PlayerShadowHandle[ANIME_NUM_PLAYER];

	int Current_Anime;
	int AnimeFrame;
	int PlayerIconHandle;
	

	void SaveStageNumber();

	void AnimationPlayer();

public:

	SelectScene() = default;
	~SelectScene() = default;

	int Loop();
	void Draw();
};