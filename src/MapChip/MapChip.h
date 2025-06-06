#pragma once
#include "DxLib.h"
#include "vector"
#include "cmath"

#include "../Input/Input.h"

using namespace std;

//�J���[�R�[�h
const int RED   = GetColor(255, 0, 0);
const int GREEN = GetColor(0, 255, 0);
const int BLUE  = GetColor(0, 0, 255);

constexpr int CHIP_IMAGE_MAX_NUM  = 9;
constexpr int CHIP_X_MAX = 25;
constexpr int CHIP_Y_MAX = 25;
constexpr int CHIP_SIZE  = 32;

const char CHIP_IMAGE_PATH[256] = {
	""
};

enum TRAP_TYPE {
	LEFT_MOVE,
	RIGHT_MOVE,
	
	TRAP_NUM,
};

class MapChip {
public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Fin();

	//�g���b�v����(�g���K�[���W,�g���b�v���W,�ǂ̃g���b�v��)
	void CreateTrap(int trigger_x, int trigger_y, int trap_x, int trap_y, TRAP_TYPE type);

private:
	//���̓N���X
	CInput input;

	//�g���b�v���
	struct TrapData {
		bool isTrigger = false;	//�g���b�v�����t���O
		int triggerX, triggerY;	//���������W
		int trapX, trapY;		//�g���b�v���W

		//�g���b�v���
		TRAP_TYPE trap_type;
	};

	//�g���b�v���x�N�^�[
	vector<TrapData> trap_vec;

	//�����p�n���h��
	int handle[CHIP_IMAGE_MAX_NUM];

	//�O���t�@�C���Ł[���i�[�p
	int fileData[CHIP_Y_MAX][CHIP_X_MAX];

protected:

public:

	int i;

};