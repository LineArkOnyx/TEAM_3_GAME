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
	};

	//トラップ情報ベクター
	vector<TrapData> trap_vec;

	//分割用ハンドル
	int handle[CHIP_IMAGE_MAX_NUM];

	//外部ファイルでーた格納用
	int fileData[CHIP_Y_MAX][CHIP_X_MAX];

protected:

public:

	int i;

};