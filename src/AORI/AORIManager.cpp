#include "AORIManager.h"

AORIManager::AORIManager() {

}
AORIManager::~AORIManager() {

}


void AORIManager::Init() {
	for (int i = 0; i < PATURN; i++) {
		Aori[i].Init();
	}
	requestcount = 0;
}
void AORIManager::Load() {
	for (int i = 0; i < PATURN; i++) {
	}
}
void AORIManager::Step() {
	for (int i = 0; i < PATURN; i++) {
		Aori[i].Step();
	}


	requestcount--;
	if (requestcount < 0) {
		RandomRequest();
		requestcount = GetRand(150);
	}
}
void AORIManager::Exit() {
	for (int i = 0; i < PATURN; i++) {
		Aori[i].Exit();
	}
}

void AORIManager::Draw() {
	for (int i = 0; i < PATURN; i++) {
		Aori[i].Draw();
	}
}

void AORIManager::RandomRequest() {

	int DeadCount = 0;

	while (1)
	{
		int i = GetRand(PATURN - 1);
		

		if (!Aori[i].GetIsActive()) {
			Aori[i].Request(GetRand(720));
			break;
		}

		DeadCount++;
		if (DeadCount > 20) {
			break;
		}
	}
	
}