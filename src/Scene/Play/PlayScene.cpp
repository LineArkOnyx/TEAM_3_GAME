#include "PlayScene.h"

void PlayScene::Init()
{
	maps.Init();
}
void PlayScene::Load()
{
	maps.Load();
	//トラップ生成(仮)
	maps.CreatePITFALL(0, 0, 1, 1, 4, 23);
	maps.CreateTrap(RIGHT_MOVE, 0, 0, 64, 0, 64, 64);
}
int PlayScene::Step()
{
	int Sequence = 0;

	coll.PlayerToMap(maps);
	maps.Step();
	
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
		maps.Draw();
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "PLAY_EXIT");
		break;

	default:
		break;
	}
}