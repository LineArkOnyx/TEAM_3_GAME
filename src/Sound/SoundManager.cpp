#include "SoundManager.h"

int CSoundManager::m_iHndl[SOUNDID_NUM];

//-------------------------------------------------
//                 �R���X�g���N�g
//-------------------------------------------------
CSoundManager::CSoundManager(void)
{
	for (int SoundIndex = 0; SoundIndex < SOUNDID_NUM; SoundIndex++)
	{
		m_iHndl[SoundIndex] = -1;
	}
}

//-------------------------------------------------
//                 �f�X�g���N�g
//-------------------------------------------------
CSoundManager::~CSoundManager(void)
{
	Exit();
}

//-------------------------------------------------
//                 �@�@������
//-------------------------------------------------
void CSoundManager::Init(void)
{
	for (int SoundIndex = 0; SoundIndex < SOUNDID_NUM; SoundIndex++)
	{
		m_iHndl[SoundIndex] = -1;
	}
}

//-------------------------------------------------
//                 �@ �I������
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
//                �S�f�[�^�ǂݍ���
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
		// ��ł����[�h���s������΃t���O���I�t��
		if (m_iHndl[SoundIndex] == -1)
		{
			isRet = false;
		}
	}

	return isRet;
}

//-------------------------------------------------
//             �Đ����Ԏ擾(�~���b)
//-------------------------------------------------
int CSoundManager::GetSoundTime(tagSoundID iID)
{
	return (int)GetSoundCurrentTime(m_iHndl[iID]);
}

//-------------------------------------------------
//            �Đ������Ԏ擾(�~���b)
//-------------------------------------------------
int CSoundManager::GetSoundAllTime(tagSoundID iID)
{
	return (int)GetSoundTotalTime(m_iHndl[iID]);
}

//-------------------------------------------------
//             �@�@���y�Đ�����
//-------------------------------------------------
bool CSoundManager::IsPlay(tagSoundID iID)
{
	return CheckSoundMem(m_iHndl[iID]) == 1 ? true : false;
}

//-------------------------------------------------
//             �@�Đ��J�n���Ԑݒ�
//-------------------------------------------------
void CSoundManager::SetStartFrame(tagSoundID iID, int ms)
{
	// �w��ID�̎��g�����擾���Đݒ�
	int iFreq = GetFrequencySoundMem(m_iHndl[iID]) * ms / 1000;
	SetCurrentPositionSoundMem(iFreq, m_iHndl[iID]);
}

//-------------------------------------------------
//             �@�@�{�����[���ݒ�
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
//             �@�@�@ ���y�Đ�
//-------------------------------------------------
int CSoundManager::Play(tagSoundID iID, int iType, bool isStart)
{
	CSoundManager::SetVolume(iID, 0.4f);
	CSoundManager::SetVolume(SOUNDID_SE_HIT, 0.3f);
	return PlaySoundMem(m_iHndl[iID], iType, isStart);
}

//-------------------------------------------------
//             �@�@�@ ���y��~
//-------------------------------------------------
int CSoundManager::Stop(tagSoundID iID)
{
	return StopSoundMem(m_iHndl[iID]);
}

//-------------------------------------------------
//             �@�@�@�S���y��~
//-------------------------------------------------
void CSoundManager::StopAll(void)
{
	for (int SoundIndex = 0; SoundIndex < SOUNDID_NUM; SoundIndex++)
	{
		StopSoundMem(m_iHndl[SoundIndex]);
	}
}