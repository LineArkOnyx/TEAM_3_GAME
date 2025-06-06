#pragma once

#include "Title/TitleScene.h"
#include "Select/SelectScene.h"
#include "Play/PlayScene.h"
#include "Result/ResultScene.h"

class SceneManager
{
private:
	enum tagSCENE {
		SCENE_TITLE,	//�^�C�g�����
		SCENE_SELECT,	//�Z���N�g���
		SCENE_PLAY,		//�Q�[�������
		SCENE_RESULT,	//���U���g���

		SCENE_NUM
	};

	
	tagSCENE m_eSceneID;		//�V�[���ۑ�

	TitleScene cTitle;
	SelectScene cSelect;
	PlayScene cPlay;
	ResultScene cResult;

public:
	//�R���X�g���N�^
	SceneManager();

	//�J��Ԃ��s������
	void Loop();

	//�`�揈��
	void Draw();
};

