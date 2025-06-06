#include "PlayScene.h"

void PlayScene::Init()
{
	
}
void PlayScene::Load()
{
	
}
int PlayScene::Step()
{
	int Sequence = 0;
	
	return Sequence;
}
void PlayScene::Exit()
{
	
	
}

PlayScene::PlayScene()
{

}
PlayScene::~PlayScene()
{

}

int PlayScene::Loop()
{
	int SceneCangeFlg = 0;//リターンする用のシーン切り替えフラグ

	switch (SequenceID)
	{
	case INIT_SEQUENCE:

		Init();
		SequenceID = LOAD_SEQUENCE;
		break;

	case LOAD_SEQUENCE:

		Load();
		SequenceID = STEP_SEQUENCE;
		break;

	case STEP_SEQUENCE:

		if (Step() != 0)
		{
			SequenceID = EXIT_SEQUENCE;
		}
		break;

	case EXIT_SEQUENCE:

		Exit();
		SceneCangeFlg = 1;
		SequenceID = INIT_SEQUENCE;
		break;

	default:
		break;
	}

	return SceneCangeFlg;
}
void PlayScene::Draw()
{
	switch (SequenceID)
	{
	case INIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "PLAY_INIT");
		break;

	case LOAD_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "PLAY_LOAD");
		break;

	case STEP_SEQUENCE:
		
		DrawFormatString(0, 0, GetColor(255, 255, 0), "PLAY_STEP");
		
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "PLAY_EXIT");
		break;

	default:
		break;
	}
}