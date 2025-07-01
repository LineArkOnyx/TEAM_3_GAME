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
	LEFT_MOVE,		 //���ɓ��������g���b�v
	RIGHT_MOVE,		 //�E�ɓ��������g���b�v
	UP_MOVE,		 //��ɓ��������g���b�v
	DOWN_MOVE,		 //���ɓ��������g���b�v
	LEFT_MOVE_SPINY, //���ɓ����Ƃ�
	RIGHT_MOVE_SPINY,//�E�ɓ����Ƃ�

	PITFALL,		//���Ƃ���

	TRAP_NUM,
};

enum STAGE_TYPE {
	STAGE_1,
	STAGE_2,

	STAGE_NUM,
};

const char TRAP_IMAGE_PATH[TRAP_NUM][256] = {
	"data/Map/map.png",
	"data/Map/map.png",
	"data/Map/map.png",
	"data/Map/map.png",
	"data/Map/map.png",
	"data/Map/map.png",
	"data/Map/map.png",
};

const char CHIP_IMAGE_PATH[256] = {
	"data/Map/MapChip.png"
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

	//�g���b�v����(�g���K�[���W,�g���b�v���W,�`�b�v�͈�,�ǂ̃g���b�v��)
	void CreateTrap(TRAP_TYPE type, int trigger_x, int trigger_y, int triggerSizeX, int triggerSizeY, int trap_x, int trap_y, int sizeX, int sizeY, int spd);
	void CreatePITFALL(int trigger_x, int trigger_y, int triggerSizeX, int triggerSizeY, int pStepX = 1, int pStepY = 1, int stepX = 1, int stepY = 1);

	//�g���b�v���
	struct TrapData {
		bool isTrigger = false;				//�g���b�v�����t���O
		int triggerX, triggerY;				//���������W
		int triggerXSize, triggerYSize;		//���������W
		int trapX, trapY;					//�g���b�v���W
		int trapNextX, trapNextY;			//�g���b�v���W
		int trapSizeX, trapSizeY;			//�g���b�v�T�C�Y
		int preStepsAheadX, preStepsAheadY;	//�ǂ͈̔͂̃`�b�v��ω������邩
		int stepsAheadX, stepsAheadY;		//�ǂ͈̔͂̃`�b�v��ω������邩
		int Spd;

		//�g���b�v���
		TRAP_TYPE trap_type;

		void SetIsTrgger(bool is) { isTrigger = is; }
		void SetTriX(int x) { triggerX = x; }
		void SetTriY(int y) { triggerY = y; }
		void SetTrapX(int x) { trapX = x; }
		void SetTrapY(int y) { trapY = y; }

		void MoveTriX(int x) { triggerX += x; }
		void MoveTriY(int y) { triggerY += y; }
		void MoveTrapX(int x) { trapNextX += x; }
		void MoveTrapY(int y) { trapNextY += y; }

		void SetTrapType(TRAP_TYPE type) { trap_type = type; }

		void GetMoveDir(bool* _DirArray)
		{
			//�E�����̃`�F�b�N(�i��ł���)
			if (trapNextX > trapX) {
				_DirArray[3] = true;
			}
			//�������`�F�b�N�@
			if (trapNextX < trapX) {
				_DirArray[2] = true;
			}
			//�������`�F�b�N
			if (trapNextY > trapY) {
				_DirArray[1] = true;
			}
			//������`�F�b�N
			if (trapNextY < trapY) {
				_DirArray[0] = true;
			}
		}
	};

private:
	//���̓N���X
	CInput input;

	int trapHandle[TRAP_NUM];

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
	void SetFileData(int y, int x, int data) { fileData[y][x] = data; }

	bool GetStageClear() { return stageClear; }
	void SetCurrentStage(int is) { currentStage = is; }
	bool GetCurrentStage() { return currentStage; }
	int GetFileData(int y, int x) { return fileData[y][x]; }

	void UpDate();

	TrapData& GetTrap(int id) { return trap_vec[id]; }
	vector<TrapData> GetTrapVec() { return trap_vec; }

};