#pragma once

#include "DxLib.h"
static class Move {
public:
	static void Init();
	static void Load();
	static int Step();
	static void Exit();
	Move();
	~Move();
	static int Loop();
	static void Draw();
};