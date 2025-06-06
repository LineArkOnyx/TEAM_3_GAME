#include <DxLib.h>
#include "CollisionManager.h"
#include "Collision.h"

//  定義関連------------------------------
//
////----------------------------------------
//
////-------------------------------------------------
////			プレイヤーと敵の当たり判定
////-------------------------------------------------
//void CCollisionManager::CheckHitPlayerToEnemy(CPlayer& cPlayer, CEnemyManager& cEnemyManager, CItemManager& cItemManager)
//{
//	//-------------------------------------------------
//	//				　	普通の敵
//	//-------------------------------------------------
//	for (int EnemyIndex = 0; EnemyIndex < ENEMY_MAX_NUM[ENEMY_NORMAL]; EnemyIndex++)
//	{
//		// 敵情報を取得し、生成されていなければ次へ
//		CEnemyBase& cEnemy = cEnemyManager.GetNormalEnemy(EnemyIndex);
//		if (!cEnemy.IsAlive()) continue;
//
//		// 座標と半径を取得
//		float fPlayerPosX, fPlayerPosY, fEnemyPosX, fEnemyPosY;
//		float fPlayerRadius, fEnemyRadius;
//
//		cPlayer.GetPosX(fPlayerPosX);
//		cPlayer.GetPosY(fPlayerPosY);
//		cEnemy.GetPosX(fEnemyPosX);
//		cEnemy.GetPosY(fEnemyPosY);
//
//		fPlayerRadius = cPlayer.GetRadius();
//		fEnemyRadius = cEnemy.GetRadius();
//
//		// 球と球の当たり判定
//		if (Collision::Circle(fPlayerRadius, fEnemyRadius, fPlayerPosX, fEnemyPosX, fPlayerPosY, fEnemyPosY))
//		{
//			cEnemy.HitNormalEnemyCalc(10, fPlayerPosX, fPlayerPosY, cItemManager);
//		}
//	}
//	//-------------------------------------------------
//	//				　	強い敵
//	//-------------------------------------------------
//	for (int EnemyIndex = 0; EnemyIndex < ENEMY_MAX_NUM[ENEMY_STRONG]; EnemyIndex++)
//	{
//		// 敵情報を取得し、生成されていなければ次へ
//		CEnemyBase& cEnemy = cEnemyManager.GetStrongEnemy(EnemyIndex);
//		if (!cEnemy.IsAlive()) continue;
//
//		// 座標と半径を取得
//		float fPlayerPosX, fPlayerPosY, fEnemyPosX, fEnemyPosY;
//		float fPlayerRadius, fEnemyRadius;
//
//		cPlayer.GetPosX(fPlayerPosX);
//		cPlayer.GetPosY(fPlayerPosY);
//		cEnemy.GetPosX(fEnemyPosX);
//		cEnemy.GetPosY(fEnemyPosY);
//
//		fPlayerRadius = cPlayer.GetRadius();
//		fEnemyRadius = cEnemy.GetRadius();
//
//		// 球と球の当たり判定
//		if (Collision::Circle(fPlayerRadius, fEnemyRadius, fPlayerPosX, fEnemyPosX, fPlayerPosY, fEnemyPosY))
//		{
//			cEnemy.HitStrongEnemyCalc(10, fPlayerPosX, fPlayerPosY, cItemManager);
//		}
//	}
//	//-------------------------------------------------
//	//				　	はやい敵
//	//-------------------------------------------------
//	for (int EnemyIndex = 0; EnemyIndex < ENEMY_MAX_NUM[ENEMY_QUICK]; EnemyIndex++)
//	{
//		// 敵情報を取得し、生成されていなければ次へ
//		CQuickEnemy& cEnemy = cEnemyManager.GetQuickEnemy(EnemyIndex);
//		if (!cEnemy.IsAlive()) continue;
//
//		// 座標と半径を取得
//		float fPlayerPosX, fPlayerPosY, fEnemyPosX[QUICK_ENEMY_MAX_NUM], fEnemyPosY[QUICK_ENEMY_MAX_NUM];
//		float fPlayerRadius, fEnemyRadius;
//
//		cPlayer.GetPosX(fPlayerPosX);
//		cPlayer.GetPosY(fPlayerPosY);
//
//		fPlayerRadius = cPlayer.GetRadius();
//		fEnemyRadius = cEnemy.GetRadius();
//
//		for (int i = 0; i < QUICK_ENEMY_MAX_NUM; i++)
//		{
//			cEnemy.GetQuickPosX(i,fEnemyPosX[i]);
//			cEnemy.GetQuickPosY(i,fEnemyPosY[i]);
//
//			// 球と球の当たり判定
//			if (Collision::Circle(fPlayerRadius, fEnemyRadius, fPlayerPosX, fEnemyPosX[i], fPlayerPosY, fEnemyPosY[i]))
//			{
//				cEnemy.HitQuickEnemyCalc(i, 10, fPlayerPosX, fPlayerPosY, cItemManager);
//			}
//		}
//	}
//}
//
////-------------------------------------------------
////		　プレイヤーとアイテムの当たり判定
////-------------------------------------------------
//void CCollisionManager::CheckHitPlayerToItem(CPlayer& cPlayer, CItemManager& cItemManager)
//{
//	//-------------------------------------------------
//	//				　	HealBall
//	//-------------------------------------------------
//	for (int ItemIndex = 0; ItemIndex < HEAL_ITEM_NUM; ItemIndex++)
//	{
//		// 敵情報を取得し、生成されていなければ次へ
//		CItemBase& cHealBall = cItemManager.GetHealBall(ItemIndex);
//		if (!cHealBall.IsActive()) continue;
//
//		// 座標と半径を取得
//		float fPlayerPosX, fPlayerPosY, fItemPosX, fItemPosY;
//		float fPlayerRadius, fPlayerCollectRadius, fItemRadius;
//
//		cPlayer.GetPosX(fPlayerPosX);
//		cPlayer.GetPosY(fPlayerPosY);
//		cHealBall.GetPosX(fItemPosX);
//		cHealBall.GetPosY(fItemPosY);
//
//		fPlayerRadius = cPlayer.GetRadius();
//		fPlayerCollectRadius = cPlayer.GetCollectRadius();
//		fItemRadius = cHealBall.GetRadius();
//
//		// アイテム取得範囲とアイテムの当たり判定処理
//		if (Collision::Circle(fPlayerCollectRadius, fItemRadius, fPlayerPosX, fItemPosX, fPlayerPosY, fItemPosY))
//		{
//			cHealBall.HitCollectCalc();
//		}
//		// プレイヤーとアイテムの当たり判定処理
//		if (Collision::Circle(fPlayerRadius, fItemRadius, fPlayerPosX, fItemPosX, fPlayerPosY, fItemPosY))
//		{
//			cHealBall.HitPlayerCalc();
//		}
//	}
//
//	//-------------------------------------------------
//	//				　	EXPBall
//	//-------------------------------------------------
//	for (int ItemIndex = 0; ItemIndex < HEAL_ITEM_NUM; ItemIndex++)
//	{
//		// 敵情報を取得し、生成されていなければ次へ
//		CItemBase& cEXPBall = cItemManager.GetEXPBall(ItemIndex);
//		if (!cEXPBall.IsActive()) continue;
//
//		// 座標と半径を取得
//		float fPlayerPosX, fPlayerPosY, fItemPosX, fItemPosY;
//		float fPlayerRadius, fPlayerCollectRadius, fItemRadius;
//
//		cPlayer.GetPosX(fPlayerPosX);
//		cPlayer.GetPosY(fPlayerPosY);
//		cEXPBall.GetPosX(fItemPosX);
//		cEXPBall.GetPosY(fItemPosY);
//
//		fPlayerRadius = cPlayer.GetRadius();
//		fPlayerCollectRadius = cPlayer.GetCollectRadius();
//		fItemRadius = cEXPBall.GetRadius();
//
//		// アイテム取得範囲とアイテムの当たり判定処理
//		if (Collision::Circle(fPlayerCollectRadius, fItemRadius, fPlayerPosX, fItemPosX, fPlayerPosY, fItemPosY))
//		{
//			cEXPBall.HitCollectCalc();
//		}
//		// プレイヤーとアイテムの当たり判定処理
//		if (Collision::Circle(fPlayerRadius, fItemRadius, fPlayerPosX, fItemPosX, fPlayerPosY, fItemPosY))
//		{
//			cEXPBall.HitPlayerCalc();
//		}
//	}
//}
