#include "SelectScene.h"

#define PLAYER_SPEED (5)
#define KASOUKU_PLAYER (3)
//#define LINE_COLOR  GetColor(200,200,200)
#define LINE_COLOR  GetColor(255,100,0)
//#define BACK_COLOR  GetColor(55,55,255)
#define BACK_COLOR  GetColor(55,0,55)

void SelectScene::Init()
{

	PlayerPosX = 0.0f;
	PlayerPosY = 0.0f;
	CurrentStage = 0;
	DecisionStage = 0;
	NextStage = 0;
	Current_Anime = 0;
	AnimeFrame = 0;
	kasoku = 0;
	m_IsOverX = false;
	m_IsOverY = false;
	m_IsMove = false;
	m_Iskasoku = false;
	muki = true;

}
void SelectScene::Load()
{

	PlayerPosX = m_eStageData[CurrentStage].x;
	PlayerPosY = m_eStageData[CurrentStage].y;

	NextStage = -1;

	LoadDivGraph(PLAYER_DIV_HANDLE, ANIME_NUM_PLAYER, 
				 2, 2, 32, 32, PlayerIconDivHandle);

	LoadDivGraph(PLAYER_SHADOW_HANDLE, ANIME_NUM_PLAYER, 
				 2, 2, 32, 32, PlayerShadowHandle);

	StageIconHandle = LoadGraph(ISLAND_HANDLE);
	PlayerIconHandle = LoadGraph(PLAYER_HANDLE);


	/*for (int i = 0; i < ANIME_NUM_PLAYER; i++)
		GraphFilter(PlayerShadowHandle[i], DX_GRAPH_FILTER_TWO_COLOR,
					0, GetColor(0, 0, 128), 1, GetColor(255, 255, 0), 255);*/

}
int SelectScene::Step()
{

	float kakudo;

	//kakudo = atan2f((m_eStageData[1].x - m_eStageData[0].x), (m_eStageData[1].y - m_eStageData[0].y));
	kakudo = atan2f((m_eStageData[NextStage].x - m_eStageData[CurrentStage].x),
		(m_eStageData[NextStage].y - m_eStageData[CurrentStage].y));

	if (CInput::IsKeyKeep(KEY_INPUT_LSHIFT))
	{
		m_Iskasoku = true;
	}
	else
	{
		m_Iskasoku = false;
	}

	if (!m_Iskasoku) kasoku = 0;
	else kasoku = KASOUKU_PLAYER;


	if (CInput::IsKeyPush(KEY_INPUT_RIGHT) && !m_IsMove ||
		CInput::IsKeyPush(KEY_INPUT_D) && !m_IsMove)
	{
		if (m_eStageData[CurrentStage].AfterStage != -1)
		{
			NextStage = m_eStageData[CurrentStage].AfterStage;
			m_IsMove = true;

			if (m_eStageData[CurrentStage].x < m_eStageData[CurrentStage + 1].x)
			{
				m_IsOverX = true;
				muki = true;
			}
			else 
			{
				m_IsOverX = false;
				muki = false;
			}
		}
		else;

	}
	if (CInput::IsKeyPush(KEY_INPUT_LEFT) && !m_IsMove ||
		CInput::IsKeyPush(KEY_INPUT_A) && !m_IsMove)
	{
		if (m_eStageData[CurrentStage].BeforeStage != -1)
		{
			NextStage = m_eStageData[CurrentStage].BeforeStage;
			m_IsMove = true;

			if (m_eStageData[CurrentStage].x < m_eStageData[CurrentStage - 1].x)
			{
				m_IsOverX = true;
				muki = true;
			}
			else
			{
				m_IsOverX = false;
				muki = false;
			}
		}
		else;
	}

	if (m_IsMove)
	{
		PlayerPosX += sinf(kakudo) * (PLAYER_SPEED + kasoku);
		PlayerPosY += cosf(kakudo) * (PLAYER_SPEED + kasoku);

		if (m_IsOverX)
		{
			if (m_eStageData[NextStage].x < PlayerPosX)
			{
				PlayerPosX = m_eStageData[NextStage].x;
				PlayerPosY = m_eStageData[NextStage].y;

				m_IsMove = false;
				CurrentStage = NextStage;
				NextStage = -1;

			}
		}
		else
		{
			if (m_eStageData[NextStage].x > PlayerPosX)
			{

				PlayerPosX = m_eStageData[NextStage].x;
				PlayerPosY = m_eStageData[NextStage].y;

				m_IsMove = false;
				CurrentStage = NextStage;
				NextStage = -1;

			}
		}

	}

	int Sequence = 0;

	if (CInput::IsKeyPush(KEY_INPUT_RETURN) && !m_IsMove) {
		Sequence = 1;
		DecisionStage = CurrentStage;

	}
	return Sequence;
}
void SelectScene::Exit()
{

}

//SelectScene::SelectScene()
//{
//
//}
//SelectScene::~SelectScene()
//{
//
//}

void SelectScene::SaveStageNumber(){
	FILE* fp;
	fopen_s(&fp, Path, "wb+");
	if (fp != NULL)
	{
		fwrite(&DecisionStage, sizeof(int), 1, fp);
		fclose(fp);
	}
}

int SelectScene::Loop()
{
	int SceneCangeFlg = 0;//リターンする用のシーン切り替えフラグ

	switch (SequenceID)
	{
	case INIT_SEQUENCE:

		Init();
		SequenceID = LOAD_SEQUENCE;
		break;

	case LOAD_SEQUENCE:

		Load();
		SequenceID = STEP_SEQUENCE;
		break;

	case STEP_SEQUENCE:

		if (Step() != 0) {
			SequenceID = EXIT_SEQUENCE;
		}
		break;

	case EXIT_SEQUENCE:
		SaveStageNumber();
		Exit();
		SequenceID = INIT_SEQUENCE;
		SceneCangeFlg = 1;
		break;

	default:
		break;
	}

	return SceneCangeFlg;
}
void SelectScene::Draw()
{

	DrawBox(0, 0, 1280, 720, BACK_COLOR, true);

	for (int Index = 0; Index < STAGE_MAX; Index++)
	{
		if (Index < STAGE_MAX - 1)
		{
			DrawLineAA(m_eStageData[Index].x, m_eStageData[Index].y,
				m_eStageData[Index + 1].x, m_eStageData[Index + 1].y, LINE_COLOR);    // 線を描画
		}

		DrawRotaGraph((int)m_eStageData[Index].x, (int)m_eStageData[Index].y, 1.0f, 0.0f, StageIconHandle, true);


	}

	AnimationPlayer();

	/*switch (SequenceID)
	{
	case INIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "SELECT_INIT");
		break;

	case LOAD_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "SELECT_LOAD");
		break;

	case STEP_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "SELECT_STEP");
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "SELECT_EXIT");
		break;

	default:
		break;
	}*/
}

void SelectScene::AnimationPlayer()
{
	if (!m_IsMove)
	{
		AnimeFrame = 0;
		Current_Anime = 0;

		/*DrawRotaGraph((int)PlayerPosX, (int)PlayerPosY, 1.0f, 0.0f,
					  PlayerIconDivHandle[Current_Anime], true,!muki);*/
	}

	else
	{
		/*DrawRotaGraph((int)PlayerPosX, (int)PlayerPosY, 1.0f, 0.0f,
					  PlayerIconDivHandle[Current_Anime],true,!muki);*/

		if (AnimeFrame < m_ePlayerData[Current_Anime].AnimeFrame)
		{
			if (!kasoku) AnimeFrame++;
			else AnimeFrame += 2;
		}
		else
		{
			if (Current_Anime < ANIME_WALK_LOOP)
			{
				Current_Anime++;
			}

			else Current_Anime = 0;

			AnimeFrame = 0;
		}

		
	
	}


	DrawRotaGraph((int)PlayerPosX, (int)PlayerPosY, 1.2f, 0.0f,
		PlayerShadowHandle[Current_Anime], true, !muki);


	DrawRotaGraph((int)PlayerPosX, (int)PlayerPosY, 1.0f, 0.0f,
		PlayerIconDivHandle[Current_Anime], true, !muki);

}