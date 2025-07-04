#pragma once
#include "../Collision.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"

class CollisonManager {
private:

protected:

public:

	void Init();

	void PlayerToMap(Player& player, MapChip& map);

	bool goal;

};