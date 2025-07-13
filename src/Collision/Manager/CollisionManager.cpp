#include "CollisionManager.h"

void CollisonManager::Init(){
	goal = false;
}

void CollisonManager::PlayerToMap(Player& player, MapChip& map) {

	//�v���C���[�ƃ}�b�v�̓����蔻��
	for (int mapIndexY = 0; mapIndexY < CHIP_Y_MAX; mapIndexY++) {
		for (int mapIndexX = 0; mapIndexX < CHIP_X_MAX; mapIndexX++) {
			if (map.GetFileData(mapIndexY, mapIndexX) == -1 || map.GetFileData(mapIndexY, mapIndexX) == 3 || map.GetFileData(mapIndexY, mapIndexX) == 2)continue;
			bool dir[4] = { false };
			player.GetMoveDir(dir);

			int mapX = mapIndexX * CHIP_SIZE;
			int mapY = mapIndexY * CHIP_SIZE;

			if (IsHitRect(player.GetXPos(), player.GetNextYPos(), player.GetWidth(), player.GetHeight(), mapX, mapY, CHIP_SIZE, CHIP_SIZE)) {
				if (dir[0]) {
					float over = mapY + CHIP_SIZE - player.GetNextYPos();
					player.SetNextYPos((float)(player.GetNextYPos() + over));
				}
				if (dir[1]) {
					float overlap = player.GetNextYPos() + player.GetHeight() - mapY;
					player.SetNextYPos((float)(player.GetNextYPos() - overlap));
					player.SetJumpFlag(false);
				}
			}
		}
	}
	for (int mapIndexY = 0; mapIndexY < CHIP_Y_MAX; mapIndexY++) {
		for (int mapIndexX = 0; mapIndexX < CHIP_X_MAX; mapIndexX++) {
			if (map.GetFileData(mapIndexY, mapIndexX) == -1 || map.GetFileData(mapIndexY, mapIndexX) == 3 || map.GetFileData(mapIndexY, mapIndexX) == 2)continue;
			bool dir[4] = { false };
			player.GetMoveDir(dir);

			int mapX = mapIndexX * CHIP_SIZE;
			int mapY = mapIndexY * CHIP_SIZE;

			if (IsHitRect(player.GetNextXPos(), player.GetNextYPos(), player.GetWidth(), player.GetHeight(), mapX, mapY, CHIP_SIZE, CHIP_SIZE)) {
				if (dir[2]) {
					float over = mapX + CHIP_SIZE - player.GetNextXPos();
					player.SetNextXPos((float)(player.GetNextXPos() + over));
				}
				if (dir[3]) {
					float over = player.GetNextXPos() + player.GetWidth() - mapX;
					player.SetNextXPos((float)(player.GetNextXPos() - over));
				}
			}
		}
	}

	//�Ƃ��̏���
	for (int mapIndexY = 0; mapIndexY < CHIP_Y_MAX; mapIndexY++) {
		for (int mapIndexX = 0; mapIndexX < CHIP_X_MAX; mapIndexX++) {
			int mapX = mapIndexX * CHIP_SIZE;
			int mapY = mapIndexY * CHIP_SIZE;
			if (map.GetFileData(mapIndexY, mapIndexX) == 2) {
				if (IsHitRect(player.GetNextXPos(), player.GetNextYPos(), player.GetWidth(), player.GetHeight(), mapX, mapY, CHIP_SIZE, CHIP_SIZE)) {
					player.SetAliveFlg(false);
				}
			}
		}
	}
	//�S�[���̏���
	for (int mapIndexY = 0; mapIndexY < CHIP_Y_MAX; mapIndexY++) {
		for (int mapIndexX = 0; mapIndexX < CHIP_X_MAX; mapIndexX++) {
			int mapX = mapIndexX * CHIP_SIZE;
			int mapY = mapIndexY * CHIP_SIZE;
			if (map.GetFileData(mapIndexY, mapIndexX) == 3) {
				if (IsHitRect(player.GetNextXPos(), player.GetNextYPos(), player.GetWidth(), player.GetHeight(), mapX, mapY, CHIP_SIZE, CHIP_SIZE)) {
					goal = true;
				}
			}
		}
	}

	//������====================================================================================================================================================================================================================
	
	//�ǂ������Ă���ꍇ
	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		MapChip::TrapData maps = map.GetTrap(trapIndex);
		//���Ƃ����͊֌W�Ȃ�
		if (maps.trap_type == PITFALL)continue;

		bool dir[4] = { false };
		maps.GetMoveDir(dir);

		bool pdir[4] = { false };
		player.GetMoveDir(pdir);

		if (IsHitRect(player.GetXPos(), player.GetNextYPos(), player.GetWidth(), player.GetHeight(), maps.trapX, maps.trapY, maps.trapSizeX, maps.trapSizeY)) {
			if (dir[0]) { // �u���b�N����ɓ����Ă���
				float overlap = player.GetNextYPos() + player.GetHeight() - maps.trapNextY;
				player.SetNextYPos(player.GetNextYPos() - overlap);
				player.SetJumpFlag(false);
			}
			else if (dir[1]) { // ��
				float overlap = maps.trapNextY + maps.trapSizeY - player.GetNextYPos();
				player.SetNextYPos(player.GetNextYPos() + overlap);
			}

			//�u���b�N�����ĂȂ����
			if (dir[0] || dir[1])break;
			if (pdir[1]) {
				float overlap = player.GetNextYPos() + player.GetHeight() - maps.trapY;
				player.SetNextYPos((float)(player.GetNextYPos() - overlap));
				player.SetJumpFlag(false);

				//�������Ƀu���b�N�������Ă����
				if (dir[2]) {
					player.SetNextXPos(player.GetNextXPos() - map.GetTrap(trapIndex).Spd);
				}
				//�����E�Ƀu���b�N�������Ă����
				if (dir[3]) {
					player.SetNextXPos(player.GetNextXPos() + map.GetTrap(trapIndex).Spd);
				}

			}
			if (dir[0] || dir[1] || dir[2] || dir[3])break;
			if (pdir[0]) {
				float over = maps.trapY + maps.trapSizeY - player.GetNextYPos();
				player.SetNextYPos((float)(player.GetNextYPos() + over));
			}
			
		}
	}
	//�ǂ������Ă���ꍇ
	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		MapChip::TrapData maps = map.GetTrap(trapIndex);
		//���Ƃ����͊֌W�Ȃ�
		if (maps.trap_type == PITFALL)continue;

		bool dir[4] = { false };
		maps.GetMoveDir(dir);

		bool pdir[4] = { false };
		player.GetMoveDir(pdir);

		if (IsHitRect(player.GetNextXPos(), player.GetNextYPos(), player.GetWidth(), player.GetHeight(), maps.trapX, maps.trapY, maps.trapSizeX, maps.trapSizeY)) {
			if (dir[2]) { //���ɓ����Ă���
				float overlap = player.GetNextXPos() + player.GetWidth() - maps.trapNextX;
				player.SetNextXPos(player.GetNextXPos() - overlap);
			}
			else if (dir[3]) { // �E
				float overlap = maps.trapNextX + maps.trapSizeX - player.GetNextXPos();
				player.SetNextXPos(player.GetNextXPos() + overlap);
			}

			if (pdir[2]) {
				float over = maps.trapX + maps.trapSizeX - player.GetNextXPos();
				player.SetNextXPos((float)(player.GetNextXPos() + over));
			}
			if (pdir[3]) {
				float over = player.GetNextXPos() + player.GetWidth() - maps.trapX;
				player.SetNextXPos((float)(player.GetNextXPos() - over));
			}
		}
	}

	//���W�X�V
	map.UpDate();
	//=========================================================================================================================================================================================================================


	//�g���K�[=================================================================================================
	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		//�g���K�[�Ƃ̓����蔻��
		if (IsHitRect(player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight(), map.GetTrap(trapIndex).triggerX, map.GetTrap(trapIndex).triggerY, map.GetTrap(trapIndex).triggerXSize, map.GetTrap(trapIndex).triggerYSize)) {
			map.GetTrap(trapIndex).isTrigger = true;
		}
		//�N��������
		if (map.GetTrap(trapIndex).isTrigger) {
			//�g���b�v�̋N������
			switch (map.GetTrap(trapIndex).trap_type)
			{
			case LEFT_MOVE:
				if (map.GetTrap(trapIndex).finX < map.GetTrap(trapIndex).trapX) {
					map.GetTrap(trapIndex).MoveTrapX(-map.GetTrap(trapIndex).Spd);
				}
				break;
			case RIGHT_MOVE:
				if (map.GetTrap(trapIndex).finX > map.GetTrap(trapIndex).trapX) {
					map.GetTrap(trapIndex).MoveTrapX(map.GetTrap(trapIndex).Spd);
				}
				break;
			case UP_MOVE:
				if (map.GetTrap(trapIndex).finY < map.GetTrap(trapIndex).trapY) {
					map.GetTrap(trapIndex).MoveTrapY(-map.GetTrap(trapIndex).Spd);
				}
				break;
			case DOWN_MOVE:
				if (map.GetTrap(trapIndex).finX > map.GetTrap(trapIndex).trapX) {
					map.GetTrap(trapIndex).MoveTrapY(map.GetTrap(trapIndex).Spd);
				}
				break;
			case PITFALL:
				for (int y = map.GetTrap(trapIndex).preStepsAheadY; y < map.GetTrap(trapIndex).stepsAheadY; y++) {
					for (int x = map.GetTrap(trapIndex).preStepsAheadX; x < map.GetTrap(trapIndex).stepsAheadX; x++) {
						map.SetFileData(y, x, -1);
					}
				}
				break;
			case TRAP_NUM:
				break;
			default:
				break;
			}
		}
	}
}

void CollisonManager::PlayerToAORI(Player& player, AORIManager& aori){
	for (int i = 0; i < PATURN; i++) {

		if (IsHitRect(player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight(), aori.GetAORI(i).GetPosX(), aori.GetAORI(i).GetPosY(), std::string(aori.GetAORI(i).Comment[i]).size(), 16)) {
			player.SetAliveFlg(false);
		}

		DrawBox(aori.GetAORI(i).GetPosX(), aori.GetAORI(i).GetPosY(), aori.GetAORI(i).GetPosX() + std::string(aori.GetAORI(i).Comment[i]).size(), aori.GetAORI(i).GetPosY() + 16, GetColor(255, 255, 255), false);
	}
}