#pragma once
#include "DxLib.h"

enum tagSoundID {
		// BGM
		SOUNDID_BGM_TITLE,			// タイトル画面のBGM
		SOUNDID_BGM_PLAY,			// ゲーム中のBGM
		
		// SE
		SOUNDID_SE_DECISION,		// SE 決定
		SOUNDID_SE_CANCEL,			// SE キャンセル
		SOUNDID_SE_WALK,			// SE 歩き
		SOUNDID_SE_JUMP,			// SE ジャンプ
		SOUNDID_SE_GOAL,			// SE ゴール
		SOUNDID_SE_HIT,				// SE 被弾(タヒ)
		SOUNDID_SE_HYUN,			// SE ひゅーん
		SOUNDID_SE_JAKIN,			// SE じゃきん


		SOUNDID_NUM
	};

//=================================================
//				サウンド操作クラス
//=================================================
class CSoundManager
{
private:
	int m_iHndl[SOUNDID_NUM];	// サウンドハンドル

	static CSoundManager* m_Instance;//インスタンス

public:
	CSoundManager();
	~CSoundManager();

	//インスタンス取得
	static CSoundManager* GetInstance();
	//インスタンス破棄
	static void DeleteInstance();

	// 初期化
	void Init();
	// 終了処理
	void Exit();

	// 全データ読み込み
	// @return : true = 全ロード成功 false = 一つ以上読み込み失敗
	bool LoadAllData();

	//****************************************
	//				取得関係
	//****************************************
	// 再生時間取得(ミリ秒)
	// @memo : 圧縮形式の再生データは不可らしい
	int GetSoundTime(tagSoundID iID);
	// 再生総時間取得(ミリ秒)
	int GetSoundAllTime(tagSoundID iID);
	// 音楽再生判定
	// @[iID]  : データ読み込みした際のID番号
	// @return : true = 再生中, false = 停止中
	bool IsPlay(tagSoundID iID);

	//****************************************
	//				設定関係
	//****************************************
	// 再生開始時間設定
	// @[ms] : 再生開始時間(ミリ秒)
	// @memo : Play()前に設定し、Play()では途中から再生にしてください
	//         使用時は必ず停止してからにしましょう
	void SetStartFrame(tagSoundID iID, int ms);
	// ボリューム設定
	// @[fVol] : ボリューム(0.0～1.0)
	void SetVolume(tagSoundID iID, float fVol);

	//****************************************
	//			　音楽再生関係
	//****************************************
	// 音楽再生
	// @[iID]		:	データ読み込みした際のID番号
	// @[iType]		:	再生タイプ DXライブラリと同じ
	//					DX_PLAYTYPE_NORMAL	:	ノーマル再生
	//					DX_PLAYTYPE_BACK	:	バックグラウンド再生
	//					DX_PLAYTYPE_LOOP	:	ループ再生
	// @[isStart]	:	true = 最初から再生, false = 途中から再生
	// @return		:	0 = 成功, -1 = エラー
	int Play(tagSoundID iID, int iType = DX_PLAYTYPE_BACK, bool isStart = true);

	// 音楽停止
	// @[iID]	:	データ読み込みした際のID番号
	// @return	:	0 = 成功, -1 = エラー
	int Stop(tagSoundID iID);
	// 全音楽停止
	void StopAll(void);
};