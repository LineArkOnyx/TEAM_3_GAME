#pragma once
#include "DxLib.h"

class Effect {

private:

public:
	Effect();
	~Effect();

	//������
	void Init();
	//�ǂ݂���
	void Load();
	//�ʏ폈��
	void Step();
	//�`�揈��
	void Draw();
	//�I������
	void Fin();
	//�X�V����
	void Update();

};