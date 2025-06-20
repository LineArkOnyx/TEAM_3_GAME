#pragma once
#include "DxLib.h"

using namespace std;

//��`
//�v���C���[�̉摜�𕪊������Ƃ��̍ő吔
constexpr int IMG_MAX_NUM = 128;

class Player
{
private:
	enum tagPlayerState {
		PLAYER_STATE_NORMAL,	//�ҋ@
		PLAYER_STATE_RIGHT_RUN,	//�E�ɑ���
		PLAYER_STATE_LEFT_RUN,	//���ɑ���
		PLAYER_STATE_JUMP		//�W�����v
	};

	enum tagDir {
		UP = 0,		//�����
		DOWN,		//������
		LEFT,		//������
		RIGHT		//�E����
	};

	float m_fXPos;
	float m_fYPos;
	float m_fNextXPos;
	float m_fNextYPos;
	float m_fRot;

	float m_fWidth;
	float m_fHeight;

	float m_fXSpeed;
	float m_fYSpeed;

	int m_iHndl[IMG_MAX_NUM];
	int m_iImgNum;					//�`�悷��摜�̔z��ԍ�

	int m_iFreamCnt;		//�t���[���J�E���g�p�ϐ�
	int m_iSecond;			//�b

	bool m_bIsAlive;		//�����t���O
	bool m_bIsJump;			//�W�����v�t���O

	tagPlayerState m_eState;
	tagPlayerState m_eOldState;
	tagDir m_eDir;

public:
	Player();
	~Player();

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
	//�d��
	void Gravity();

	//���쏈��
	void Control();		//���E�ړ�

	void Move();		//�ړ�
	void Jump();		//�W�����v

	//�A�j���[�V����
	void Animation();

	//�t���[��
	void CntFream();
	void ResetFream();
	void InitFream();
	void ResetSecond();

public:
	//�擾�֐�
	float GetXPos() { return m_fXPos; }		//X���W�擾
	float GetYPos() { return m_fYPos; }		//Y���W�擾

	//�X�V���X���W
	float GetNextXPos() { return m_fNextXPos; }
	//�X�V���Y���W
	float GetNextYPos() { return m_fNextYPos; }

	//�����擾
	float GetWidth() { return m_fWidth; }
	//�c���擾
	float GetHeight() { return m_fHeight; }

	//�����t���O�擾
	bool GetAlliveFlag() { return m_bIsAlive; }
	//�W�����v�t���O�擾
	bool GetJumpFlag() { return m_bIsJump; }
	//�����`�F�b�N
	void GetMoveDir(bool* _DirArray);

public:
	//�ݒ�֐�
	//X���W�̐ݒ�
	void SetXPos(float Pos) { m_fXPos = Pos; }
	//Y���W�̐ݒ�
	void SetYPos(float Pos) { m_fYPos = Pos; }

	//�X�V���X���W�̐ݒ�
	void SetNextXPos(float Pos) { m_fNextXPos = Pos; }
	//�X�V���Y���W�̐ݒ�
	void SetNextYPos(float Pos) { m_fNextYPos = Pos; }

	//�W�����v�t���O�̐ݒ�
	void SetJumpFlag(bool flag) { m_bIsJump = flag; }
};