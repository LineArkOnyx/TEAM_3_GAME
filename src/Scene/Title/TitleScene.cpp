#include "TitleScene.h"

// 定義
const char TITLE_START_PATH[] = "data/Title/Goal.png";
const float MOUSEPOINT_RADIUS = 3.0f;
const int STARTBUTTON_WIDTH = 250;
const int STARTBUTTON_HEIGHT = 150;

void TitleScene::Init()
{
	maps.Init();
	coll.Init();
	Effectmanager.Init();

	m_fStartPosX = 1100.0f;
	m_fStartPosY = 610.0f;

	m_iStartHndl = -1;
	TitleHndl = -1;

	buttonReach = false;

	// トランジション初期化（上下から出て中央で重なり、Uターンで消える）
	Move::Init();
	isTransitionFinished = false;

	// プレイヤー初期化
	player.Init(0);

	// タイトル文字位置リセット
	m_titleY = 0.0f;
	m_isTitleFalling = false;
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

	// トランジション中は処理スキップ
	if (!Move::IsFinished()) {
		Move::Update();
		return 0;
	}
	isTransitionFinished = true;

	GetMousePoint(&MousePosX, &MousePosY);

	// 画面外判定（プレイヤーが画面外に落ちたらシーン切替）
	float px = player.GetXPos();
	float py = player.GetYPos();

	if (px < 0 || px > 1280 || py < 0 || py > 720 + player.GetHeight()) {
		return 1;  // シーン切替フラグ
	}

	// プレイヤー操作・当たり判定
	player.Step();
	coll.PlayerToMap(player, maps);
	player.Update();

	int Sequence = 0;
	buttonReach = false;
	
	// 例：Y座標が400を超えたら、タイトルが落ちてくる
	const float TITLE_FALL_TRIGGER_Y = 400.0f;

	if (!m_isTitleFalling && player.GetYPos() > TITLE_FALL_TRIGGER_Y) {
		m_isTitleFalling = true;
	}

	// タイトル文字が落下中はY座標を下げる
	if (m_isTitleFalling) {
		m_titleY += 5.0f;  // 落下速度

		
	}

	// タイトル文字とプレイヤーの当たり判定（落下中のみ）
	if (m_isTitleFalling) {
		if (IsHitRect(m_titleX, m_titleY, m_titleWidth, m_titleHeight,
			player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight())) {
			return 1;
		}
	}

	// プレイヤーが死んだらシーン切替
	if (!player.GetAlliveFlag()) {
		player.SetAliveFlg(false);  // プレイヤー死亡フラグセット
	}

	// スタートボタン判定
	if (IsHitSphereAndRectCollision((float)MousePosX, (float)MousePosY, MOUSEPOINT_RADIUS, m_fStartPosX, m_fStartPosY, STARTBUTTON_WIDTH, STARTBUTTON_HEIGHT)) {
		buttonReach = true;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			Sequence = 1;
		}
	}

	return Sequence;
}

void TitleScene::Exit()
{
	// 必要なら終了処理をここに
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

int TitleScene::Loop()
{
	int SceneCangeFlg = 0; // シーン切替フラグ

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

			// タイトル文字描画（落下位置に応じてY座標変化）
			DrawStringToHandle((int)m_titleX, (int)m_titleY, "デビルもどき", GetColor(0, 0, 255), Font::fontHandle[かくめい][_64_6]);
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