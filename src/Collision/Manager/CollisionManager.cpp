#include "CollisionManager.h"

bool IsPlayerOnBlock(Player& player, MapChip& block) {
	for (int trapIndex = 0; trapIndex < block.GetTrapVec().size(); trapIndex++) {
		MapChip::TrapData maps = block.GetTrap(trapIndex);
		if (maps.trap_type == PITFALL)continue;
		// �v���C���[�̑���Y�ƃu���b�N�̏��Y����v���Ă���
		float playerBottom = player.GetYPos() + player.GetHeight();
		float blockTop = maps.trapY;

		// Y�̌덷���������i�}���s�N�Z���j������Ă�Ƃ݂Ȃ�
		const float tolerance = 4.0f;

		bool verticalMatch = fabs(playerBottom - blockTop) < tolerance;

		// �������ɓ������Ă���i�͈͂��d�Ȃ��Ă���j
		bool horizontalOverlap =
			player.GetXPos() + player.GetWidth() > maps.trapSizeX + 2 &&
			player.GetXPos() < maps.trapX + maps.trapSizeX + 2;

		return verticalMatch && horizontalOverlap;
	}
}

void CollisonManager::PlayerToMap(Player& player, MapChip& map) {

	//�v���C���[�ƃ}�b�v�̓����蔻��
	for (int mapIndexY = 0; mapIndexY < CHIP_Y_MAX; mapIndexY++) {
		for (int mapIndexX = 0; mapIndexX < CHIP_X_MAX; mapIndexX++) {
			if (map.GetFileData(mapIndexY, mapIndexX) == -1)continue;
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
			if (map.GetFileData(mapIndexY, mapIndexX) == -1)continue;
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

	//�ǂƂ̓����蔻��
	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		MapChip::TrapData maps = map.GetTrap(trapIndex);
		if (maps.trap_type == PITFALL)continue;
		bool dir[4] = { false };
		maps.GetMoveDir(dir);
		if (IsHitRect(player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight(), maps.trapX, maps.trapY, maps.trapSizeX, maps.trapSizeY)) {
			if (dir[0]) { // �u���b�N����ɓ����Ă���
				float overlap = player.GetNextYPos() + player.GetHeight() - maps.trapNextY;
				player.SetNextYPos(player.GetNextYPos() - overlap);
				player.SetJumpFlag(false);
				/*player.SetYSpeed(0.0f);*/
			}
			else if (dir[1]) { // ��
				float overlap = maps.trapNextY + maps.trapSizeY - player.GetNextYPos();
				player.SetNextYPos(player.GetNextYPos() + overlap);
			}
		}
		//if (IsPlayerOnBlock(player, map)) {
		//	bool dir[4] = { false };
		//	maps.GetMoveDir(dir);
		//	if (dir[2]) { // ���ɓ����Ă�
		//		player.SetXPos(player.GetXPos());
		//	}
		//	else if (dir[3]) { // �E�ɓ����Ă�
		//		player.SetXPos(player.GetXPos());
		//	}
		//}
	}
	//�ǂƂ̓����蔻��
	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		MapChip::TrapData maps = map.GetTrap(trapIndex);
		if (maps.trap_type == PITFALL)continue;
		bool dir[4] = { false };
		maps.GetMoveDir(dir);
		if (IsHitRect(player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight(), maps.trapX, maps.trapY, maps.trapSizeX, maps.trapSizeY)) {
			if (dir[2]) { // ��
				float overlap = player.GetNextXPos() + player.GetWidth() - maps.trapNextX;
				player.SetNextXPos(player.GetNextXPos() - overlap);
			}
			else if (dir[3]) { // �E
				float overlap = maps.trapNextX + maps.trapSizeX - player.GetNextXPos();
				player.SetNextXPos(player.GetNextXPos() + overlap);
			}
		}
	}

	//���W�X�V
	map.UpDate();

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
				map.GetTrap(trapIndex).MoveTrapX(-1);
				break;
			case RIGHT_MOVE:
				map.GetTrap(trapIndex).MoveTrapX(1);
				break;
			case UP_MOVE:
				map.GetTrap(trapIndex).MoveTrapY(-1);
				break;
			case DOWN_MOVE:
				map.GetTrap(trapIndex).MoveTrapY(1);
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