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
		{"����΂��`"},
		{"��"},
		{"���[��"},
		{"����www"},
		{"�ȁ[�ɂ���Ă�"},
		{"????????????????"},
		{"�������񂩁`"},
		{"����w"},
		{"����ق�ƂɃN���A�ł���?"},
		{"������������������"},
		{"����������(߁��)��������!!"},
		{"����σ_������˂���!w"},
		{"�]�T����()"},
		{"�ւ��ւ��s�b�`���[�r�r���Ă�ww"},
		{"����Ă�낤����˂������̖�Y!!"},
		{"����"},
		{"���܂ł���Ă�˂�"},
		{"�����`��"},
		{"�������ɑ�"},
		{"������w"},
		{"������Ɖ������Ă邩�킩��Ȃ�"},
		{"���łȂ��ጩ�������Ⴄ��"},
		{"�������񂩁`"},
		{"�����Ă����̂͌������o��̂���������()"},
		{"m9(^�D^)�߷ެ�"},
		{"�R�c"},
		{"�V�B�`�����Ȏ��ɂ��܂ɂ��ā`"},
		{"���܂񂩂���"},
		{"�M�������\�߂Ɗ함����߂ői���܂����R�͂�����񂨕�����ł���"},
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