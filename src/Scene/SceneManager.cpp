#include "SceneManager.h"

//��`�֘A


//�R���X�g���N�^
SceneManager::SceneManager()
{
	//�ŏ��̓^�C�g����ʂ�
	m_eSceneID = SCENE_TITLE;
}

void SceneManager::Loop()
{
	//�S�[�����������S���������肷��
	int End = 0;

	//�����͂ЂƂ܂�switch���𗘗p����
	switch (m_eSceneID)
	{
	case SceneManager::SCENE_TITLE:
		//�^�C�g���̃G���h�V�[���܂ŗ�����
		if (cTitle.Loop() != 0) 
		{
			//�Z���N�g�V�[���Ɉړ�����
			m_eSceneID = SCENE_SELECT;
		}
		break;
	case SceneManager::SCENE_SELECT:
		//�Z���N�g�̃G���h�܂ŗ�����
		if(cSelect.Loop() != 0)
		{
			//�v���C�V�[���ɍs��
			m_eSceneID = SCENE_PLAY;
		}
		break;
	case SceneManager::SCENE_PLAY:
		if (cPlay.Loop() != 0)
		{
			//���U���g�V�[���ɍs��
			m_eSceneID = SCENE_RESULT;
		}
		break;
	case SceneManager::SCENE_RESULT:
		if (cResult.Loop() != 0)
		{
			//�^�C�g���V�[���ɍs��
			m_eSceneID = SCENE_TITLE;
		}
		break;
	}
}

//�X�V����
void SceneManager::Draw()
{
	switch (m_eSceneID)
	{
	case SceneManager::SCENE_TITLE:
		cTitle.Draw();
		break;
	case SceneManager::SCENE_SELECT:
		cSelect.Draw();
		break;
	case SceneManager::SCENE_PLAY:
		cPlay.Draw();
		break;
	case SceneManager::SCENE_RESULT:
		cResult.Draw();
		break;
	}
}
