#pragma once
#include <DxLib.h>
#include <math.h>

// ラジアン角に変換する式
#define DEG_TO_RAD(a)	((a) * DX_PI_F / 180.0f)

template<class T>
class Math2D {
public:
	//============================================================
	//                          四則演算
	//============================================================

	// 加算
	static T Add(T NumA, T NumB)
	{
		return NumA + NumB;
	}

	// 減算
	static T Sub(T NumA, T NumB)
	{
		return NumA - NumB;
	}

	// 乗算
	static T Mult(T NumA, T NumB)
	{
		return NumA * NumB;
	}

	// 除算
	static T Div(T NumA, T NumB)
	{
		return NumA / NumB;
	}

	//============================================================
	//                          指数法則
	//============================================================

	// NumA^NumB
	static T Exponent(T Num, T Index)
	{
		T ExponentNum = Num;

		// 指数が0であるならば
		if (Index == 0)
		{
			ExponentNum = 1;
			return ExponentNum;
		}
		// 指数が0より小さいとき
		else if (Index < 0)
		{
			for (int ExponentIndex = -1; ExponentIndex > Index; ExponentIndex--)
			{
				ExponentNum *= Num;
			}

			return 1 / ExponentNum;
		}
		// 指数が0より大きいとき
		else
		{
			for (int ExponentIndex = 1; ExponentIndex < Index; ExponentIndex++)
			{
				ExponentNum *= Num;
			}

			return ExponentNum;
		}
	}

	//============================================================
	//                        直線の方程式
	//============================================================

	// 傾き
	// 傾き = APosY - BPosY / APosX - BPosX ( Yの増加量 / Xの増加量 )
	static T Slope(T APosX, T APosY, T BPosX, T BPosY)
	{
		// Xの増加量
		T Run = APosX - BPosX;
		// Yの増加量
		T Rise = APosY - BPosY;

		return Div(Rise, Run);
	}

	// Y切片
	// Y切片 = PosY - (Slope * PosX)
	static T Yintercept(T PosX, T PosY, T Slope)
	{
		return Sub(PosY, Mult(Slope, PosX));
	}

	// 直線の交点

	// 交点Xの座標
	// 交点X = (YinterceptB - YinterceptA) / (SlopeA - SlopeB)
	static T IntersectionX(T SlopeA, T YinterceptA, T SlopeB, T YinterceptB)
	{
		return Div(Sub(YinterceptB, YinterceptA), Sub(SlopeA, SlopeB));
	}

	// 交点Yの座標
	// 交点Y = (Slope * IntersectionX) + Yintercept
	static T IntersectionY(T Slope, T Yintercept, T IntersectionX)
	{
		return Add(Mult(Slope, IntersectionX), Yintercept);
	}

	//============================================================
	//                         三角関数
	//============================================================
	// X = cosθ・r
	// Y = sinθ・r
	// Xの変化量
	static T TrigfuncX(T APosX, T BPosX)
	{
		T PosX = 0;
		PosX = APosX - BPosX;

		return PosX;
	}

	// Yの変化量
	static T TrigfuncY(T APosY, T BPosY)
	{
		T PosY = 0;
		PosY = APosY - BPosY;

		return PosY;
	}

	// rを求める
	static T RadiusTrigfunc(T APosX, T APosY, T BPosX, T BPosY)
	{
		return  (T)sqrt(Exponent(TrigfuncX(APosX, BPosX), 2) + Exponent(TrigfuncY(APosY, BPosY), 2));
	}

	// cosを求める
	static T FindTheAngle_cos(T APosX, T APosY, T BPosX, T BPosY)
	{
		return TrigfuncX(APosX, BPosX) / RadiusTrigfunc(APosX, APosY, BPosX, BPosY);
	}

	// sinを求める
	static T FindTheAngle_sin(T APosX, T APosY, T BPosX, T BPosY)
	{
		return TrigfuncY(APosY, BPosY) / RadiusTrigfunc(APosX, APosY, BPosX, BPosY);
	}


	//============================================================
	//                          ベクトル
	//============================================================

	// ベクトルの長さを求める
	static T vLength(T PosX, T PosY)
	{
		return sqrt(Exponent(PosX, 2) + Exponent(PosY, 2));
	}

	// 内積からラジアン角を求める
	static T Dot(T APosX, T APosY, T BPosX, T BPosY)
	{
		return acos((APosX * BPosX) + (APosY * BPosY));
	}

	// 外積


};

class Math3D {
public:
	static VECTOR VecCreate(VECTOR VectorA, VECTOR VectorB);
	static VECTOR AddVec(VECTOR VectorA, VECTOR VectorB);
	static VECTOR MultVec(VECTOR VectorA, VECTOR VectorB);
};