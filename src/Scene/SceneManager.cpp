#include "SceneManager.h"

//定義関連


//コンストラクタ
SceneManager::SceneManager()
{
	//最初はタイトル画面に
	m_eSceneID = SCENE_TITLE;
}

void SceneManager::Loop()
{
	//ゴールしたか死亡したか判定する
	int End = 0;

	//ここはひとまずswitch文を利用する
	switch (m_eSceneID)
	{
	case SceneManager::SCENE_TITLE:
		//タイトルのエンドシーンまで来たら
		if (cTitle.Loop() != 0) 
		{
			//セレクトシーンに移動する
			m_eSceneID = SCENE_SELECT;
		}
		break;
	case SceneManager::SCENE_SELECT:
		//セレクトのエンドまで来たら
		if(cSelect.Loop() != 0)
		{
			//プレイシーンに行く
			m_eSceneID = SCENE_PLAY;
		}
		break;
	case SceneManager::SCENE_PLAY:
		if (cPlay.Loop() != 0)
		{
			//リザルトシーンに行く
			m_eSceneID = SCENE_RESULT;
		}
		break;
	case SceneManager::SCENE_RESULT:
		if (cResult.Loop() != 0)
		{
			//タイトルシーンに行く
			m_eSceneID = SCENE_TITLE;
		}
		break;
	}
}

//更新処理
void SceneManager::Draw()
{
	switch (m_eSceneID)
	{
	case SceneManager::SCENE_TITLE:
		cTitle.Draw();
		break;
	case SceneManager::SCENE_SELECT:
		cSelect.Draw();
		break;
	case SceneManager::SCENE_PLAY:
		cPlay.Draw();
		break;
	case SceneManager::SCENE_RESULT:
		cResult.Draw();
		break;
	}
}
