#include "CollisionManager.h"

void CollisonManager::PlayerToMap(MapChip& map){
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
						map.SetFileData(y, x, 2);
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