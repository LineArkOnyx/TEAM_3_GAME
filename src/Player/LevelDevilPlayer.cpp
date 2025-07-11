#include "LevelDevilPlayer.h"
#include "../../Sound/SoundManager.h"

//定義
//横幅
constexpr float PLAYER_WIDTH = 32.0f;
//縦幅
constexpr float PLAYER_HEIGHT = 32.0f;

//プレイヤーのスピード
constexpr float PLAYER_SPEED = 3.0f;
constexpr float PLAYER_JUMP_SPEED = 11.0f;
constexpr float PLAYER_JUMPPAD_JUMPSPEED = 15.0f;

//プレイヤーに与える重力
constexpr float PLAYER_GRAVITY = 0.6f;
constexpr float PLAYER_MAX_GRAVITY = 5.5f;

//プレイヤーの画像パス
constexpr char PLAYER_IMG_PATH[] = { "data/Player/Player_debi.png" };

//読み込み関連
constexpr int IMG_ALL_NUM = 4;
constexpr int IMG_X_NUM = 2;
constexpr int IMG_Y_NUM = 2;
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

	m_iFreamCnt = 0;
	m_iSecond = 0;

	memset(m_iHndl, -1, sizeof(m_iHndl));
	m_iImgNum = -1;

	m_eState = PLAYER_STATE_NORMAL;
	m_eOldState = PLAYER_STATE_NORMAL;

	m_bIsAlive = false;
	m_bIsJump = false;
	m_bIsJump_pad = false;
}

Player::~Player()
{

}

void Player::Init(int num)
{
	//縦横サイズ
	m_fWidth = PLAYER_WIDTH;
	m_fHeight = PLAYER_HEIGHT;
	//生存フラグ
	m_bIsAlive = true;
	//描画する画像の配列番号
	m_iImgNum = 0;

	switch (num) {
	case 0:
		m_fXPos = 128.0f;
		m_fYPos = 720.0f - 64.0f;
		break;
	case 1:
		m_fXPos = 128.0f;
		m_fYPos = 8 * 32;
		break;
	case 2:
		m_fXPos = 64.0f;
		m_fYPos = 8 * 32;
		break;
	default:
		break;
	}
	
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
	//生存フラグがOFF
	if (!m_bIsAlive) { return; }

	m_fNextXPos = m_fXPos;
	m_fNextYPos = m_fYPos;

	m_eOldState = m_eState;

	//操作
	Control();
	//重力
	Gravity();
	//ジャンプ
	Jump();
	//移動
	Move();
	//殺す
	Death();
}

void Player::Draw()
{
	//生存フラグがOFF
	if (!m_bIsAlive) { return; }
	DrawGraph(m_fXPos, m_fYPos, m_iHndl[m_iImgNum], true);

	//アニメーション
	Animation();
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
}

void Player::Control()
{
	float fSpd = 0.0f;

	if (CheckHitKey(KEY_INPUT_D))
	{
		fSpd = PLAYER_SPEED;
		if (!m_bIsJump) {
			m_eState = PLAYER_STATE_RIGHT_RUN;
		}
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		fSpd = -PLAYER_SPEED;
		if (!m_bIsJump) {
			m_eState = PLAYER_STATE_LEFT_RUN;
		}
	}
	else
	{
		m_eState = PLAYER_STATE_NORMAL;
	}

	m_fXSpeed = fSpd;
}

void Player::Jump()
{
	if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W)) {
		if (!m_bIsJump) {
			m_bIsJump = true;
			m_fYSpeed = -PLAYER_JUMP_SPEED;
			m_eState = PLAYER_STATE_JUMP;
		}
	}
	if (m_bIsJump_pad)
	{
		m_bIsJump = true;
		m_fYSpeed = -PLAYER_JUMPPAD_JUMPSPEED;
		m_eState = PLAYER_STATE_JUMP;
	}
}

void Player::Animation()
{
	//通常時
	if (m_eState == PLAYER_STATE_NORMAL)
	{
		m_iImgNum = 0;
	}
	//右移動
	if (m_eState == PLAYER_STATE_RIGHT_RUN)
	{
		CntFream();
		ResetFream();
		if (m_eOldState == PLAYER_STATE_NORMAL) {
			m_iImgNum = 1;
		}
		if (m_iImgNum >= 2)
		{
			m_iImgNum = 1;
		}
		if (m_iFreamCnt % 15 == 0) {
			m_iImgNum++;
		}
	
	}
	//左移動
	if (m_eState == PLAYER_STATE_LEFT_RUN)
	{
		CntFream();
		ResetFream();
		if (m_eOldState == PLAYER_STATE_NORMAL) {
			m_iImgNum = 1;
		}
		if (m_iImgNum >= 2)
		{
			m_iImgNum = 1;
		}
		if (m_iFreamCnt % 15 == 0) {
			m_iImgNum++;
		}
	}
	//ジャンプ
	if (m_eState == PLAYER_STATE_JUMP)
	{
		m_iImgNum = 3;
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

void Player::CntFream()
{
	//フレームカウント
	m_iFreamCnt++;
}

void Player::InitFream()
{
	//フレームをゼロに
	m_iFreamCnt = 0;
	m_iSecond = 0;
}

void Player::ResetFream()
{
	if (m_iFreamCnt >= 60)
	{
		m_iSecond++;
		m_iFreamCnt = 0;
	}
}

void Player::ResetSecond()
{
	if (m_iSecond >= 10000) {
		m_iSecond = 0;
	}
}

void Player::Death()
{
	if (m_fNextYPos >= 720)
	{
		m_bIsAlive = false;
	}
	if (m_fNextYPos <= 0)
	{
		m_bIsAlive = false;
	}
	if (m_fNextXPos >= 1280)
	{
		m_bIsAlive = false;
	}
	if (m_fNextXPos <= 0)
	{
		m_bIsAlive = false;
	}

	if (m_bIsAlive == false)
	{
		CSoundManager::GetInstance()->Play(SOUNDID_SE_DEATH);
		CSoundManager::GetInstance()->SetVolume(SOUNDID_SE_DEATH, 1.0f);
	}
}