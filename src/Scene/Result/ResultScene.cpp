#include "ResultScene.h"

void ResultScene::Init()
{
	imghndl = 0;
}
void ResultScene::Load()
{
	imghndl = LoadGraph("data/Title/Rider.png");
}
int ResultScene::Step()
{
	int Sequence = 0;
	if (CInput::IsKeyPush(KEY_INPUT_RETURN)) {
		Sequence = 1;
	}
	return Sequence;
}
void ResultScene::Exit()
{
	imghndl = 0;
}

ResultScene::ResultScene()
{

}
ResultScene::~ResultScene()
{

}

int ResultScene::Loop()
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

		if (Step() != 0) {
			SequenceID = EXIT_SEQUENCE;
		}
		break;

	case EXIT_SEQUENCE:

		Exit();
		SequenceID = INIT_SEQUENCE;
		SceneCangeFlg = 1;
		break;

	default:
		break;
	}

	return SceneCangeFlg;
}
void ResultScene::Draw()
{
	switch (SequenceID)
	{
	case INIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "RESULT_INIT");
		break;

	case LOAD_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "RESULT_LOAD");
		break;

	case STEP_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "RESULT_STEP");

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawGraph(0, 0, imghndl, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "RESULT_EXIT");
		break;

	default:
		break;
	}
}