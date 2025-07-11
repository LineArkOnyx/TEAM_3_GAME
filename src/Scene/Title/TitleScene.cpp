#include "TitleScene.h"

// ��`
const char TITLE_START_PATH[] = "data/Title/Goal.png";
const float MOUSEPOINT_RADIUS = 3.0f;
const int STARTBUTTON_WIDTH = 250;
const int STARTBUTTON_HEIGHT = 150;

void TitleScene::Init()
{
	maps.Init();
	coll.Init();
	Effectmanager.Init();

	m_fStartPosX = 1100.0f;
	m_fStartPosY = 610.0f;

	m_iStartHndl = -1;
	TitleHndl = -1;

	buttonReach = false;

	// �g�����W�V�����������i�㉺����o�Ē����ŏd�Ȃ�AU�^�[���ŏ�����j
	Move::Init();
	isTransitionFinished = false;

	// �v���C���[������
	player.Init(0);

	// �^�C�g�������ʒu���Z�b�g
	m_titleY = 0.0f;
	m_isTitleFalling = false;
}

void TitleScene::Load()
{
	if (m_iStartHndl == -1) {
		m_iStartHndl = LoadGraph(TITLE_START_PATH);
		TitleHndl = LoadGraph("data/background.png");
	}
	maps.Load(STAGE_TITLE);
	player.Load();
	Font::FontHandleLoad();
}

int TitleScene::Step()
{
	SetMouseDispFlag(TRUE);

	// �g�����W�V�������͏����X�L�b�v
	if (!Move::IsFinished()) {
		Move::Update();
		return 0;
	}
	isTransitionFinished = true;

	GetMousePoint(&MousePosX, &MousePosY);

	// ��ʊO����i�v���C���[����ʊO�ɗ�������V�[���ؑցj
	float px = player.GetXPos();
	float py = player.GetYPos();

	if (px < 0 || px > 1280 || py < 0 || py > 720 + player.GetHeight()) {
		return 1;  // �V�[���ؑփt���O
	}

	// �v���C���[����E�����蔻��
	player.Step();
	coll.PlayerToMap(player, maps);
	player.Update();

	int Sequence = 0;
	buttonReach = false;
	
	// ��FY���W��400�𒴂�����A�^�C�g���������Ă���
	const float TITLE_FALL_TRIGGER_Y = 400.0f;

	if (!m_isTitleFalling && player.GetYPos() > TITLE_FALL_TRIGGER_Y) {
		m_isTitleFalling = true;
	}

	// �^�C�g����������������Y���W��������
	if (m_isTitleFalling) {
		m_titleY += 5.0f;  // �������x

		
	}

	// �^�C�g�������ƃv���C���[�̓����蔻��i�������̂݁j
	if (m_isTitleFalling) {
		if (IsHitRect(m_titleX, m_titleY, m_titleWidth, m_titleHeight,
			player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight())) {
			return 1;
		}
	}

	// �v���C���[�����񂾂�V�[���ؑ�
	if (!player.GetAlliveFlag()) {
		player.SetAliveFlg(false);  // �v���C���[���S�t���O�Z�b�g
	}

	// �X�^�[�g�{�^������
	if (IsHitSphereAndRectCollision((float)MousePosX, (float)MousePosY, MOUSEPOINT_RADIUS, m_fStartPosX, m_fStartPosY, STARTBUTTON_WIDTH, STARTBUTTON_HEIGHT)) {
		buttonReach = true;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			Sequence = 1;
		}
	}

	return Sequence;
}

void TitleScene::Exit()
{
	// �K�v�Ȃ�I��������������
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

int TitleScene::Loop()
{
	int SceneCangeFlg = 0; // �V�[���ؑփt���O

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
	maps.Draw();

	switch (SequenceID)
	{
	case INIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_INIT");
		break;

	case LOAD_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_LOAD");
		break;

	case STEP_SEQUENCE:
		//DrawGraph(0, 0, TitleHndl, true);
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_STEP");

		if (isTransitionFinished) {
			// �g�����W�V������̂ݕ\��
			DrawGraph(m_fStartPosX, m_fStartPosY, m_iStartHndl, true);

			// �^�C�g�������`��i�����ʒu�ɉ�����Y���W�ω��j
			DrawStringToHandle((int)m_titleX, (int)m_titleY, "�f�r�����ǂ�", GetColor(0, 0, 255), Font::fontHandle[�����߂�][_64_6]);
		}

		// �v���C���[�`��
		player.Draw();

		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_EXIT");
		break;
	}

	// �őO�ʂɃg�����W�V�����`��
	Move::Draw();
}