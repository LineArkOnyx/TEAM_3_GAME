#include "AORI.h"

AORI::AORI() {

}
AORI::~AORI() {

}

void AORI::Init() {
	m_PosX = 0.0f;
	m_PosY = 0.0f;
	IsActive = false;
	paturn = 0;
}
void AORI::Load() {
	
}
void AORI::Step() {
	if (IsActive) {
		
		m_PosX -= 5.0f;

		if (m_PosX < -640.0f) {
			IsActive = false;
		}
	}
}
void AORI::Exit() {
	m_PosX = 0.0f;
	m_PosY = 0.0f;
	IsActive = false;

}

void AORI::Draw() {
	if (IsActive) {
		DrawFormatString(m_PosX, m_PosY, GetColor(255, 255, 255), Comment[paturn]);
	}
}

void AORI::Request(int PosY) {
	m_PosX = 1280.0f;
	m_PosY = PosY;
	IsActive = true;
	paturn = GetRand(PATURN - 1);
}