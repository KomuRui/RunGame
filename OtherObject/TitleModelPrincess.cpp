#include "TitleModelPrincess.h"
#include "../Engine/Model.h"

//�萔
namespace
{
	static const int START_FRAME = 1;	  //�J�n�t���[��
	static const int END_FRAME = 60;      //�I���t���[��
	static const float ANIM_SPEED = 1.0f; //�A�j���[�V�����̍Đ����x
}

//�R���X�g���N�^
TitleModelPrincess::TitleModelPrincess(GameObject* parent)
	:GameObject(parent, "TitleModelPrincess"), hModel_(-1)
{
}

//������
void TitleModelPrincess::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load("Star_Main_Character2.fbx");
	assert(hModel_ >= ZERO);

	//�A�j���[�V����
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModelPrincess::StartUpdate()
{
}

//�X�V
void TitleModelPrincess::Update()
{
}

//�`��
void TitleModelPrincess::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModelPrincess::Release()
{
}
