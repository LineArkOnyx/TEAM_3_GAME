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

	// トランジション初期化
	Move::Init();
	isTransitionFinished = false;

	// プレイヤー初期化
	player.Init(0);

	// タイトル文字位置リセット
	m_titleY = 0.0f;
	m_isTitleFalling = false;

	m_isTitleFalling = false;
	m_titleTrapUsed = false;
	m_titleTrapActive = false;
}

void TitleScene::Load()
{
	if (m_iStartHndl == -1) {
		m_iStartHndl = LoadGraph(TITLE_START_PATH);
		TitleHndl = LoadGraph("data/background.png");
	}

	// サウンドデータを読み込む（成功チェックも入れると良い）
	bool loadSoundSuccess = CSoundManager::GetInstance()->LoadAllData();
	if (!loadSoundSuccess) {
;
	}

	// タイトルBGMをループ再生
	CSoundManager::GetInstance()->Play(SOUNDID_BGM_TITLE, DX_PLAYTYPE_LOOP);

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

	// プレイヤーの画面外判定（シーン切替）
	float px = player.GetXPos();
	float py = player.GetYPos();

	if (px < 0 || px > 1280 || py < 0 || py > 720 + player.GetHeight()) {
		return 1;  // シーン切替
	}

	// プレイヤー操作・当たり判定処理
	player.Step();
	coll.PlayerToMap(player, maps);
	player.Update();

	int Sequence = 0;
	buttonReach = false;

	const float TITLE_FALL_TRIGGER_X = 400.0f;

	if (!m_isTitleFalling && !m_titleTrapUsed && player.GetXPos() > TITLE_FALL_TRIGGER_X) {
		m_isTitleFalling = true;   // 罠が落ち始める
		m_titleTrapUsed = true;    // 罠は一度しか使えない
		m_titleTrapActive = true;  // 罠は現在落下中
	}

	// タイトル文字落下処理
	if (m_isTitleFalling) {
		m_titleY += 7.0f;

		if (IsHitRect(m_titleX, m_titleY, m_titleWidth, m_titleHeight,
			player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight())) {

			// プレイヤーに当たったら死亡処理など
			player.Init(0);

			// 罠の落下終了
			m_isTitleFalling = false;
			m_titleTrapActive = false;
			m_titleY = 0.0f;

		}
		else if (m_titleY > 720) {
			// 罠が画面外まで落ちたらリセット
			m_isTitleFalling = false;
			m_titleTrapActive = false;
			m_titleY = 0.0f;
		}
	}
	float tx = player.GetXPos();

	// 1100を超えたらシーン遷移
	if (tx > m_fStartPosX) {
		return 1;  // シーン切替を示す値（例えば1）
	}

	if (!player.GetAlliveFlag()) {
		if (!m_bPlayedDeathSE) {
			CSoundManager::GetInstance()->Play(SOUNDID_SE_DEATH);
			CSoundManager::GetInstance()->SetVolume(SOUNDID_SE_DEATH, 0.6f);
			m_bPlayedDeathSE = true;
		}

		// プレイヤー死亡した瞬間に罠は「未使用状態」に戻す
		m_titleTrapUsed = false;

		// タイトル落下フラグはもちろん落ちていない状態に
		m_isTitleFalling = false;
		m_titleTrapActive = false;
		m_titleY = 0.0f;

		// プレイヤーを復活させる（既存処理）
		player.Init(0);
	}
	else {
		// プレイヤー生存中はフラグを戻しておく（次回死亡SE再生のため）
		m_bPlayedDeathSE = false;
	}


	// スタートボタンのマウス判定
	if (IsHitSphereAndRectCollision((float)MousePosX, (float)MousePosY, MOUSEPOINT_RADIUS,
		m_fStartPosX, m_fStartPosY, STARTBUTTON_WIDTH, STARTBUTTON_HEIGHT)) {
		buttonReach = true;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			Sequence = 1;
		}

	}

	return Sequence;
}

void TitleScene::Exit()
{
	CSoundManager::GetInstance()->Stop(SOUNDID_BGM_TITLE);
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

int TitleScene::Loop()
{
	int SceneCangeFlg = 0;

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
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_STEP");

		if (isTransitionFinished) {
			// トランジション後にボタン・タイトル表示
			DrawGraph(m_fStartPosX, m_fStartPosY, m_iStartHndl, true);
			DrawStringToHandle((int)m_titleX, (int)m_titleY,
				"デビルもどき", GetColor(0, 0, 255),
				Font::fontHandle[かくめい][_64_6]);
			// ★ ここに「スタート」という青文字を追加
			DrawString(m_fStartPosX-20, m_fStartPosY - 20, "スタート", GetColor(0, 0, 255));
		}

		player.Draw();  // プレイヤー描画
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_EXIT");
		break;
	}

	// 最前面にトランジション演出
	Move::Draw();
}
