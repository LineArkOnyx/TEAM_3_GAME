#include "Effect.h"


EffectManager::EffectManager() {

}
EffectManager::~EffectManager() {

}

//������
void EffectManager::Init() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Init();
	}
}
//�ǂ݂���
void EffectManager::Load() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Load(m_EffectData[0]);
	}
}
//�ʏ폈��
void EffectManager::Step() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Step();
	}
}
//�`�揈��
void EffectManager::Draw() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Draw();
	}
}
//�I������
void EffectManager::Fin() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Fin();
	}
}
//�X�V����
void EffectManager::Update() {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		m_cEffect[i].Update();
	}
}

//�Ăяo��
void EffectManager::Request(int _Pos_X, int _Pos_Y, int _ID) {
	for (int i = 0; i < EFFECT_NAX_NUM; i++) {
		if (m_cEffect[i].GetID() == _ID) {

			m_cEffect[i].Request(_Pos_X, _Pos_Y);
		}
	}
}




Effect::Effect() {
	m_ID = -1;			// ID
	for (int i = 0; i < EFFECT_MAX_HNDL; i++) {
		m_Hndl[i] = -1;	// �摜�n���h��(�ꉞ�ő�l��16��)
	}
	m_Pos_X = 0.0f;		// �\���ʒu
	m_Pos_Y = 0.0f;		// �\���ʒu
	m_CurrentFlame = 0;	// ���݃t���[��
	m_IsActive = false;	// �������t���O

	m_MaxFlame = 0;		// �ő�t���[��
	m_Size = 0;			// �s�N�Z����
	m_Num_X = 0;		// ���̕�����
	m_Num_Y = 0;		// �c�̕�����
}
Effect::~Effect() {

}

//������
void Effect::Init() {
	m_ID = -1;			// ID
	for (int i = 0; i < EFFECT_MAX_HNDL; i++) {
		m_Hndl[i] = -1;	// �摜�n���h��(�ꉞ�ő�l��16��)
	}
	m_Pos_X = 0.0f;		// �\���ʒu
	m_Pos_Y = 0.0f;		// �\���ʒu
	m_CurrentFlame = 0;	// ���݃t���[��
	m_IsActive = false;	// �������t���O

	m_MaxFlame = 0;		// �ő�t���[��
	m_Size = 0;			// �s�N�Z����
	m_Num_X = 0;		// ���̕�����
	m_Num_Y = 0;		// �c�̕�����
}
//�ǂ݂���
void Effect::Load(EFFECT_DATA _EffectData) {
	m_ID = _EffectData.E_ID;				// ID
	m_MaxFlame = _EffectData.E_MAX_FLAME;	// �ő�t���[��
	m_Size = _EffectData.E_SIZE;			// �s�N�Z����
	m_Num_X = _EffectData.E_NUM_X;			// ���̕�����
	m_Num_Y = _EffectData.E_NUM_Y;			// �c�̕�����
	LoadDivGraph(_EffectData.E_IMG_PATH, m_MaxFlame, m_Num_X, m_Num_Y, m_Size, m_Size, m_Hndl);// �摜
}
//�ʏ폈��
void Effect::Step() {

	if (m_IsActive && m_CurrentFlame < m_MaxFlame) {
		m_CurrentFlame++;
	}
	else if (m_CurrentFlame >= m_MaxFlame) {
		m_IsActive = false;
	}
}
//�`�揈��
void Effect::Draw() {
	if (m_IsActive) {
		DrawGraph(m_Pos_X, m_Pos_Y, m_Hndl[m_CurrentFlame], true);
	}
}
//�I������
void Effect::Fin() {
	m_ID = -1;			// ID
	for (int i = 0; i < EFFECT_MAX_HNDL; i++) {
		m_Hndl[i] = { -1 };		// �摜�n���h��(�ꉞ�ő�l��16��)
	}
	m_Pos_X = 0.0f;		// �\���ʒu
	m_Pos_Y = 0.0f;		// �\���ʒu
	m_CurrentFlame = 0;	// ���݃t���[��
	m_IsActive = false;		// �������t���O

	m_MaxFlame = 0;		// �ő�t���[��
	m_Size = 0;			// �s�N�Z����
	m_Num_X = 0;		// ���̕�����
	m_Num_Y = 0;		// �c�̕�����
}
//�X�V����
void Effect::Update() {

}

//�Ăяo��
void Effect::Request(int _Pos_X, int _Pos_Y) {
	m_Pos_X = _Pos_X;
	m_Pos_Y = _Pos_Y;
	m_CurrentFlame = 0;
	m_IsActive = true;
}