#include "Move.h"

int Move::imageTop = -1;
int Move::imageBottom = -1;
int Move::yTop = -600;
int Move::yBottom = 600;
int Move::holdCounter = 0;
Move::State Move::currentState = Move::State::Entering;

void Move::Init() {
    imageTop = LoadGraph("data/Move/Image (1).png");   // ã‚©‚ç—ˆ‚é‰æ‘œ
    imageBottom = LoadGraph("data/Move/Image.png");    // ‰º‚©‚ç—ˆ‚é‰æ‘œ
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
        if (holdCounter >= 30) { // 0.5•b’ö“x
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
        // ‰½‚à‚µ‚È‚¢
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
