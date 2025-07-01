#pragma once
#include "DxLib.h"
#include "vector"
#include "cmath"

#include "../Input/Input.h"

using namespace std;

//カラーコード
const int RED   = GetColor(255, 0, 0);
const int GREEN = GetColor(0, 255, 0);
const int BLUE  = GetColor(0, 0, 255);

constexpr int CHIP_IMAGE_MAX_NUM  = 9;
constexpr int CHIP_X_MAX = 40;
constexpr int CHIP_Y_MAX = 23;
constexpr int CHIP_SIZE  = 32;

enum TRAP_TYPE {
	LEFT_MOVE,		 //左に動くだけトラップ
	RIGHT_MOVE,		 //右に動くだけトラップ
	UP_MOVE,		 //上に動くだけトラップ
	DOWN_MOVE,		 //下に動くだけトラップ
	LEFT_MOVE_SPINY, //左に動くとげ
	RIGHT_MOVE_SPINY,//右に動くとげ

	PITFALL,		//落とし穴

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

//csvファイルパス
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

	//ステージの読み込み
	void Read(int stageId);

	//トラップ生成(トリガー座標,トラップ座標,チップ範囲,どのトラップか)
	void CreateTrap(TRAP_TYPE type, int trigger_x, int trigger_y, int triggerSizeX, int triggerSizeY, int trap_x, int trap_y, int sizeX, int sizeY, int spd);
	void CreatePITFALL(int trigger_x, int trigger_y, int triggerSizeX, int triggerSizeY, int pStepX = 1, int pStepY = 1, int stepX = 1, int stepY = 1);

	//トラップ情報
	struct TrapData {
		bool isTrigger = false;				//トラップ発動フラグ
		int triggerX, triggerY;				//発生源座標
		int triggerXSize, triggerYSize;		//発生源座標
		int trapX, trapY;					//トラップ座標
		int trapNextX, trapNextY;			//トラップ座標
		int trapSizeX, trapSizeY;			//トラップサイズ
		int preStepsAheadX, preStepsAheadY;	//どの範囲のチップを変化させるか
		int stepsAheadX, stepsAheadY;		//どの範囲のチップを変化させるか
		int Spd;

		//トラップ種類
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
			//右方向のチェック(進んでいる)
			if (trapNextX > trapX) {
				_DirArray[3] = true;
			}
			//左方向チェック　
			if (trapNextX < trapX) {
				_DirArray[2] = true;
			}
			//下方向チェック
			if (trapNextY > trapY) {
				_DirArray[1] = true;
			}
			//上方向チェック
			if (trapNextY < trapY) {
				_DirArray[0] = true;
			}
		}
	};

private:
	//入力クラス
	CInput input;

	int trapHandle[TRAP_NUM];

	//トラップ情報ベクター
	vector<TrapData> trap_vec;

	//分割用ハンドル
	int handle[CHIP_IMAGE_MAX_NUM];

	//外部ファイルでーた格納用
	int fileData[CHIP_Y_MAX][CHIP_X_MAX];

	//クリアフラグ
	bool stageClear;

	//現在のステージ数
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