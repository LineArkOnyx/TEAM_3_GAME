#pragma once

#include "AORI.h"


class AORIManager {
private:

	

	AORI Aori[PATURN];

	int requestcount;

public:

	AORIManager();
	~AORIManager();

	void Init();
	void Load();
	void Step();
	void Exit();

	void Draw();

	void RandomRequest();
};