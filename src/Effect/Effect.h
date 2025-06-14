#pragma once
#include "DxLib.h"

class Effect {

private:

public:
	Effect();
	~Effect();

	//初期化
	void Init();
	//読みこみ
	void Load();
	//通常処理
	void Step();
	//描画処理
	void Draw();
	//終了処理
	void Fin();
	//更新処理
	void Update();

};