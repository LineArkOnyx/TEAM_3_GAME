#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/Collision.h"
#include "../../Collision/Manager/CollisionManager.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"
#include "../../Font/Font.h"

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

public:
	TitleScene();
	~TitleScene();

	int Loop();
	void Draw();
};
