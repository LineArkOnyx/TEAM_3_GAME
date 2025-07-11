#pragma once

#include "DxLib.h"

#define PATURN (32)


class AORI {
private:
	float m_PosX;
	float m_PosY;

	bool IsActive;

	int paturn;
public:

	char Comment[PATURN][128]{
		{"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"},
		{"wwwwwwww"},
		{"www"},
		{"がんばえ～"},
		{"草"},
		{"あーあ"},
		{"ちょwww"},
		{"なーにやってんだ"},
		{"????????????????"},
		{"避けられんか～"},
		{"うはw"},
		{"これほんとにクリアできる?"},
		{"うおおおおおおおお"},
		{"ｷﾀ━━━━(ﾟ∀ﾟ)━━━━!!"},
		{"やっぱダメじゃねえか!w"},
		{"余裕だぜ()"},
		{"へいへいピッチャービビってるww"},
		{"やってやろうじゃねぇかこの野郎!!"},
		{"おん"},
		{"いつまでやってんねん"},
		{"うぇ～い"},
		{"さすがに草"},
		{"うっざw"},
		{"ちょっと何言ってるかわからない"},
		{"俺でなきゃ見逃しちゃうね"},
		{"避けられんか～"},
		{"撃っていいのは撃たれる覚悟のあるやつだけだ()"},
		{"m9(^Д^)ﾌﾟｷﾞｬｰ"},
		{"審議"},
		{"シ。～愚かな死にざまについて～"},
		{"すまんかった"},
		{"貴方を詐欺罪と器物損壊罪で訴えます理由はもちろんお分かりですね"},
	};
	AORI();
	~AORI();

	void Init();
	void Load();
	void Step();
	void Exit();

	void Draw();

	void Request(int PosY);
	bool GetIsActive() { return IsActive; }

	float GetPosX() { return m_PosX; }
	float GetPosY() { return m_PosY; }
};