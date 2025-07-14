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

	// �g�����W�V����������
	Move::Init();
	isTransitionFinished = false;

	// �v���C���[������
	player.Init(0);

	// �^�C�g�������ʒu���Z�b�g
	m_titleY = 0.0f;
	m_isTitleFalling = false;

	m_isTitleFalling = false;
	m_titleTrapUsed = false;
	m_titleTrapActive = false;
}

void TitleScene::Load()
{
	if (m_iStartHndl == -1) {
		m_iStartHndl = LoadGraph(TITLE_START_PATH);
		TitleHndl = LoadGraph("data/background.png");
	}

	// �T�E���h�f�[�^��ǂݍ��ށi�����`�F�b�N�������Ɨǂ��j
	bool loadSoundSuccess = CSoundManager::GetInstance()->LoadAllData();
	if (!loadSoundSuccess) {
;
	}

	// �^�C�g��BGM�����[�v�Đ�
	CSoundManager::GetInstance()->Play(SOUNDID_BGM_TITLE, DX_PLAYTYPE_LOOP);

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

	// �v���C���[�̉�ʊO����i�V�[���ؑցj
	float px = player.GetXPos();
	float py = player.GetYPos();

	if (px < 0 || px > 1280 || py < 0 || py > 720 + player.GetHeight()) {
		return 1;  // �V�[���ؑ�
	}

	// �v���C���[����E�����蔻�菈��
	player.Step();
	coll.PlayerToMap(player, maps);
	player.Update();

	int Sequence = 0;
	buttonReach = false;

	const float TITLE_FALL_TRIGGER_X = 400.0f;

	if (!m_isTitleFalling && !m_titleTrapUsed && player.GetXPos() > TITLE_FALL_TRIGGER_X) {
		m_isTitleFalling = true;   // 㩂������n�߂�
		m_titleTrapUsed = true;    // 㩂͈�x�����g���Ȃ�
		m_titleTrapActive = true;  // 㩂͌��ݗ�����
	}

	// �^�C�g��������������
	if (m_isTitleFalling) {
		m_titleY += 7.0f;

		if (IsHitRect(m_titleX, m_titleY, m_titleWidth, m_titleHeight,
			player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight())) {

			// �v���C���[�ɓ��������玀�S�����Ȃ�
			player.Init(0);

			// 㩂̗����I��
			m_isTitleFalling = false;
			m_titleTrapActive = false;
			m_titleY = 0.0f;

		}
		else if (m_titleY > 720) {
			// 㩂���ʊO�܂ŗ������烊�Z�b�g
			m_isTitleFalling = false;
			m_titleTrapActive = false;
			m_titleY = 0.0f;
		}
	}
	float tx = player.GetXPos();

	// 1100�𒴂�����V�[���J��
	if (tx > m_fStartPosX) {
		return 1;  // �V�[���ؑւ������l�i�Ⴆ��1�j
	}

	if (!player.GetAlliveFlag()) {
		if (!m_bPlayedDeathSE) {
			CSoundManager::GetInstance()->Play(SOUNDID_SE_DEATH);
			CSoundManager::GetInstance()->SetVolume(SOUNDID_SE_DEATH, 0.6f);
			m_bPlayedDeathSE = true;
		}

		// �v���C���[���S�����u�Ԃ�㩂́u���g�p��ԁv�ɖ߂�
		m_titleTrapUsed = false;

		// �^�C�g�������t���O�͂�����񗎂��Ă��Ȃ���Ԃ�
		m_isTitleFalling = false;
		m_titleTrapActive = false;
		m_titleY = 0.0f;

		// �v���C���[�𕜊�������i���������j
		player.Init(0);
	}
	else {
		// �v���C���[�������̓t���O��߂��Ă����i���񎀖SSE�Đ��̂��߁j
		m_bPlayedDeathSE = false;
	}


	// �X�^�[�g�{�^���̃}�E�X����
	if (IsHitSphereAndRectCollision((float)MousePosX, (float)MousePosY, MOUSEPOINT_RADIUS,
		m_fStartPosX, m_fStartPosY, STARTBUTTON_WIDTH, STARTBUTTON_HEIGHT)) {
		buttonReach = true;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			Sequence = 1;
		}

	}

	return Sequence;
}

void TitleScene::Exit()
{
	CSoundManager::GetInstance()->Stop(SOUNDID_BGM_TITLE);
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

int TitleScene::Loop()
{
	int SceneCangeFlg = 0;

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
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_STEP");

		if (isTransitionFinished) {
			// �g�����W�V������Ƀ{�^���E�^�C�g���\��
			DrawGraph(m_fStartPosX, m_fStartPosY, m_iStartHndl, true);
			DrawStringToHandle((int)m_titleX, (int)m_titleY,
				"�f�r�����ǂ�", GetColor(0, 0, 255),
				Font::fontHandle[�����߂�][_64_6]);
			// �� �����Ɂu�X�^�[�g�v�Ƃ���������ǉ�
			DrawString(m_fStartPosX-20, m_fStartPosY - 20, "�X�^�[�g", GetColor(0, 0, 255));
		}

		player.Draw();  // �v���C���[�`��
		break;

	case EXIT_SEQUENCE:
		DrawFormatString(0, 0, GetColor(255, 255, 0), "TITLE_EXIT");
		break;
	}

	// �őO�ʂɃg�����W�V�������o
	Move::Draw();
}
