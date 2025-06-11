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
constexpr int CHIP_X_MAX = 40;
constexpr int CHIP_Y_MAX = 23;
constexpr int CHIP_SIZE  = 32;

enum TRAP_TYPE {
	LEFT_MOVE,
	RIGHT_MOVE,
	UP_MOVE,
	DOWN_MOVE,

	TRAP_NUM,
};

enum STAGE_TYPE {
	STAGE_1,
	STAGE_2,

	STAGE_NUM,
};

const char CHIP_IMAGE_PATH[256] = {
	"data/Map/map.png"
};

//csv�t�@�C���p�X
const char CsvFilePath[STAGE_NUM][256] = {
	"data/Map/Map001.csv",
	"data/Map/Map002.csv",
};

class MapChip {
public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Fin();

	//�X�e�[�W�̓ǂݍ���
	void Read(int stageId);

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

		void SetIsTrgger(bool is) { isTrigger = is; }
		void SetTriX(int x) { triggerX = x; }
		void SetTriY(int y) { triggerY = y; }
		void SetTrapX(int x) { trapX = x; }
		void SetTrapY(int y) { trapY = y; }

		void MoveTriX(int x) { triggerX += x; }
		void MoveTriY(int y) { triggerY += y; }
		void MoveTrapX(int x) { trapX += x; }
		void MoveTrapY(int y) { trapY += y; }

		void SetTrapType(TRAP_TYPE type) { trap_type = type; }
	};

	//�g���b�v���x�N�^�[
	vector<TrapData> trap_vec;

	//�����p�n���h��
	int handle[CHIP_IMAGE_MAX_NUM];

	//�O���t�@�C���Ł[���i�[�p
	int fileData[CHIP_Y_MAX][CHIP_X_MAX];

	//�N���A�t���O
	bool stageClear;

	//���݂̃X�e�[�W��
	int currentStage;

protected:

public:

	int i;

	void SetStageClear(bool is) { stageClear = is; }
	bool GetStageClear() { return stageClear; }
	void SetCurrentStage(int is) { currentStage = is; }
	bool GetCurrentStage() { return currentStage; }

	TrapData& GetTrap(int id) { return trap_vec[id]; }
	vector<TrapData> GetTrapVec() { return trap_vec; }

};