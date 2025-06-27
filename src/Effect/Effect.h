#pragma once
#include "DxLib.h"

#define EFFECT_MAX_HNDL (16)

#define EFFECT_NAX_NUM (16)

enum Effect_ID {

	EFFECT_ID_DEAD = 0,
	EFFECT_ID_POINT,

	EFFECT_ID_MAX,
};



struct EFFECT_DATA {
	int E_ID;				// ID
	char E_IMG_PATH[128];	// �t�@�C���p�X
	int E_MAX_FLAME;		// �ő�t���[��
	int E_SIZE;				// �s�N�Z����
	int E_NUM_X;			// ���̕�����
	int E_NUM_Y;			// �c�̕�����
};



class Effect {

private:
	int m_ID;				// ID
	int m_Hndl[EFFECT_MAX_HNDL];			// �摜�n���h��(�ꉞ�ő�l��16��)
	float m_Pos_X;			// �\���ʒu
	float m_Pos_Y;			// �\���ʒu
	int m_CurrentFlame;		// ���݃t���[��
	bool m_IsActive;		// �������t���O

	int m_MaxFlame;			// �ő�t���[��
	int m_Size;				// �s�N�Z����
	int m_Num_X;			// ���̕�����
	int m_Num_Y;			// �c�̕�����
public:
	Effect();
	~Effect();

	//������
	void Init();
	//�ǂ݂���
	void Load(EFFECT_DATA _EffectData);
	//�ʏ폈��
	void Step();
	//�`�揈��
	void Draw();
	//�I������
	void Fin();
	//�X�V����
	void Update();

	//�Ăяo��
	void Request(int _Pos_X, int _Pos_Y);

	int GetID() { return m_ID; }
};



class EffectManager {

private:

	Effect m_cEffect[EFFECT_NAX_NUM];

	EFFECT_DATA m_EffectData[EFFECT_ID_MAX] = {
		{EFFECT_ID_DEAD,"data/Effect/Dead.png",4,32,2,2 },
		{EFFECT_ID_POINT,"data/Effect/Dead_2.png",4,32,2,2 },
	};

public:

	EffectManager();
	~EffectManager();

	//������
	void Init();
	//�ǂ݂���
	void Load();
	//�ʏ폈��
	void Step();
	//�`�揈��
	void Draw();
	//�I������
	void Fin();
	//�X�V����
	void Update();

	//�Ăяo��
	void Request(int _Pos_X, int _Pos_Y,int _ID);
};