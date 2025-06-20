#include "CollisionManager.h"

void CollisonManager::PlayerToMap(Player& player, MapChip& map){

	//プレイヤーとマップの当たり判定
	for (int mapIndexY = 0; mapIndexY < CHIP_Y_MAX; mapIndexY++) {
		for (int mapIndexX = 0; mapIndexX < CHIP_X_MAX; mapIndexX++) {
			if (map.GetFileData(mapIndexY, mapIndexX) == -1)continue;
			bool dir[4] = { false };
			player.GetMoveDir(dir);

			if (IsHitRect(player.GetXPos(), player.GetNextXPos(), PLAYER_WIDTH, PLAYER_HEIGHT, mapIndexX * CHIP_SIZE, mapIndexY * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE)) {

			}
		}
	}

	//トラップの起動処理
	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		if (map.GetTrap(trapIndex).isTrigger) {
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