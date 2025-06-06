#include "Input.h"


//現在のフレームのキー情報
char CInput::currentKeyBuf[KEY_BUF_LEN] = { 0 };
//前フレームのキー情報
char CInput::preKeyBuf[KEY_BUF_LEN] = { 0 };

//現在のフレームのマウス情報
int CInput::currentMouseBuf[MOUSE_BUF_LEN] = { 0 };
//前フレームのマウス情報
int CInput::preMouseBuf[MOUSE_BUF_LEN] = { 0 };

int CInput::JoypadNum = 0;

//入力制御初期化
void CInput::InitInput()
{
	//キー
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}

	//マウス
	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		currentMouseBuf[index] = 0;
		preMouseBuf[index] = 0;
	}
}

//入力制御のステップ
//ほかのステップより早く呼ぶ
void CInput::StepInput()
{


	//前のフレームのマウス情報変数に記録しておく
	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		preMouseBuf[index] = currentMouseBuf[index];
	}
	//前のフレームのキー情報変数に記録しておく
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		preKeyBuf[index] = currentKeyBuf[index];
	}
	//現在のキー情報を取得
	GetHitKeyStateAll(currentKeyBuf);
	//現在のマウス情報を取得
	GetHitMouseStateAll();
}


//キー
bool CInput::IsKeyPush(int key_code)
{
	//前振れで押されてない　かつ　現フレで押されている
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
		return true;

	//押されてないのでfalse
	return false;
}

bool CInput::IsKeyKeep(int key_code)
{
	//前振れで押されている　かつ　現フレも押されている
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

bool CInput::IsKeyRelease(int key_code)
{
	//前フレで押されている　かつ　現フレで押されていない
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
	{
		return true;
	}
	return false;
}

//押されている
bool CInput::IsKeyDown(int key_code)
{
	//現フレで押されている（前振れの状態は関係なし）
	if (currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}




//マウス関連
bool CInput::IsMousePush(int Mouse_code)
{
	//前振れで押されてない　かつ　現フレで押されている
	if (preMouseBuf[Mouse_code] == 0 && currentMouseBuf[Mouse_code] != 0) {
		return true;
	}

	//押されてないのでfalse
	return false;
}


bool CInput::IsMouseKeep(int Mouse_code)
{
	if (preMouseBuf[Mouse_code] == 1 && currentMouseBuf[Mouse_code] == 1)
	{
		return true;
	}

	return false;
}

bool CInput::IsMouseRelease(int Mouse_code)
{
	if (preMouseBuf[Mouse_code] == 1 && currentMouseBuf[Mouse_code] == 0)
	{
		return true;
	}
	return false;
}

//マウスの入力された状態を得る
void CInput::GetHitMouseStateAll()
{
	memset(currentMouseBuf, 0, sizeof(currentMouseBuf));

	if (GetMouseInput() && MOUSE_INPUT_LEFT != 0) {
		currentMouseBuf[0] = MOUSE_INPUT_LEFT;
	}
	else if(GetMouseInput() && MOUSE_INPUT_RIGHT){
		currentMouseBuf[1] = MOUSE_INPUT_RIGHT;
	}
	else if (GetMouseInput() && MOUSE_INPUT_MIDDLE) {
		currentMouseBuf[2] = MOUSE_INPUT_MIDDLE;
	}
}

