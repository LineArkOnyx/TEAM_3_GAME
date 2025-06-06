#include "SelectScene.h"

void SelectScene::Init()
{

}
void SelectScene::Load()
{

}
int SelectScene::Step()
{
	int Sequence = 0;
	if (CInput::IsKeyPush(KEY_INPUT_RETURN)) {
		Sequence = 1;
	}
	return Sequence;
}
void SelectScene::Exit()
{

}

SelectScene::SelectScene()
{

}
SelectScene::~SelectScene()
{

}

int SelectScene::Loop()
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
void SelectScene::Draw()
{
	switch (SequenceID)
	{
	case INIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "SELECT_INIT");
		break;

	case LOAD_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "SELECT_LOAD");
		break;

	case STEP_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "SELECT_STEP");
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "SELECT_EXIT");
		break;

	default:
		break;
	}
}