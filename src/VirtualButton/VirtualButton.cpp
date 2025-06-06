#include "VirtualButton.h"

CVirtualButton_Square* CVirtualButton_Square::m_Instance = NULL;

CVirtualButton_Square* CVirtualButton_Square::GetInstance() {
	if (m_Instance == NULL) {
		m_Instance = new CVirtualButton_Square();
	}

	return m_Instance;
}
void CVirtualButton_Square::DeleteInstance() {
	if (m_Instance) {
		delete m_Instance;
		m_Instance = NULL;
	}
}

void CVirtualButton_Square::Init()//�������p
{
	vList_ButtonData.clear();
}
void CVirtualButton_Square::Step()//�X�V�Ȃǂ��s��
{
	//�}�E�X�̈ʒu���擾
	int Mouse_XPos = 0;
	int Mouse_YPos = 0;
	GetMousePoint(&Mouse_XPos, &Mouse_YPos);
	float MouseRadius = 2.0f;

	//���X�g���Ƀf�[�^���Ȃ������ꍇ�̓X���[
	if (vList_ButtonData.size() > 0) {
		//�T�C�Y���̃��[�v
		for (int i = 0; i < vList_ButtonData.size(); i++) {
			
			//�X�^���X���X�V
			vList_ButtonData[i].m_CurrentStance = vList_ButtonData[i].m_NextStance;

			//���X�^���X����UFALSE
			vList_ButtonData[i].m_NextStance = false;

			//�������Ă��邩�N���b�N����Ă���ꍇ
			if (CInput::IsMousePush(CInput::MOUSE_LEFT) || CInput::IsMouseKeep(CInput::MOUSE_LEFT)) {
				//�����蔻����Ƃ�
				if (IsHitSphereAndRectCollision((float)Mouse_XPos, (float)Mouse_YPos, MouseRadius,
					vList_ButtonData[i].m_fPos_X, vList_ButtonData[i].m_fPos_Y, vList_ButtonData[i].m_fSize_W, vList_ButtonData[i].m_fSize_H)) {
					
					//���X�^���X��TRUE
					vList_ButtonData[i].m_NextStance = true;
				
				}//�N���b�N���Ă��邩�������Ă��Ȃ����O�X�^���X��true�ȏꍇ������藼�X�^���X��false�ɂ���
				else if (vList_ButtonData[i].m_CurrentStance) {
					vList_ButtonData[i].m_CurrentStance = false;
					vList_ButtonData[i].m_NextStance = false;
				}
			}
		}
	}
}
void CVirtualButton_Square::Exit()//�O�̂��߂̔j���p
{

}
void CVirtualButton_Square::Draw()//�{�^���`��
{
	//���X�g���Ƀf�[�^���Ȃ������ꍇ�̓X���[
	if (vList_ButtonData.size() > 0) {
		//�T�C�Y���̃��[�v
		for (int i = 0; i < vList_ButtonData.size(); i++) {
			//�v�Z���₷���悤�Ƀo�b�t�@�ֈڂ�
			ButtonData ButtonBuf = vList_ButtonData[i];

			//�}�W�b�N�i���o�[�����邯�ǖ����Łc�c
			DrawBox(ButtonBuf.m_fPos_X, ButtonBuf.m_fPos_Y, ButtonBuf.m_fPos_X + ButtonBuf.m_fSize_W, ButtonBuf.m_fPos_Y + ButtonBuf.m_fSize_H,
				GetColor(ButtonBuf.m_ButtonColor_R - 32, ButtonBuf.m_ButtonColor_G - 32, ButtonBuf.m_ButtonColor_B - 32), 1);
			if (!vList_ButtonData[i].m_NextStance) {
				DrawBox(ButtonBuf.m_fPos_X + 8, ButtonBuf.m_fPos_Y + 8, ButtonBuf.m_fPos_X + ButtonBuf.m_fSize_W - 16, ButtonBuf.m_fPos_Y + ButtonBuf.m_fSize_H - 16,
					GetColor(ButtonBuf.m_ButtonColor_R, ButtonBuf.m_ButtonColor_G, ButtonBuf.m_ButtonColor_B), 1);
			}
		}
	}
}

int CVirtualButton_Square::RequestVirtualButton(float Pos_X, float Pos_Y, float Size_W, float Size_H, int _R, int _G, int _B)//�{�^���̃��N�G�X�g
{
	ButtonData DataBuf;

	DataBuf.ActiveID = vList_ButtonData.size();
	DataBuf.m_CurrentStance = false;
	DataBuf.m_NextStance = false;
	DataBuf.m_fPos_X = Pos_X;
	DataBuf.m_fPos_Y = Pos_Y;
	DataBuf.m_fSize_W = Size_W;
	DataBuf.m_fSize_H = Size_H;
	DataBuf.m_ButtonColor_R = _R;
	DataBuf.m_ButtonColor_G = _G;
	DataBuf.m_ButtonColor_B = _B;

	vList_ButtonData.push_back(DataBuf);

	return DataBuf.ActiveID;
}

//�������ꂽ
bool CVirtualButton_Square::IsKeyPush(int _ID)
{
	if (vList_ButtonData.size() - 1 < _ID) { return false; }

	if (!vList_ButtonData[_ID].m_CurrentStance && vList_ButtonData[_ID].m_NextStance) {
		return true;
	}
	return false;
}
//����������
bool CVirtualButton_Square::IsKeyKeep(int _ID)
{
	if (vList_ButtonData.size() - 1 < _ID) { return false; }

	if (vList_ButtonData[_ID].m_CurrentStance && vList_ButtonData[_ID].m_NextStance) {
		return true;
	}
	return false;
}
//�������Ƃ�
bool CVirtualButton_Square::IsKeyRelease(int _ID)
{
	if (vList_ButtonData.size() - 1 < _ID) { return false; }

	if (vList_ButtonData[_ID].m_CurrentStance && !vList_ButtonData[_ID].m_NextStance) {
		return true;
	}
	return false;
}
//�P���ɉ�����Ă邩�ۂ�
bool CVirtualButton_Square::IsKeyDown(int _ID)
{
	if (vList_ButtonData.size() - 1 < _ID) { return false; }

	if (vList_ButtonData[_ID].m_CurrentStance || vList_ButtonData[_ID].m_NextStance) {
		return true;
	}
	return false;
}