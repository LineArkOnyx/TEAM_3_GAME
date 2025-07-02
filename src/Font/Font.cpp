#include "Font.h"

int Font::fontHandle[FONT_TYPE_NUM][CREATE_TYPE_NUM];

void Font::Init(){
	for (int i = 0; i < FONT_TYPE_NUM; i++) {
		//フォントのハンドルを作成
		for (int j = 0; j < CREATE_TYPE_NUM; j++) {
			fontHandle[i][j] = -1;
		}
	}
}

void Font::FontFileLoad(){
	//フォントをこのexeだけで読み込む
	for (int i = 0; i < FONT_TYPE_NUM; i++) {
		//フォント読込
		AddFontResourceEx(FontPath[i], FR_PRIVATE, NULL);
	}
}

void Font::FontHandleLoad(){
	for (int i = 0; i < FONT_TYPE_NUM; i++) {
		for (int j = 0; j < CREATE_TYPE_NUM; j++) {
			fontHandle[i][j] = CreateFontToHandle(FontLoadName[i], FontSize[j], FontThickness[j]);
		}
	}
}

void Font::Step() {
	
}

void Font::Draw() {

}

void Font::Fin() {
	for (int i = 0; i < FONT_TYPE_NUM; i++) {
		//フォント解放
		RemoveFontResourceEx(FontPath[i], FR_PRIVATE, NULL);
		for (int j = 0; j < CREATE_TYPE_NUM; j++) {
			DeleteFontToHandle(fontHandle[i][j]);
		}
	}
}
