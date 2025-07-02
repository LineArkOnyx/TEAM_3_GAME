#include "Move.h"

int Move::imageTop = -1;
int Move::imageBottom = -1;
int Move::yTop = -600;
int Move::yBottom = 600;
int Move::holdCounter = 0;
Move::State Move::currentState = Move::State::Entering;

void Move::Init() {
    imageTop = LoadGraph("data/Move/Image (1).png");   // �ォ�痈��摜
    imageBottom = LoadGraph("data/Move/Image.png");    // �����痈��摜
    yTop = -600;
    yBottom = 600;
    holdCounter = 0;
    currentState = State::Entering;
}

void Move::Update() {
    switch (currentState) {
    case State::Entering:
        yTop += 20;
        yBottom -= 20;
        if (yTop >= 0) {
            yTop = 0;
            yBottom = 0;
            currentState = State::Holding;
        }
        break;

    case State::Holding:
        holdCounter++;
        if (holdCounter >= 30) { // 0.5�b���x
            currentState = State::Reversing;
        }
        break;

    case State::Reversing:
        yTop -= 20;
        yBottom += 20;
        if (yTop < -600 && yBottom > 600) {
            currentState = State::Finished;
        }
        break;

    case State::Finished:
        // �������Ȃ�
        break;
    }
}

void Move::Draw() {
    DrawGraph(0, yTop, imageTop, true);
    DrawGraph(0, yBottom, imageBottom, true);
}

bool Move::IsFinished() {
    return currentState == State::Finished;
}
