#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/Collision.h"
#include "../../Collision/Manager/CollisionManager.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"
#include "../../Font/Font.h"
#include "../../Effect/Effect.h"
#include "../../Sound/SoundManager.h"

// �� �g�����W�V�������o���g�����߂ɒǉ�
#include "Move.h"

class TitleScene
{
private:
	enum SEQUENCE_ID
	{
		INIT_SEQUENCE,
		LOAD_SEQUENCE,
		STEP_SEQUENCE,
		EXIT_SEQUENCE,

		SEQUENCE_NUM,
	};

	SEQUENCE_ID SequenceID = INIT_SEQUENCE;

	void Init();
	void Load();
	int Step();
	void Exit();

	// �}�E�X�J�[�\�����W
	int MousePosX;
	int MousePosY;

	// �X�^�[�g�{�^��
	float m_fStartPosX;
	float m_fStartPosY;
	int m_iStartHndl;
	bool buttonReach;

	// �^�C�g���摜
	int TitleHndl;
	double Exlate;

	// �� �g�����W�V�������o���I��������ǂ���
	bool isTransitionFinished;

	// �^�C�g�������ʒu�E����p
	float m_titleX = 640 - 150;       // X���W
	float m_titleY = 0.0f;            // Y���W�i�����p�j
	const int m_titleWidth = 300;     // ���i�����蔻��j
	const int m_titleHeight = 50;     // �����i�����蔻��j
	bool m_isTitleFalling = false;    // �������t���O

	bool m_titleTrapUsed = false;   // 㩂������ς݂��ǂ���
	bool m_titleTrapActive = false; // ����㩂������Ă��邩�i���������j

	bool m_bPlayedDeathSE = false;

	CollisonManager coll;
	MapChip maps;
	Player  player;
	CInput  input;

	EffectManager Effectmanager;

public:
	TitleScene();
	~TitleScene();

	int Loop();
	void Draw();
};