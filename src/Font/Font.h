#pragma once
#include "DxLib.h"

//フォント種類
enum FONT_TYPE {
	ロックンロール,
	かくめい,
	ロンド,

	FONT_TYPE_NUM,
};

//フォント作成種類
enum CREATE_TYPE {
	_16_6,
	_32_6,
	_48_6,
	_64_6,

	CREATE_TYPE_NUM,
};

//フォントサイズ
constexpr int FontSize[CREATE_TYPE_NUM] = {
	16,
	32,
	48,
	64,
};

//フォントの太さ
constexpr int FontThickness[CREATE_TYPE_NUM] = {
	6,
	6,
	6,
	6,
};

//フォント名
constexpr char FontLoadName[FONT_TYPE_NUM][256] = {
	"RocknRoll One",
	"Nikkyou Sans",
	"ロンド B スクエア",
};

//フォントパス
constexpr char FontPath[FONT_TYPE_NUM][256] = {
	"data/Font/RocknRollOne-Regular.ttf",
	"data/Font/NikkyouSans-mLKax.ttf",
	"data/Font/Ronde-B_square.otf",
};

class Font {
public:

	//初期化
	static void Init();

	//フォントファイルの読込
	static void FontFileLoad();

	//フォントファイルの読込
	static void FontHandleLoad();

	//処理
	static void Step();

	//描画
	static void Draw();

	//終了
	static void Fin();

private:

protected:

public:

	//フォントハンドル
	static int fontHandle[FONT_TYPE_NUM][CREATE_TYPE_NUM];

};