#include "TitleScene.h"

//��`
const char TITLE_START_PATH[] = { "data/Title/Goal.png" };
const float MOUSEPOINT_RADIUS = 3.0f;
const int STARTBUTTON_WIDHT = 250;
const int STARTBUTTON_HEIGHT = 150;

void TitleScene::Init()
{
	m_fStartPosX = 200.0f;
	m_fStartPosY = 200.0f;

	m_iStartHndl = -1;
	TitleHndl = -1;
	Exlate = 15.0;

	buttonReach = false;

	// �g�����W�V�����������i�㉺����o�Ē����ŏd�Ȃ�AU�^�[���ŏ�����j
	Move::Init();
	isTransitionFinished = false;
}
void TitleScene::Load()
{
	if (m_iStartHndl == -1) {
		m_iStartHndl = LoadGraph(TITLE_START_PATH);
		TitleHndl = LoadGraph("data/background.png");
	}
	Font::FontHandleLoad();
}
int TitleScene::Step()
{
	SetMouseDispFlag(TRUE);

	// �g�����W�V�������̓}�E�X����ȂǃX�L�b�v
	if (!Move::IsFinished()) {
		Move::Update();
		return 0;
	}
	isTransitionFinished = true;

	GetMousePoint(&MousePosX, &MousePosY);

	int Sequence = 0;
	buttonReach = false;

	DrawFormatString(100, 120, GetColor(255, 0, 0), "%d", MousePosX);
	DrawFormatString(100, 140, GetColor(255, 0, 0), "%d", MousePosY);

	if (IsHitSphereAndRectCollision((float)MousePosX, (float)MousePosY, MOUSEPOINT_RADIUS, m_fStartPosX, m_fStartPosY, STARTBUTTON_WIDHT, STARTBUTTON_HEIGHT))
	{
		buttonReach = true;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			Sequence = 1;
		}
	}

	return Sequence;
}
void TitleScene::Exit()
{

}

TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{

}

int TitleScene::Loop()
{
	int SceneCangeFlg = 0;//���^�[������p�̃V�[���؂�ւ��t���O

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
void TitleScene::Draw()
{
	switch (SequenceID)
	{
	case INIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_INIT");
		break;

	case LOAD_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_LOAD");
		break;

	case STEP_SEQUENCE:
		DrawRotaGraph(640, 360, Exlate, 0, TitleHndl, true);
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_STEP");

		if (isTransitionFinished) {
			// �g�����W�V������̂ݕ\��
			DrawGraph(m_fStartPosX, m_fStartPosY, m_iStartHndl, true);
			DrawBox(m_fStartPosX, m_fStartPosY + 5, 53, 53, GetColor(255, 0, 0), buttonReach);
		}

		DrawStringToHandle(0, 0, "�^�C�g��", GetColor(0, 0, 255), Font::fontHandle[���b�N�����[��][_64_6]);
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_EXIT");
		break;
	}
	// �őO�ʂɃg�����W�V�����`��
	Move::Draw();
}

