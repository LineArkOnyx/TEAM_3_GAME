#include "SelectScene.h"

#define PLAYER_SPEED (10)
#define GRAY_COLOR  (125,125,125)

void SelectScene::Init()
{

	PlayerPosX = 0.0f;
	PlayerPosY = 0.0f;
	CurrentStage = 0;
	DecisionStage = 0;
	NextStage = 0;
	m_IsOverX = false;
	m_IsOverY = false;
	m_IsMove = false;


}
void SelectScene::Load()
{

	PlayerPosX = m_eStageData[CurrentStage].x;
	PlayerPosY = m_eStageData[CurrentStage].y;

	NextStage = -1;

	StageIconHandle = LoadGraph(ISLAND_HANDLE);
	PlayerIconHandle = LoadGraph(PLAYER_HANDLE);


}
int SelectScene::Step()
{

	float kakudo;

	//kakudo = atan2f((m_eStageData[1].x - m_eStageData[0].x), (m_eStageData[1].y - m_eStageData[0].y));
	kakudo = atan2f((m_eStageData[NextStage].x - m_eStageData[CurrentStage].x),
		(m_eStageData[NextStage].y - m_eStageData[CurrentStage].y));


	if (CInput::IsKeyPush(KEY_INPUT_RIGHT) && !m_IsMove)
	{
		if (m_eStageData[CurrentStage].AfterStage != -1)
		{
			NextStage = m_eStageData[CurrentStage].AfterStage;
			m_IsMove = true;

			if (m_eStageData[CurrentStage].x < m_eStageData[CurrentStage + 1].x)
				m_IsOverX = true;
			else m_IsOverX = false;
		}
		else;

	}
	if (CInput::IsKeyPush(KEY_INPUT_LEFT) && !m_IsMove)
	{
		if (m_eStageData[CurrentStage].BeforeStage != -1)
		{
			NextStage = m_eStageData[CurrentStage].BeforeStage;
			m_IsMove = true;

			if (m_eStageData[CurrentStage].x < m_eStageData[CurrentStage - 1].x)
				m_IsOverX = true;
			else m_IsOverX = false;
		}
		else;
	}

	if (m_IsMove)
	{
		PlayerPosX += sinf(kakudo) * PLAYER_SPEED;
		PlayerPosY += cosf(kakudo) * PLAYER_SPEED;

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

	DrawBox(0, 0, 1280, 720, GetColor(50, 70, 225), true);

	for (int Index = 0; Index < STAGE_MAX; Index++)
	{
		if (Index < STAGE_MAX - 1)
		{
			DrawLineAA(m_eStageData[Index].x, m_eStageData[Index].y,
				m_eStageData[Index + 1].x, m_eStageData[Index + 1].y, GRAY_COLOR);    // 線を描画
		}

		DrawRotaGraph((int)m_eStageData[Index].x, (int)m_eStageData[Index].y, 1.0f, 0.0f, StageIconHandle, true);


	}

	DrawRotaGraph((int)PlayerPosX, (int)PlayerPosY, 1.0f, 0.0f, PlayerIconHandle, true);

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