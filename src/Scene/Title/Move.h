#pragma once
#include "DxLib.h"

class Move {
public:
    static void Init();           // �������i�摜���[�h�E�ʒu�ݒ�j
    static void Update();         // ��ԍX�V�i�A�j���[�V�����i�s�j
    static void Draw();           // �`��i�摜�̕\���j
    static bool IsFinished();     // �I���m�F�i���o���I��������j

private:
    enum class State {
        Entering,    // �����ֈړ���
        Holding,     // �����Œ�~
        Reversing,   // ���̕����ɖ߂�iU�^�[���j
        Finished     // �I��
    };

    static int imageTop;
    static int imageBottom;
    static int yTop;
    static int yBottom;
    static int holdCounter;
    static State currentState;
};
