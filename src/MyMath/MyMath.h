#pragma once
#include <DxLib.h>
#include <math.h>

// ���W�A���p�ɕϊ����鎮
#define DEG_TO_RAD(a)	((a) * DX_PI_F / 180.0f)

template<class T>
class Math2D {
public:
	//============================================================
	//                          �l�����Z
	//============================================================

	// ���Z
	static T Add(T NumA, T NumB)
	{
		return NumA + NumB;
	}

	// ���Z
	static T Sub(T NumA, T NumB)
	{
		return NumA - NumB;
	}

	// ��Z
	static T Mult(T NumA, T NumB)
	{
		return NumA * NumB;
	}

	// ���Z
	static T Div(T NumA, T NumB)
	{
		return NumA / NumB;
	}

	//============================================================
	//                          �w���@��
	//============================================================

	// NumA^NumB
	static T Exponent(T Num, T Index)
	{
		T ExponentNum = Num;

		// �w����0�ł���Ȃ��
		if (Index == 0)
		{
			ExponentNum = 1;
			return ExponentNum;
		}
		// �w����0��菬�����Ƃ�
		else if (Index < 0)
		{
			for (int ExponentIndex = -1; ExponentIndex > Index; ExponentIndex--)
			{
				ExponentNum *= Num;
			}

			return 1 / ExponentNum;
		}
		// �w����0���傫���Ƃ�
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
	//                        �����̕�����
	//============================================================

	// �X��
	// �X�� = APosY - BPosY / APosX - BPosX ( Y�̑����� / X�̑����� )
	static T Slope(T APosX, T APosY, T BPosX, T BPosY)
	{
		// X�̑�����
		T Run = APosX - BPosX;
		// Y�̑�����
		T Rise = APosY - BPosY;

		return Div(Rise, Run);
	}

	// Y�ؕ�
	// Y�ؕ� = PosY - (Slope * PosX)
	static T Yintercept(T PosX, T PosY, T Slope)
	{
		return Sub(PosY, Mult(Slope, PosX));
	}

	// �����̌�_

	// ��_X�̍��W
	// ��_X = (YinterceptB - YinterceptA) / (SlopeA - SlopeB)
	static T IntersectionX(T SlopeA, T YinterceptA, T SlopeB, T YinterceptB)
	{
		return Div(Sub(YinterceptB, YinterceptA), Sub(SlopeA, SlopeB));
	}

	// ��_Y�̍��W
	// ��_Y = (Slope * IntersectionX) + Yintercept
	static T IntersectionY(T Slope, T Yintercept, T IntersectionX)
	{
		return Add(Mult(Slope, IntersectionX), Yintercept);
	}

	//============================================================
	//                         �O�p�֐�
	//============================================================
	// X = cos�ƁEr
	// Y = sin�ƁEr
	// X�̕ω���
	static T TrigfuncX(T APosX, T BPosX)
	{
		T PosX = 0;
		PosX = APosX - BPosX;

		return PosX;
	}

	// Y�̕ω���
	static T TrigfuncY(T APosY, T BPosY)
	{
		T PosY = 0;
		PosY = APosY - BPosY;

		return PosY;
	}

	// r�����߂�
	static T RadiusTrigfunc(T APosX, T APosY, T BPosX, T BPosY)
	{
		return  (T)sqrt(Exponent(TrigfuncX(APosX, BPosX), 2) + Exponent(TrigfuncY(APosY, BPosY), 2));
	}

	// cos�����߂�
	static T FindTheAngle_cos(T APosX, T APosY, T BPosX, T BPosY)
	{
		return TrigfuncX(APosX, BPosX) / RadiusTrigfunc(APosX, APosY, BPosX, BPosY);
	}

	// sin�����߂�
	static T FindTheAngle_sin(T APosX, T APosY, T BPosX, T BPosY)
	{
		return TrigfuncY(APosY, BPosY) / RadiusTrigfunc(APosX, APosY, BPosX, BPosY);
	}


	//============================================================
	//                          �x�N�g��
	//============================================================

	// �x�N�g���̒��������߂�
	static T vLength(T PosX, T PosY)
	{
		return sqrt(Exponent(PosX, 2) + Exponent(PosY, 2));
	}

	// ���ς��烉�W�A���p�����߂�
	static T Dot(T APosX, T APosY, T BPosX, T BPosY)
	{
		return acos((APosX * BPosX) + (APosY * BPosY));
	}

	// �O��


};

class Math3D {
public:
	static VECTOR VecCreate(VECTOR VectorA, VECTOR VectorB);
	static VECTOR AddVec(VECTOR VectorA, VECTOR VectorB);
	static VECTOR MultVec(VECTOR VectorA, VECTOR VectorB);
};