#include "MapChip.h"

void MapChip::Init(){
	memset(&handle, -1, sizeof(int));
	memset(&fileData, -1, sizeof(int));

	currentStage = STAGE_1;
	i = 0;
}

void MapChip::Load() {
	//正方形のチップ画像だけで頼む
	LoadDivGraph(CHIP_IMAGE_PATH, CHIP_IMAGE_MAX_NUM,
		sqrt(CHIP_IMAGE_MAX_NUM), sqrt(CHIP_IMAGE_MAX_NUM),
		CHIP_SIZE, CHIP_SIZE, handle);

	for (int i = 0; i < TRAP_NUM; i++) {
		trapHandle[i] = LoadGraph(TRAP_IMAGE_PATH[i]);
	}

	Read(currentStage);
}

void MapChip::Step() {
	if (input.IsKeyKeep(KEY_INPUT_G)) {
		for (int MapChipYIndex = 0; MapChipYIndex < CHIP_Y_MAX; MapChipYIndex++) {
			DrawLine(0, MapChipYIndex * 32, 1280, MapChipYIndex * 32, GetColor(255, 0, 0));
			for (int MapChipXIndex = 0; MapChipXIndex < CHIP_X_MAX; MapChipXIndex++) {
				DrawLine(MapChipXIndex * 32, 0, MapChipXIndex * 32, 720, GetColor(255, 0, 0));
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
	for (int trapIndex = 0; trapIndex < trap_vec.size(); trapIndex++) {
		switch (trap_vec[trapIndex].trap_type)
		{
		case LEFT_MOVE:
			DrawModiGraph(trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY, trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY,
				trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trapHandle[LEFT_MOVE], true);
			DrawBox(trap_vec[trapIndex].triggerX, trap_vec[trapIndex].triggerY, trap_vec[trapIndex].triggerX + trap_vec[trapIndex].triggerXSize, trap_vec[trapIndex].triggerY + trap_vec[trapIndex].triggerYSize, GetColor(255, 255, 255), false);
			break;
		case RIGHT_MOVE:
			DrawModiGraph(trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY, trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY,
				trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trapHandle[RIGHT_MOVE], true);
			DrawBox(trap_vec[trapIndex].triggerX, trap_vec[trapIndex].triggerY, trap_vec[trapIndex].triggerX + trap_vec[trapIndex].triggerXSize, trap_vec[trapIndex].triggerY + trap_vec[trapIndex].triggerYSize, GetColor(255, 255, 255), false);
			break;
		case UP_MOVE:
			DrawModiGraph(trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY, trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY,
				trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trapHandle[UP_MOVE], true);
			DrawBox(trap_vec[trapIndex].triggerX, trap_vec[trapIndex].triggerY, trap_vec[trapIndex].triggerX + trap_vec[trapIndex].triggerXSize, trap_vec[trapIndex].triggerY + trap_vec[trapIndex].triggerYSize, GetColor(255, 255, 255), false);
			break;
		case DOWN_MOVE:
			DrawModiGraph(trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY, trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY,
				trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trapHandle[DOWN_MOVE], true);
			DrawBox(trap_vec[trapIndex].triggerX, trap_vec[trapIndex].triggerY, trap_vec[trapIndex].triggerX + trap_vec[trapIndex].triggerXSize, trap_vec[trapIndex].triggerY + trap_vec[trapIndex].triggerYSize, GetColor(255, 255, 255), false);
			break;
		case PITFALL:
			DrawBox(trap_vec[trapIndex].triggerX, trap_vec[trapIndex].triggerY, trap_vec[trapIndex].triggerX + trap_vec[trapIndex].triggerXSize, trap_vec[trapIndex].triggerY + trap_vec[trapIndex].triggerYSize, GetColor(255, 0, 0), false);
			break;
		case TRAP_NUM:
			break;
		default:
			break;
		}
	}

}

void MapChip::Fin(){

}

void MapChip::Read(int stageId){
	FILE* fp;

	fopen_s(&fp, CsvFilePath[stageId], "r");

	int mapIndexX = 0;
	int mapIndexY = 0;

	while (true) {
		// 数値部分を読み込む
		fscanf_s(fp, "%d", &fileData[mapIndexY][mapIndexX]);
		mapIndexX++;

		// 「,」を飛ばすために読み込みを実行
		char chara = fgetc(fp);

		// EOFの場合は読み込み終了
		if (chara == EOF) {
			break;
		}

		// 改行コードの場合は保存先を変更する
		if (chara == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
	}

	fclose(fp);
}

void MapChip::CreateTrap(TRAP_TYPE type, int trigger_x, int trigger_y, int triggerSizeX, int triggerSizeY, int trap_x, int trap_y, int sizeX, int sizeY){
	TrapData traps;

	traps.isTrigger = false;		//トラップ発生

	//座標代入コーナー
	traps.triggerX = trigger_x;
	traps.triggerY = trigger_y;
	traps.triggerXSize = triggerSizeX;
	traps.triggerYSize = triggerSizeY;
	traps.trapNextX = traps.trapX = trap_x;
	traps.trapNextY = traps.trapY = trap_y;
	traps.trapSizeX = sizeX;
	traps.trapSizeY = sizeY;

	//トラップの種類設定
	traps.trap_type = type;

	//ベクターに挿入
	trap_vec.push_back(traps);
}

void MapChip::CreatePITFALL(int trigger_x, int trigger_y, int triggerSizeX, int triggerSizeY, int pStepX, int pStepY, int stepX, int stepY){
	TrapData traps;

	traps.isTrigger = false;		//トラップ発生

	//座標代入コーナー
	traps.triggerX = trigger_x;
	traps.triggerY = trigger_y;
	traps.triggerXSize = triggerSizeX;
	traps.triggerYSize = triggerSizeY;
	traps.preStepsAheadX = pStepX;
	traps.preStepsAheadY = pStepY;
	traps.stepsAheadX = stepX;
	traps.stepsAheadY = stepY;

	//トラップの種類設定
	traps.trap_type = PITFALL;

	//ベクターに挿入
	trap_vec.push_back(traps);
}

void MapChip::UpDate() {
	for (int trapIndex = 0; trapIndex < trap_vec.size(); trapIndex++) {
		if (trap_vec[trapIndex].trap_type == PITFALL)continue;
		trap_vec[trapIndex].trapX = trap_vec[trapIndex].trapNextX;
		trap_vec[trapIndex].trapY = trap_vec[trapIndex].trapNextY;
	}
}