#pragma once

#include "Title/TitleScene.h"
#include "Select/SelectScene.h"
#include "Play/PlayScene.h"
#include "Result/ResultScene.h"

class SceneManager
{
private:
	enum tagSCENE {
		SCENE_TITLE,	//タイトル画面
		SCENE_SELECT,	//セレクト画面
		SCENE_PLAY,		//ゲーム中画面
		SCENE_RESULT,	//リザルト画面

		SCENE_NUM
	};

	
	tagSCENE m_eSceneID;		//シーン保存

	TitleScene cTitle;
	SelectScene cSelect;
	PlayScene cPlay;
	ResultScene cResult;

public:
	//コンストラクタ
	SceneManager();

	//繰り返し行う処理
	void Loop();

	//描画処理
	void Draw();
};

