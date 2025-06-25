#include "CollisionManager.h"

void CollisonManager::PlayerToMap(Player& player, MapChip& map){

	//プレイヤーとマップの当たり判定
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

	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		//トリガーとの当たり判定
		if (IsHitRect(player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight(), map.GetTrap(trapIndex).triggerX, map.GetTrap(trapIndex).triggerY, map.GetTrap(trapIndex).triggerXSize, map.GetTrap(trapIndex).triggerYSize)) {
			map.GetTrap(trapIndex).isTrigger = true;
		}
		//起動したら
		if (map.GetTrap(trapIndex).isTrigger) {
			//トラップの起動処理
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