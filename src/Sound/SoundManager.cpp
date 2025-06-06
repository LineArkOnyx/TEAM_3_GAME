#include "SoundManager.h"

int CSoundManager::m_iHndl[SOUNDID_NUM];

//-------------------------------------------------
//                 コンストラクト
//-------------------------------------------------
CSoundManager::CSoundManager(void)
{
	for (int SoundIndex = 0; SoundIndex < SOUNDID_NUM; SoundIndex++)
	{
		m_iHndl[SoundIndex] = -1;
	}
}

//-------------------------------------------------
//                 デストラクト
//-------------------------------------------------
CSoundManager::~CSoundManager(void)
{
	Exit();
}

//-------------------------------------------------
//                 　　初期化
//-------------------------------------------------
void CSoundManager::Init(void)
{
	for (int SoundIndex = 0; SoundIndex < SOUNDID_NUM; SoundIndex++)
	{
		m_iHndl[SoundIndex] = -1;
	}
}

//-------------------------------------------------
//                 　 終了処理
//-------------------------------------------------
void CSoundManager::Exit(void)
{
	for (int SoundIndex = 0; SoundIndex < SOUNDID_NUM; SoundIndex++)
	{
		if (m_iHndl[SoundIndex] != -1)
		{
			DeleteSoundMem(m_iHndl[SoundIndex]);
			m_iHndl[SoundIndex] = -1;
		}
	}
}
//-------------------------------------------------
//                全データ読み込み
//-------------------------------------------------
bool CSoundManager::LoadAllData()
{
	bool isRet = true;
	const char pFileName[SOUNDID_NUM][128] =
	{
		"data/Sound/BGM/TitleBGM.mp3",
		"data/Sound/BGM/PlayBGM.mp3",
		"data/Sound/SE/Decision.mp3",
		"data/Sound/SE/Cancel.mp3",
		"data/Sound/SE/Whip.mp3",
		"data/Sound/SE/Magic.mp3",
		"data/Sound/SE/Hit.mp3",
		"data/Sound/SE/Recover.mp3",
	};

	for (int SoundIndex = 0; SoundIndex < SOUNDID_NUM; SoundIndex++)
	{
		m_iHndl[SoundIndex] = LoadSoundMem(pFileName[SoundIndex]);
		// 一つでもロード失敗があればフラグをオフに
		if (m_iHndl[SoundIndex] == -1)
		{
			isRet = false;
		}
	}

	return isRet;
}

//-------------------------------------------------
//             再生時間取得(ミリ秒)
//-------------------------------------------------
int CSoundManager::GetSoundTime(tagSoundID iID)
{
	return (int)GetSoundCurrentTime(m_iHndl[iID]);
}

//-------------------------------------------------
//            再生総時間取得(ミリ秒)
//-------------------------------------------------
int CSoundManager::GetSoundAllTime(tagSoundID iID)
{
	return (int)GetSoundTotalTime(m_iHndl[iID]);
}

//-------------------------------------------------
//             　　音楽再生判定
//-------------------------------------------------
bool CSoundManager::IsPlay(tagSoundID iID)
{
	return CheckSoundMem(m_iHndl[iID]) == 1 ? true : false;
}

//-------------------------------------------------
//             　再生開始時間設定
//-------------------------------------------------
void CSoundManager::SetStartFrame(tagSoundID iID, int ms)
{
	// 指定IDの周波数を取得して設定
	int iFreq = GetFrequencySoundMem(m_iHndl[iID]) * ms / 1000;
	SetCurrentPositionSoundMem(iFreq, m_iHndl[iID]);
}

//-------------------------------------------------
//             　　ボリューム設定
//-------------------------------------------------
void CSoundManager::SetVolume(tagSoundID iID, float fVol)
{
	if (fVol < 0.f || fVol>1.f)
	{
		return;
	}

	ChangeVolumeSoundMem((int)(255.f * fVol), m_iHndl[iID]);
}

//-------------------------------------------------
//             　　　 音楽再生
//-------------------------------------------------
int CSoundManager::Play(tagSoundID iID, int iType, bool isStart)
{
	CSoundManager::SetVolume(iID, 0.4f);
	CSoundManager::SetVolume(SOUNDID_SE_HIT, 0.3f);
	return PlaySoundMem(m_iHndl[iID], iType, isStart);
}

//-------------------------------------------------
//             　　　 音楽停止
//-------------------------------------------------
int CSoundManager::Stop(tagSoundID iID)
{
	return StopSoundMem(m_iHndl[iID]);
}

//-------------------------------------------------
//             　　　全音楽停止
//-------------------------------------------------
void CSoundManager::StopAll(void)
{
	for (int SoundIndex = 0; SoundIndex < SOUNDID_NUM; SoundIndex++)
	{
		StopSoundMem(m_iHndl[SoundIndex]);
	}
}