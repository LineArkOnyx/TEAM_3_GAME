#include "MapChip.h"

void MapChip::Init(){
	memset(&handle, -1, sizeof(int));
	memset(&fileData, -1, sizeof(int));

	i = 0;
}

void MapChip::Load() {
	//正方形のチップ画像だけで頼む
	LoadDivGraph(CHIP_IMAGE_PATH, CHIP_IMAGE_MAX_NUM,
		sqrt(CHIP_IMAGE_MAX_NUM), sqrt(CHIP_IMAGE_MAX_NUM),
		CHIP_SIZE, CHIP_SIZE, handle);
}

void MapChip::Step() {

	//仮
	if (input.IsKeyPush(KEY_INPUT_UP)) {
		trap_vec[i].isTrigger = true;
		i++;
	}

	//トラップ挙動
	for (int trapNum = 0; trapNum < trap_vec.size(); trapNum++) {
		if (trap_vec[trapNum].isTrigger) {
			switch (trap_vec[trapNum].trap_type)
			{
			case LEFT_MOVE:
				trap_vec[trapNum].trapX--;
				break;
			case RIGHT_MOVE:
				trap_vec[trapNum].trapX++;
				break;
			case TRAP_NUM:
				break;
			default:
				break;
			}
		}
	}
}

void MapChip::Draw() {
	//マップチップの描画
	for (int MapChipYIndex = 0; MapChipYIndex < CHIP_Y_MAX; MapChipYIndex++) {
		for (int MapChipXIndex = 0; MapChipXIndex < CHIP_X_MAX; MapChipXIndex++) {
			int mapChipType = fileData[MapChipYIndex][MapChipXIndex];
			DrawGraph(CHIP_SIZE * MapChipXIndex, CHIP_SIZE * MapChipYIndex,handle[mapChipType], false);
		}
	}

	//トラップの描画
	for (int trapNum = 0; trapNum < trap_vec.size();trapNum++) {
		//トリガー(青)
		DrawBox(trap_vec[trapNum].triggerX, trap_vec[trapNum].triggerY, trap_vec[trapNum].triggerX + CHIP_SIZE, trap_vec[trapNum].triggerY + CHIP_SIZE, BLUE, true);
		//トラップ(赤)
		DrawBox(trap_vec[trapNum].trapX, trap_vec[trapNum].trapY, trap_vec[trapNum].trapX + CHIP_SIZE, trap_vec[trapNum].trapY + CHIP_SIZE, RED, true);
	}

}

void MapChip::Fin(){

}

void MapChip::CreateTrap(int trigger_x,int trigger_y,int trap_x,int trap_y, TRAP_TYPE type){
	TrapData traps;

	traps.isTrigger = false;		//トラップ発生

	//座標代入コーナー
	traps.triggerX = trigger_x;
	traps.triggerY = trigger_y;
	traps.trapX = trap_x;
	traps.trapY = trap_y;

	//トラップの種類設定
	traps.trap_type = type;

	//ベクターに挿入
	trap_vec.push_back(traps);
}