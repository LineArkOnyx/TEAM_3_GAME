#include "MyMath.h"

VECTOR Math3D::VecCreate(VECTOR VectorA, VECTOR VectorB)
{//ベクトル生成
	VECTOR result;
	result.x = VectorB.x - VectorA.x;
	result.y = VectorB.y - VectorA.y;
	result.z = VectorB.z - VectorA.z;
	return result;
}

VECTOR Math3D::AddVec(VECTOR VectorA, VECTOR VectorB)
{
	//ベクトル生成
	VECTOR result;
	result.x = VectorA.x + VectorB.x;
	result.y = VectorA.y + VectorB.y;
	result.z = VectorA.z + VectorB.z;
	return result;
}

VECTOR Math3D::MultVec(VECTOR VectorA, VECTOR VectorB)
{
	//ベクトル生成
	VECTOR result;
	result.x = VectorA.x * VectorB.x;
	result.y = VectorA.y * VectorB.y;
	result.z = VectorA.z * VectorB.z;
	return result;
}