#include "PlayScene.h"

void PlayScene::Init()
{
	maps.Init();

	player.Init();

	Effectmanager.Init();
}
void PlayScene::Load()
{
	ReadStageNumber();

	maps.Load(num);

	//トラップ生成(仮)
	switch (num) {
	case 0:
		maps.CreatePITFALL(576 - 16, 720 - 64, 64, 64, 17, 1, 20, 23);
		maps.CreateTrap(UP_MOVE, 300, 720 - 64, 64, 64, 64, 750, 1000, 64, 3);
		break;
	case 1:

		break;
	case 2:

		break;
	default:

		break;
	}

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

	if (!player.GetAlliveFlag()) {
		SequenceID = INIT_SEQUENCE;
	}
	
	return Sequence;
}
void PlayScene::Exit()
{
	
	Effectmanager.Fin();
}

void PlayScene::ReadStageNumber(){
	FILE* fp;
	fopen_s(&fp, _Path, "rb+");
	if (fp != NULL)
	{
		fread(&num, sizeof(int), 1, fp);
		fclose(fp);
	}
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
		
		maps.Draw();
		player.Draw();
		DrawFormatString(0, 0, GetColor(255, 255, 0), "%d", num);

		Effectmanager.Draw();
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "PLAY_EXIT");
		break;

	default:
		break;
	}
}