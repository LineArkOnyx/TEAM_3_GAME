#include "PlayScene.h"

void PlayScene::Init()
{
	maps.Init();

	player.Init();

	Effectmanager.Init();
}
void PlayScene::Load()
{
	maps.Load();
	//トラップ生成(仮)
	maps.CreatePITFALL(600, 720 - 64, 64, 64, 18, 1, 23, 23);
	maps.CreateTrap(UP_MOVE, 300, 720 - 64, 64, 64, 64, 720, 1000, 64);

	player.Load();

	Effectmanager.Load();
}
int PlayScene::Step()
{
	int Sequence = 0;

	player.Step();
	coll.PlayerToMap(player, maps);

	maps.Step();

	player.Update();

	Effectmanager.Step();
	Effectmanager.Update();
	
	return Sequence;
}
void PlayScene::Exit()
{
	
	Effectmanager.Fin();
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
		player.Draw();

		Effectmanager.Draw();
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "PLAY_EXIT");
		break;

	default:
		break;
	}
}