#include "PlayScene.h"
#include "../../Sound/SoundManager.h"

void PlayScene::Init()
{
	ReadStageNumber();
	coll.Init();
	maps.Init();


	player.Init(num);

	Effectmanager.Init();

	if (!CSoundManager::GetInstance()->IsPlay(SOUNDID_BGM_PLAY)) {
		CSoundManager::GetInstance()->LoadAllData();
		CSoundManager::GetInstance()->Play(SOUNDID_BGM_PLAY);
		CSoundManager::GetInstance()->SetVolume(SOUNDID_BGM_PLAY, 1.0f);
	}

	aoriManager.Init();

	nextNum = 0;
}
void PlayScene::Load()
{

	maps.Load(num);

	//トラップ生成(仮)
	switch (num) {
	case 0:
		maps.CreatePITFALL(576, 720 - 64, 64, 64, 17, 1, 21, 23);
		maps.CreateTrap(UP_MOVE, 300, 720 - 64, 64, 64, 64, 750, 1000, 64, -1, -64, 7.6);
		break;
	case 1:
		maps.CreatePITFALL(576, 7 * 32 - 16, 64, 32, 21, 9, 27, 23);
		maps.CreateTrap(RIGHT_MOVE, 27 * 32, 7 * 32, 64, 256, 27 * 32, 10 * 32, 96, 32, 1280, -1, 7.6); 
		break;
	case 2:
		maps.CreatePITFALL(5 * 32, 11 * 32, 128, 32, 9, 8, 12, 9);
		maps.CreatePITFALL(5 * 32, 11 * 32, 128, 32, 5, 13, 13, 14);
		break;
	default:

		break;
	}

	player.Load();

	Effectmanager.Load();

	aoriManager.Load();
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

	if (coll.goal) {
		SequenceID = INIT_SEQUENCE;
		num = num + 1;
		SaveStageNumber();
		nextNum = num;
		if (nextNum > 4) {
			Sequence = 1;
		}
	}
	
	aoriManager.Step();

	return Sequence;
}
void PlayScene::Exit()
{
	CSoundManager::GetInstance()->Exit();
	Effectmanager.Fin();

	aoriManager.Exit();
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

void PlayScene::SaveStageNumber(){
	FILE* fp;
	fopen_s(&fp, _Path, "wb+");
	if (fp != NULL)
	{
		fwrite(&num, sizeof(int), 1, fp);
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

		aoriManager.Draw();
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "PLAY_EXIT");
		break;

	default:
		break;
	}
}