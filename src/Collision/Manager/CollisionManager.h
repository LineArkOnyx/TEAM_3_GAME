#pragma once
#include <string>

#include "../Collision.h"
#include "../../MapChip/MapChip.h"
#include "../../Player/LevelDevilPlayer.h"
#include "../../AORI/AORIManager.h"

class CollisonManager {
private:

protected:

public:

	void Init();

	void PlayerToMap(Player& player, MapChip& map);

	void PlayerToAORI(Player& player, AORIManager& aori);

	bool goal;

};