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
	for (int trapNum = 0; trapNum < trap_vec.size();trapNum++) {
		//�g���K�[(��)
		DrawBox(trap_vec[trapNum].triggerX, trap_vec[trapNum].triggerY, trap_vec[trapNum].triggerX + CHIP_SIZE, trap_vec[trapNum].triggerY + CHIP_SIZE, BLUE, true);
		//�g���b�v(��)
		DrawBox(trap_vec[trapNum].trapX, trap_vec[trapNum].trapY, trap_vec[trapNum].trapX + CHIP_SIZE, trap_vec[trapNum].trapY + CHIP_SIZE, RED, true);
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

void MapChip::CreateTrap(int trigger_x,int trigger_y,int trap_x,int trap_y, TRAP_TYPE type){
	TrapData traps;

	traps.isTrigger = false;		//�g���b�v����

	//���W����R�[�i�[
	traps.triggerX = trigger_x;
	traps.triggerY = trigger_y;
	traps.trapX = trap_x;
	traps.trapY = trap_y;

	//�g���b�v�̎�ސݒ�
	traps.trap_type = type;

	//�x�N�^�[�ɑ}��
	trap_vec.push_back(traps);
}