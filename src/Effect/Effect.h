#pragma once
#include "DxLib.h"

class Effect {

private:

public:
	Effect();
	~Effect();

	//‰Šú‰»
	void Init();
	//“Ç‚İ‚±‚İ
	void Load();
	//’Êíˆ—
	void Step();
	//•`‰æˆ—
	void Draw();
	//I—¹ˆ—
	void Fin();
	//XVˆ—
	void Update();

};