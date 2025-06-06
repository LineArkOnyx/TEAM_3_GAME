#pragma once

#include <math.h>
#include <vector>
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Input/Input.h"

using namespace std;

class CVirtualButton_Square {
private:

	static CVirtualButton_Square* m_Instance;//�C���X�^���X

	struct ButtonData {

		bool m_CurrentStance;		//�O�t���[���̉�����Ă��邩���Ȃ���
		bool m_NextStance;			//���t���[���̉�����Ă��邩���Ȃ���

		float m_fPos_X;		
		float m_fPos_Y;
		float m_fSize_W;	
		float m_fSize_H;

		int m_ButtonColor_R;		//�{�^���̐Ԃ�
		int m_ButtonColor_G;		//�{�^���̗΂�
		int m_ButtonColor_B;		//�{�^���̐�

		int ActiveID;			//ID
	};
	
	vector<ButtonData> vList_ButtonData;//�{�^���̃��X�g

public:
	//�C���X�^���X�擾
	static CVirtualButton_Square* GetInstance();
	//�C���X�^���X�j��
	static void DeleteInstance();

	void Init();//�������p
	void Step();//�X�V�Ȃǂ��s��
	void Exit();//�O�̂��߂̔j���p
	void Draw();//�{�^���`��

	int RequestVirtualButton(float Pos_X, float Pos_Y, float Size_W, float Size_H, int _R,int _G,int _B);//�{�^���̃��N�G�X�g

	//�������ꂽ
	bool IsKeyPush(int _ID);
	//����������
	bool IsKeyKeep(int _ID);
	//�������Ƃ�
	bool IsKeyRelease(int _ID);
	//�P���ɉ�����Ă邩�ۂ�
	bool IsKeyDown(int _ID);
};