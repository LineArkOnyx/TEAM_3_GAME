
#include "Collision.h"

//2D
//IsHitRect‚Ì’è‹`
bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh) {
	if (Bx < Ax + Aw &&
		Bx + Bw > Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		// “–‚½‚Á‚Ä‚¢‚é‚Æ‚«‚Ìˆ—
		return true;
	}
	return false;
}

bool IsHitUpper(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw){
	if (Bx < Ax + Aw && Bx + Bw > Ax && By < Ay + Ah) {
		return true;
	}
	return false;
}

//IsHitCircle‚Ì’è‹`
bool IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY)) {
		//“–‚½‚Á‚Ä‚¢‚é‚Ìˆ—
		return true;
	}

	return false;

}

bool IsHitRect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) {
	if (Bx < Ax + Aw &&
		Bx + Bw > Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		// “–‚½‚Á‚Ä‚¢‚é‚Æ‚«‚Ìˆ—
		return true;
	}
	return false;
}

//IsHitCircle‚Ì’è‹`
bool IsHitCircle(float aX, float aY, float aR, float bX, float bY, float bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY)) {
		//“–‚½‚Á‚Ä‚¢‚é‚Ìˆ—
		return true;
	}

	return false;

}

//3D
//’¼•û‘Ì“–‚½‚è”»’è
bool IsHitRect(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize)
{
	if (bPos.x < aPos.x + aSize.x &&
		bPos.x + bSize.x > aPos.x &&
		bPos.y + bSize.y > aPos.y &&
		bPos.y < aPos.y + aSize.y &&
		bPos.z + bSize.z > aPos.z &&
		bPos.z < aPos.z + aSize.z)
	{
		//“–‚½‚Á‚Ä‚¢‚é‚Ìˆ—
		return true;
	}

	//“–‚½‚Á‚Ä‚¢‚È‚¢‚Æ‚«
	return false;
}

//‹…‚Ì“–‚½‚è”»’è
bool SphereCollision(float aR, VECTOR aPos, float bR, VECTOR bPos)
{
	if ((aR + bR) * (aR + bR) >
		(aPos.x - bPos.x) * (aPos.x - bPos.x) +
		(aPos.y - bPos.y) * (aPos.y - bPos.y) +
		(aPos.z - bPos.z) * (aPos.z - bPos.z))
	{
		//“–‚½‚Á‚Ä‚¢‚é‚Æ‚«
		return true;
	}
	//‚ ‚½‚Á‚Ä‚¢‚È‚¢‚Æ‚«
	return false;
}

bool IsHitSphereAndRectCollision(float aX, float aY, float aR, float Bx, float By, float Bw, float Bh)
{
	if ((aX > Bx) && (aX < Bx + Bw) && (aY > By - aR) && (aY < By + Bh + aR))
	{
		return true;
	}
	else if ((aX > Bx - aR) && (aX < Bx + Bw + aR) && (aY > By) && (aY < By + Bh))
	{
		return true;
	}
	else if (((Bx - aX) * (Bx - aX)) + ((By - aY) * (By - aY)) < (aR * aR))
	{
		return true;
	}
	else if (((Bx + Bw - aX) * (Bx + Bw - aX)) + ((By - aY) * (By - aY)) < (aR * aR))
	{
		return true;
	}
	else if (((Bx + Bw - aX) * (Bx + Bw - aX)) + ((By + Bh - aY) * (By + Bh - aY)) < (aR * aR))
	{
		return true;
	}
	else if (((Bx - aX) * (Bx - aX)) + ((By + Bh - aY) * (By + Bh - aY)) < (aR * aR))
	{
		return true;
	}
	//‚ ‚Á‚Ä‚¢‚È‚¢‚Æ‚«
	else {
		return false;
	}
}