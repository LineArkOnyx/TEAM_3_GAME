#include "TitleScene.h"


//定義
const char TITLE_START_PATH[] = "data/Title/Goal.png";
const float MOUSEPOINT_RADIUS = 3.0f;
const int STARTBUTTON_WIDTH = 250;
const int STARTBUTTON_HEIGHT = 150;

void TitleScene::Init()
{
	maps.Init();
	coll.Init();
	Effectmanager.Init();


	m_fStartPosX = 1050.0f;
	m_fStartPosY = 400.0f;

	m_iStartHndl = -1;
	TitleHndl = -1;

	buttonReach = false;

	// トランジション初期化（上下から出て中央で重なり、Uターンで消える）
	Move::Init();
	isTransitionFinished = false;

	//プレイヤー初期化
	player.Init(0);




}
void TitleScene::Load()
{
	if (m_iStartHndl == -1) {
		m_iStartHndl = LoadGraph(TITLE_START_PATH);
		TitleHndl = LoadGraph("data/background.png");
	}
	maps.Load(STAGE_TITLE);  
	player.Load();
	Font::FontHandleLoad();
}
int TitleScene::Step()
{
	SetMouseDispFlag(TRUE);

	// トランジション中はマウス判定などスキップ
	if (!Move::IsFinished()) {
		Move::Update();
		return 0;
	}
	isTransitionFinished = true;

	GetMousePoint(&MousePosX, &MousePosY);

	// プレイヤー操作処理
	player.Step();
	// マップとの当たり判定
	coll.PlayerToMap(player, maps);

	player.Update();


	int Sequence = 0;
	buttonReach = false;

	DrawFormatString(100, 120, GetColor(255, 0, 0), "%d", MousePosX);
	DrawFormatString(100, 140, GetColor(255, 0, 0), "%d", MousePosY);

	if (IsHitSphereAndRectCollision((float)MousePosX, (float)MousePosY, MOUSEPOINT_RADIUS, m_fStartPosX, m_fStartPosY, STARTBUTTON_WIDTH, STARTBUTTON_HEIGHT))
	{
		buttonReach = true;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			Sequence = 1;
		}
	}

	return Sequence;
}
void TitleScene::Exit()
{

}

TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{

}

int TitleScene::Loop()
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
void TitleScene::Draw()
{
	maps.Draw(); 

	switch (SequenceID)
	{
	case INIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_INIT");
		break;

	case LOAD_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_LOAD");
		break;

	case STEP_SEQUENCE:
		//DrawGraph(0, 0, TitleHndl, true);
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_STEP");

		if (isTransitionFinished) {
			// トランジション後のみ表示
			DrawGraph(m_fStartPosX, m_fStartPosY, m_iStartHndl, true);

			DrawStringToHandle(640 - 150, 0, "デビルもどき", GetColor(0, 0, 255), Font::fontHandle[かくめい][_64_6]);
		}

		// プレイヤー描画
		player.Draw();

		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_EXIT");

		break;
	}

	// 最前面にトランジション描画
	Move::Draw();
}

