#pragma once
#include "DxLib.h"

using namespace std;

//定義
//プレイヤーの画像を分割したときの最大数
constexpr int IMG_MAX_NUM = 128;

class Player
{
private:
	enum tagPlayerState {
		PLAYER_STATE_NORMAL,	//待機
		PLAYER_STATE_RIGHT_RUN,	//右に走る
		PLAYER_STATE_LEFT_RUN,	//左に走る
		PLAYER_STATE_JUMP		//ジャンプ
	};

	enum tagDir {
		UP = 0,		//上方向
		DOWN,		//下方向
		LEFT,		//左方向
		RIGHT		//右方向
	};

	float m_fXPos;
	float m_fYPos;
	float m_fNextXPos;
	float m_fNextYPos;
	float m_fRot;

	float m_fWidth;
	float m_fHeight;

	float m_fXSpeed;
	float m_fYSpeed;

	int m_iHndl[IMG_MAX_NUM];
	int m_iImgNum;					//描画する画像の配列番号

	int m_iFreamCnt;		//フレームカウント用変数
	int m_iSecond;			//秒

	bool m_bIsAlive;		//生存フラグ
	bool m_bIsJump;			//ジャンプフラグ

	tagPlayerState m_eState;
	tagPlayerState m_eOldState;
	tagDir m_eDir;

public:
	Player();
	~Player();

	//初期化
	void Init();
	//読みこみ
	void Load();
	//通常処理
	void Step();
	//描画処理
	void Draw();
	//終了処理
	void Fin();
	//更新処理
	void Update();
	//重力
	void Gravity();

	//操作処理
	void Control();		//左右移動

	void Move();		//移動
	void Jump();		//ジャンプ

	//アニメーション
	void Animation();

	//フレーム
	void CntFream();
	void ResetFream();
	void InitFream();
	void ResetSecond();

public:
	//取得関数
	float GetXPos() { return m_fXPos; }		//X座標取得
	float GetYPos() { return m_fYPos; }		//Y座標取得

	//更新後のX座標
	float GetNextXPos() { return m_fNextXPos; }
	//更新後のY座標
	float GetNextYPos() { return m_fNextYPos; }

	//横幅取得
	float GetWidth() { return m_fWidth; }
	//縦幅取得
	float GetHeight() { return m_fHeight; }

	//生存フラグ取得
	bool GetAlliveFlag() { return m_bIsAlive; }
	//ジャンプフラグ取得
	bool GetJumpFlag() { return m_bIsJump; }
	//方向チェック
	void GetMoveDir(bool* _DirArray);

public:
	//設定関数
	//X座標の設定
	void SetXPos(float Pos) { m_fXPos = Pos; }
	//Y座標の設定
	void SetYPos(float Pos) { m_fYPos = Pos; }

	//更新後のX座標の設定
	void SetNextXPos(float Pos) { m_fNextXPos = Pos; }
	//更新後のY座標の設定
	void SetNextYPos(float Pos) { m_fNextYPos = Pos; }

	//ジャンプフラグの設定
	void SetJumpFlag(bool flag) { m_bIsJump = flag; }
};