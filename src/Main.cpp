//�E�B���h�E��\������v���O����

#include "DxLib.h"	//DX���C�u�����̃C���N���[�h
#include <math.h>

#include "Scene/SceneManager.h"
#include "Input/Input.h"
#include "VirtualButton/VirtualButton.h"

// define
#define	SCREEN_SIZE_X	1280	// X�����̉�ʃT�C�Y���w��(�f�t�H���g)
#define	SCREEN_SIZE_Y	720	// Y�����̉�ʃT�C�Y���w��(�f�t�H���g)

//�~���� DX_PI_F;

// Win32�A�v���P�[�V������ WinMain�֐� ����n�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1) {
		return -1;
	}

	// ��ʃT�C�Y��ύX
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//�`�悷��X�N���[����ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���
	
	SceneManager cScene;
	CInput::InitInput();
	CVirtualButton_Square::GetInstance()->Init();
	//-----------------------------------------

	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//�G�X�P�[�v�L�[�������ꂽ��I��
			break;
		}

		//��ʂɕ\�����ꂽ���̂�������
		ClearDrawScreen();

		//-----------------------------------------
		//��������Q�[���̖{�̂��������ƂɂȂ�
		//-----------------------------------------
		
		// �v�Z����
		CInput::StepInput();
		CVirtualButton_Square::GetInstance()->Step();
		cScene.Loop();

		// �`�揈��
		cScene.Draw();
		CVirtualButton_Square::GetInstance()->Draw();
		//-----------------------------------------
		//���[�v�̏I����
		//�t���b�v�֐�
		ScreenFlip();

	}

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���
	CVirtualButton_Square::DeleteInstance();
	
	//-----------------------------------------
	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}

