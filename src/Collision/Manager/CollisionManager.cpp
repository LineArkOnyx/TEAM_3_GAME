#include "CollisionManager.h"

bool IsPlayerOnBlock(Player& player, MapChip& block) {
	for (int trapIndex = 0; trapIndex < block.GetTrapVec().size(); trapIndex++) {
		MapChip::TrapData maps = block.GetTrap(trapIndex);
		if (maps.trap_type == PITFALL)continue;
		// プレイヤーの足元Yとブロックの上面Yが一致している
		float playerBottom = player.GetYPos() + player.GetHeight();
		float blockTop = maps.trapY;

		// Yの誤差が小さい（±数ピクセル）＝乗ってるとみなす
		const float tolerance = 4.0f;

		bool verticalMatch = fabs(playerBottom - blockTop) < tolerance;

		// 横方向に当たっている（範囲が重なっている）
		bool horizontalOverlap =
			player.GetXPos() + player.GetWidth() > maps.trapSizeX + 2 &&
			player.GetXPos() < maps.trapX + maps.trapSizeX + 2;

		return verticalMatch && horizontalOverlap;
	}
}

void CollisonManager::PlayerToMap(Player& player, MapChip& map) {

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

	//壁との当たり判定
	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		MapChip::TrapData maps = map.GetTrap(trapIndex);
		if (maps.trap_type == PITFALL)continue;
		bool dir[4] = { false };
		maps.GetMoveDir(dir);
		if (IsHitRect(player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight(), maps.trapX, maps.trapY, maps.trapSizeX, maps.trapSizeY)) {
			if (dir[0]) { // ブロックが上に動いている
				float overlap = player.GetNextYPos() + player.GetHeight() - maps.trapNextY;
				player.SetNextYPos(player.GetNextYPos() - overlap);
				player.SetJumpFlag(false);
				/*player.SetYSpeed(0.0f);*/
			}
			else if (dir[1]) { // 下
				float overlap = maps.trapNextY + maps.trapSizeY - player.GetNextYPos();
				player.SetNextYPos(player.GetNextYPos() + overlap);
			}
		}
		//if (IsPlayerOnBlock(player, map)) {
		//	bool dir[4] = { false };
		//	maps.GetMoveDir(dir);
		//	if (dir[2]) { // 左に動いてる
		//		player.SetXPos(player.GetXPos());
		//	}
		//	else if (dir[3]) { // 右に動いてる
		//		player.SetXPos(player.GetXPos());
		//	}
		//}
	}
	//壁との当たり判定
	for (int trapIndex = 0; trapIndex < map.GetTrapVec().size(); trapIndex++) {
		MapChip::TrapData maps = map.GetTrap(trapIndex);
		if (maps.trap_type == PITFALL)continue;
		bool dir[4] = { false };
		maps.GetMoveDir(dir);
		if (IsHitRect(player.GetXPos(), player.GetYPos(), player.GetWidth(), player.GetHeight(), maps.trapX, maps.trapY, maps.trapSizeX, maps.trapSizeY)) {
			if (dir[2]) { // 左
				float overlap = player.GetNextXPos() + player.GetWidth() - maps.trapNextX;
				player.SetNextXPos(player.GetNextXPos() - overlap);
			}
			else if (dir[3]) { // 右
				float overlap = maps.trapNextX + maps.trapSizeX - player.GetNextXPos();
				player.SetNextXPos(player.GetNextXPos() + overlap);
			}
		}
	}

	//座標更新
	map.UpDate();

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