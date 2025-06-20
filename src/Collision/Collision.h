
#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "DxLib.h"

//2Dの当たり判定
//四角形の当たり判定
//IsHitRectのプロトタイプ宣言
//int型
bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);
//float型
//bool IsHitRect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh);

//3Dの当たり判定
//第一引数,オブジェクト1の座標、第二引数,オブジェクト1の幅・高さ・奥行き
//第三引数,オブジェクト2の座標、第四引数,オブジェクト2の幅・高さ・奥行き
bool IsHitRect(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize);


//円の当たり判定
//IsHitCircleのプロトタイプ宣言
//int型
bool IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR);
//float型
bool IsHitCircle(float aX, float aY, float aR, float bX, float bY, float bR);

//球の当たり判定
//第一引数、球1の半径、第二引数、球1の座標
//第三引数、球2の半径、第四引数、球2の座標
bool SphereCollision(float aR, VECTOR aPos, float bR, VECTOR bPos);

//矩形と円の当たり判定

bool IsHitSphereAndRectCollision(float aX, float aY, float aR, float Bx, float By, float Bw, float Bh);

#endif
