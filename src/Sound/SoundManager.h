#pragma once
#include "DxLib.h"

enum tagSoundID {
		// BGM
		SOUNDID_BGM_TITLE,			// �^�C�g����ʂ�BGM
		SOUNDID_BGM_PLAY,			// �Q�[������BGM
		
		// SE
		SOUNDID_SE_DECISION,		// SE ����
		SOUNDID_SE_CANCEL,			// SE �L�����Z��
		SOUNDID_SE_WALK,			// SE ����
		SOUNDID_SE_JUMP,			// SE �W�����v
		SOUNDID_SE_GOAL,			// SE �S�[��
		SOUNDID_SE_HIT,				// SE ��e(�^�q)
		SOUNDID_SE_HYUN,			// SE �Ђ�[��
		SOUNDID_SE_JAKIN,			// SE ���Ⴋ��


		SOUNDID_NUM
	};

//=================================================
//				�T�E���h����N���X
//=================================================
class CSoundManager
{
private:
	int m_iHndl[SOUNDID_NUM];	// �T�E���h�n���h��

	static CSoundManager* m_Instance;//�C���X�^���X

public:
	CSoundManager();
	~CSoundManager();

	//�C���X�^���X�擾
	static CSoundManager* GetInstance();
	//�C���X�^���X�j��
	static void DeleteInstance();

	// ������
	void Init();
	// �I������
	void Exit();

	// �S�f�[�^�ǂݍ���
	// @return : true = �S���[�h���� false = ��ȏ�ǂݍ��ݎ��s
	bool LoadAllData();

	//****************************************
	//				�擾�֌W
	//****************************************
	// �Đ����Ԏ擾(�~���b)
	// @memo : ���k�`���̍Đ��f�[�^�͕s�炵��
	int GetSoundTime(tagSoundID iID);
	// �Đ������Ԏ擾(�~���b)
	int GetSoundAllTime(tagSoundID iID);
	// ���y�Đ�����
	// @[iID]  : �f�[�^�ǂݍ��݂����ۂ�ID�ԍ�
	// @return : true = �Đ���, false = ��~��
	bool IsPlay(tagSoundID iID);

	//****************************************
	//				�ݒ�֌W
	//****************************************
	// �Đ��J�n���Ԑݒ�
	// @[ms] : �Đ��J�n����(�~���b)
	// @memo : Play()�O�ɐݒ肵�APlay()�ł͓r������Đ��ɂ��Ă�������
	//         �g�p���͕K����~���Ă���ɂ��܂��傤
	void SetStartFrame(tagSoundID iID, int ms);
	// �{�����[���ݒ�
	// @[fVol] : �{�����[��(0.0�`1.0)
	void SetVolume(tagSoundID iID, float fVol);

	//****************************************
	//			�@���y�Đ��֌W
	//****************************************
	// ���y�Đ�
	// @[iID]		:	�f�[�^�ǂݍ��݂����ۂ�ID�ԍ�
	// @[iType]		:	�Đ��^�C�v DX���C�u�����Ɠ���
	//					DX_PLAYTYPE_NORMAL	:	�m�[�}���Đ�
	//					DX_PLAYTYPE_BACK	:	�o�b�N�O���E���h�Đ�
	//					DX_PLAYTYPE_LOOP	:	���[�v�Đ�
	// @[isStart]	:	true = �ŏ�����Đ�, false = �r������Đ�
	// @return		:	0 = ����, -1 = �G���[
	int Play(tagSoundID iID, int iType = DX_PLAYTYPE_BACK, bool isStart = true);

	// ���y��~
	// @[iID]	:	�f�[�^�ǂݍ��݂����ۂ�ID�ԍ�
	// @return	:	0 = ����, -1 = �G���[
	int Stop(tagSoundID iID);
	// �S���y��~
	void StopAll(void);
};