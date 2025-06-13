#include "LevelDevilPlayer.h"


//定義
//横幅
constexpr float PLAYER_WIDTH = 0.0f;
//縦幅
constexpr float PLAYER_HEIGHT = 0.0f;

//プレイヤーのスピード
constexpr float PLAYER_SPEED = 3.0f;
constexpr float PLAYER_JUMP_SPEED = 8.0f;

//プレイヤーに与える重力
constexpr float PLAYER_GRAVITY = 0.6f;
constexpr float PLAYER_MAX_GRAVITY = 5.5f;

//プレイヤーの画像パス
constexpr char PLAYER_IMG_PATH[] = { "" };

//読み込み関連
constexpr int IMG_ALL_NUM = 1;
constexpr int IMG_X_NUM = 1;
constexpr int IMG_Y_NUM = 1;
constexpr int IMG_X_SIZE = 32;
constexpr int IMG_Y_SIZE = 32;

Player::Player()
{
	m_fXPos = 0.0f;
	m_fYPos = 0.0f;
	m_fNextXPos = 0.0f;
	m_fNextYPos = 0.0f;
	m_fRot = 0.0f;

	m_fWidth = 0.0f;
	m_fHeight = 0.0f;

	m_fXSpeed = 0.0f;
	m_fYSpeed = 0.0f;

	memset(m_iHndl, -1, sizeof(m_iHndl));

	m_eState = PLAYER_STATE_NORMAL;

	m_bIsAlive = false;
	m_bIsJump = false;
}

Player::~Player()
{

}

void Player::Init()
{

}

void Player::Load()
{
	for (int i = 0; i < IMG_ALL_NUM; i++) {
		if (m_iHndl[i] = -1)
		{
			LoadDivGraph(PLAYER_IMG_PATH, IMG_ALL_NUM, IMG_X_NUM, IMG_Y_NUM, IMG_X_SIZE, IMG_Y_SIZE, m_iHndl);
		}
	}
}

void Player::Step()
{
	m_fNextXPos = m_fXPos;
	m_fNextYPos = m_fYPos;

	//操作
	Control();
	//重力
	Gravity();
	//ジャンプ
	Jump();
	//移動
	Move();
}

void Player::Draw()
{
	DrawBox(m_fXPos, m_fYPos, m_fXPos + 32, m_fYPos + 32, GetColor(255, 0, 0), true);
}

void Player::Fin()
{

}

void Player::Update()
{
	m_fXPos = m_fNextXPos;
	m_fYPos = m_fNextYPos;
}

void Player::Gravity()
{
	//重力を与える
	if (m_fYSpeed < PLAYER_MAX_GRAVITY) {
		m_fYSpeed += PLAYER_GRAVITY;
	}
	//縦方向に当たったら止める
	if (m_fNextYPos >= 720 - 32)
	{
		m_fNextYPos = 720-32;
	}
}

void Player::Control()
{
	float fSpd = 0.0f;

	if (CheckHitKey(KEY_INPUT_D))
	{
		fSpd = PLAYER_SPEED;
		m_eState = PLAYER_STATE_RUN;
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		fSpd = -PLAYER_SPEED;
		m_eState = PLAYER_STATE_RUN;
	}

	m_fXSpeed = fSpd;
}

void Player::Jump()
{
	if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W)) {
		if (!m_bIsJump) {
			m_bIsJump = true;
			m_fYSpeed = -PLAYER_JUMP_SPEED;
		}
	}
}

void Player::Move()
{
	//移動処理
	m_fNextXPos += m_fXSpeed;
	m_fNextYPos += m_fYSpeed;
}

void Player::GetMoveDir(bool* _DirArray)
{
	//右方向のチェック
	if (m_fNextXPos > m_fXPos) {
		_DirArray[RIGHT] = true;
	}
	//左方向チェック　
	if (m_fNextXPos < m_fXPos) {
		_DirArray[LEFT] = true;
	}
	//下方向チェック
	if (m_fNextYPos > m_fYPos) {
		_DirArray[DOWN] = true;
	}
	//上方向チェック
	if (m_fNextYPos < m_fYPos) {
		_DirArray[UP] = true;
	}
}