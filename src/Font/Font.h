#pragma once
#include "DxLib.h"

//�t�H���g���
enum FONT_TYPE {
	���b�N�����[��,
	�����߂�,
	�����h,

	FONT_TYPE_NUM,
};

//�t�H���g�쐬���
enum CREATE_TYPE {
	_16_6,
	_32_6,
	_48_6,
	_64_6,

	CREATE_TYPE_NUM,
};

//�t�H���g�T�C�Y
constexpr int FontSize[CREATE_TYPE_NUM] = {
	16,
	32,
	48,
	64,
};

//�t�H���g�̑���
constexpr int FontThickness[CREATE_TYPE_NUM] = {
	6,
	6,
	6,
	6,
};

//�t�H���g��
constexpr char FontLoadName[FONT_TYPE_NUM][256] = {
	"RocknRoll One",
	"Nikkyou Sans",
	"�����h B �X�N�G�A",
};

//�t�H���g�p�X
constexpr char FontPath[FONT_TYPE_NUM][256] = {
	"data/Font/RocknRollOne-Regular.ttf",
	"data/Font/NikkyouSans-mLKax.ttf",
	"data/Font/Ronde-B_square.otf",
};

class Font {
public:

	//������
	static void Init();

	//�t�H���g�t�@�C���̓Ǎ�
	static void FontFileLoad();

	//�t�H���g�t�@�C���̓Ǎ�
	static void FontHandleLoad();

	//����
	static void Step();

	//�`��
	static void Draw();

	//�I��
	static void Fin();

private:

protected:

public:

	//�t�H���g�n���h��
	static int fontHandle[FONT_TYPE_NUM][CREATE_TYPE_NUM];

};