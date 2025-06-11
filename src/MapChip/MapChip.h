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

	//トラップ生成(トリガー座標,トラップ座標,どのトラップか)
	void CreateTrap(int trigger_x, int trigger_y, int trap_x, int trap_y, TRAP_TYPE type);

private:
	//入力クラス
	CInput input;

	//トラップ情報
	struct TrapData {
		bool isTrigger = false;	//トラップ発動フラグ
		int triggerX, triggerY;	//発生源座標
		int trapX, trapY;		//トラップ座標

		//トラップ種類
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
	bool GetStageClear() { return stageClear; }
	void SetCurrentStage(int is) { currentStage = is; }
	bool GetCurrentStage() { return currentStage; }

	TrapData& GetTrap(int id) { return trap_vec[id]; }
	vector<TrapData> GetTrapVec() { return trap_vec; }

};