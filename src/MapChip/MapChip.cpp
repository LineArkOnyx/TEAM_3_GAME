#include "MapChip.h"

void MapChip::Init(){
	memset(&handle, -1, sizeof(int));
	memset(&fileData, -1, sizeof(int));

	currentStage = STAGE_1;
	i = 0;
}

void MapChip::Load() {
	//�����`�̃`�b�v�摜�����ŗ���
	LoadDivGraph(CHIP_IMAGE_PATH, CHIP_IMAGE_MAX_NUM,
		sqrt(CHIP_IMAGE_MAX_NUM), sqrt(CHIP_IMAGE_MAX_NUM),
		CHIP_SIZE, CHIP_SIZE, handle);

	for (int i = 0; i < TRAP_NUM; i++) {
		trapHandle[i] = LoadGraph(TRAP_IMAGE_PATH[i]);
	}

	Read(currentStage);
}

void MapChip::Step() {

	//��
	if (input.IsKeyPush(KEY_INPUT_UP)) {
		trap_vec[i].isTrigger = true;
		i++;
	}
}

void MapChip::Draw() {
	//�}�b�v�`�b�v�̕`��
	for (int MapChipYIndex = 0; MapChipYIndex < CHIP_Y_MAX; MapChipYIndex++) {
		for (int MapChipXIndex = 0; MapChipXIndex < CHIP_X_MAX; MapChipXIndex++) {
			int mapChipType = fileData[MapChipYIndex][MapChipXIndex];
			DrawGraph(CHIP_SIZE * MapChipXIndex, CHIP_SIZE * MapChipYIndex,handle[mapChipType], false);
		}
	}

	//�g���b�v�̕`��
	for (int trapIndex = 0; trapIndex < trap_vec.size(); trapIndex++) {
		switch (trap_vec[trapIndex].trap_type)
		{
		case LEFT_MOVE:
			DrawModiGraph(trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY, trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY,
				trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trapHandle[LEFT_MOVE], true);
			break;
		case RIGHT_MOVE:
			DrawModiGraph(trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY, trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY,
				trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trapHandle[RIGHT_MOVE], true);
			break;
		case UP_MOVE:
			DrawModiGraph(trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY, trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY,
				trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trapHandle[UP_MOVE], true);
			break;
		case DOWN_MOVE:
			DrawModiGraph(trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY, trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY,
				trap_vec[trapIndex].trapX + trap_vec[trapIndex].trapSizeX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trap_vec[trapIndex].trapX, trap_vec[trapIndex].trapY + trap_vec[trapIndex].trapSizeY, trapHandle[DOWN_MOVE], true);
			break;
		case PITFALL:

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
		// ���l������ǂݍ���
		fscanf_s(fp, "%d", &fileData[mapIndexY][mapIndexX]);
		mapIndexX++;

		// �u,�v���΂����߂ɓǂݍ��݂����s
		char chara = fgetc(fp);

		// EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (chara == EOF) {
			break;
		}

		// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
		if (chara == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
	}

	fclose(fp);
}

void MapChip::CreateTrap(TRAP_TYPE type, int trigger_x, int trigger_y, int trap_x, int trap_y, int sizeX, int sizeY){
	TrapData traps;

	traps.isTrigger = false;		//�g���b�v����

	//���W����R�[�i�[
	traps.triggerX = trigger_x;
	traps.triggerY = trigger_y;
	traps.trapX = trap_x;
	traps.trapY = trap_y;
	traps.trapSizeX = sizeX;
	traps.trapSizeY = sizeY;

	//�g���b�v�̎�ސݒ�
	traps.trap_type = type;

	//�x�N�^�[�ɑ}��
	trap_vec.push_back(traps);
}

void MapChip::CreatePITFALL(int trigger_x, int trigger_y, int pStepX, int pStepY, int stepX, int stepY){
	TrapData traps;

	traps.isTrigger = false;		//�g���b�v����

	//���W����R�[�i�[
	traps.triggerX = trigger_x;
	traps.triggerY = trigger_y;
	traps.preStepsAheadX = pStepX;
	traps.preStepsAheadY = pStepY;
	traps.stepsAheadX = stepX;
	traps.stepsAheadY = stepY;

	//�g���b�v�̎�ސݒ�
	traps.trap_type = PITFALL;

	//�x�N�^�[�ɑ}��
	trap_vec.push_back(traps);
}