#include <DxLib.h>
#include "CollisionManager.h"
#include "Collision.h"

//  ��`�֘A------------------------------
//
////----------------------------------------
//
////-------------------------------------------------
////			�v���C���[�ƓG�̓����蔻��
////-------------------------------------------------
//void CCollisionManager::CheckHitPlayerToEnemy(CPlayer& cPlayer, CEnemyManager& cEnemyManager, CItemManager& cItemManager)
//{
//	//-------------------------------------------------
//	//				�@	���ʂ̓G
//	//-------------------------------------------------
//	for (int EnemyIndex = 0; EnemyIndex < ENEMY_MAX_NUM[ENEMY_NORMAL]; EnemyIndex++)
//	{
//		// �G�����擾���A��������Ă��Ȃ���Ύ���
//		CEnemyBase& cEnemy = cEnemyManager.GetNormalEnemy(EnemyIndex);
//		if (!cEnemy.IsAlive()) continue;
//
//		// ���W�Ɣ��a���擾
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
//		// ���Ƌ��̓����蔻��
//		if (Collision::Circle(fPlayerRadius, fEnemyRadius, fPlayerPosX, fEnemyPosX, fPlayerPosY, fEnemyPosY))
//		{
//			cEnemy.HitNormalEnemyCalc(10, fPlayerPosX, fPlayerPosY, cItemManager);
//		}
//	}
//	//-------------------------------------------------
//	//				�@	�����G
//	//-------------------------------------------------
//	for (int EnemyIndex = 0; EnemyIndex < ENEMY_MAX_NUM[ENEMY_STRONG]; EnemyIndex++)
//	{
//		// �G�����擾���A��������Ă��Ȃ���Ύ���
//		CEnemyBase& cEnemy = cEnemyManager.GetStrongEnemy(EnemyIndex);
//		if (!cEnemy.IsAlive()) continue;
//
//		// ���W�Ɣ��a���擾
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
//		// ���Ƌ��̓����蔻��
//		if (Collision::Circle(fPlayerRadius, fEnemyRadius, fPlayerPosX, fEnemyPosX, fPlayerPosY, fEnemyPosY))
//		{
//			cEnemy.HitStrongEnemyCalc(10, fPlayerPosX, fPlayerPosY, cItemManager);
//		}
//	}
//	//-------------------------------------------------
//	//				�@	�͂₢�G
//	//-------------------------------------------------
//	for (int EnemyIndex = 0; EnemyIndex < ENEMY_MAX_NUM[ENEMY_QUICK]; EnemyIndex++)
//	{
//		// �G�����擾���A��������Ă��Ȃ���Ύ���
//		CQuickEnemy& cEnemy = cEnemyManager.GetQuickEnemy(EnemyIndex);
//		if (!cEnemy.IsAlive()) continue;
//
//		// ���W�Ɣ��a���擾
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
//			// ���Ƌ��̓����蔻��
//			if (Collision::Circle(fPlayerRadius, fEnemyRadius, fPlayerPosX, fEnemyPosX[i], fPlayerPosY, fEnemyPosY[i]))
//			{
//				cEnemy.HitQuickEnemyCalc(i, 10, fPlayerPosX, fPlayerPosY, cItemManager);
//			}
//		}
//	}
//}
//
////-------------------------------------------------
////		�@�v���C���[�ƃA�C�e���̓����蔻��
////-------------------------------------------------
//void CCollisionManager::CheckHitPlayerToItem(CPlayer& cPlayer, CItemManager& cItemManager)
//{
//	//-------------------------------------------------
//	//				�@	HealBall
//	//-------------------------------------------------
//	for (int ItemIndex = 0; ItemIndex < HEAL_ITEM_NUM; ItemIndex++)
//	{
//		// �G�����擾���A��������Ă��Ȃ���Ύ���
//		CItemBase& cHealBall = cItemManager.GetHealBall(ItemIndex);
//		if (!cHealBall.IsActive()) continue;
//
//		// ���W�Ɣ��a���擾
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
//		// �A�C�e���擾�͈͂ƃA�C�e���̓����蔻�菈��
//		if (Collision::Circle(fPlayerCollectRadius, fItemRadius, fPlayerPosX, fItemPosX, fPlayerPosY, fItemPosY))
//		{
//			cHealBall.HitCollectCalc();
//		}
//		// �v���C���[�ƃA�C�e���̓����蔻�菈��
//		if (Collision::Circle(fPlayerRadius, fItemRadius, fPlayerPosX, fItemPosX, fPlayerPosY, fItemPosY))
//		{
//			cHealBall.HitPlayerCalc();
//		}
//	}
//
//	//-------------------------------------------------
//	//				�@	EXPBall
//	//-------------------------------------------------
//	for (int ItemIndex = 0; ItemIndex < HEAL_ITEM_NUM; ItemIndex++)
//	{
//		// �G�����擾���A��������Ă��Ȃ���Ύ���
//		CItemBase& cEXPBall = cItemManager.GetEXPBall(ItemIndex);
//		if (!cEXPBall.IsActive()) continue;
//
//		// ���W�Ɣ��a���擾
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
//		// �A�C�e���擾�͈͂ƃA�C�e���̓����蔻�菈��
//		if (Collision::Circle(fPlayerCollectRadius, fItemRadius, fPlayerPosX, fItemPosX, fPlayerPosY, fItemPosY))
//		{
//			cEXPBall.HitCollectCalc();
//		}
//		// �v���C���[�ƃA�C�e���̓����蔻�菈��
//		if (Collision::Circle(fPlayerRadius, fItemRadius, fPlayerPosX, fItemPosX, fPlayerPosY, fItemPosY))
//		{
//			cEXPBall.HitPlayerCalc();
//		}
//	}
//}
