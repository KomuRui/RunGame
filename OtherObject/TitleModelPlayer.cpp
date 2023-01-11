#include "TitleModelPlayer.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"

//�萔
namespace
{
	static const int START_FRAME = 1;	  //�J�n�t���[��
	static const int END_FRAME = 60;      //�I���t���[��
	static const float ANIM_SPEED = 1.0f; //�A�j���[�V�����̍Đ����x
}

//�R���X�g���N�^
TitleModelPlayer::TitleModelPlayer(GameObject* parent)
	:GameObject(parent, "TitleModelPlayer"), hModel_(-1)
{
}

//������
void TitleModelPlayer::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= ZERO);

	//�A�j���[�V����
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModelPlayer::StartUpdate()
{
}

//�X�V
void TitleModelPlayer::Update()
{
}

//�`��
void TitleModelPlayer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModelPlayer::Release()
{
}
