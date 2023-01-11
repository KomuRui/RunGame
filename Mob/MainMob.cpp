#include "MainMob.h"
#include "../Engine/ImGuiSet.h"
#include "../Image/TalkImage.h"

//�萔
namespace
{
	////////////////////////////�A�j���[�V����////////////////////////////

	static const int START_FRAME = 0;	  //�J�n�t���[��
	static const int END_FRAME = 120;     //�I���t���[��
	static const float ANIM_SPEED = 1.0f; //�A�j���[�V�����̍Đ����x

	////////////////////////////���̑�////////////////////////////

	static const float PLAYER_LOOK_DISTANCE = 8; //Player�̕����������̋���
}

//�R���X�g���N�^
MainMob::MainMob(GameObject* parent, std::string modelPath, std::string name) 
	:Mob(parent, modelPath, name),isTalk_(false),toPlayer_(XMMatrixIdentity()), isLookPlayer_(false)
{}

//�X�V�̑O�Ɉ�x�����Ă΂��
void MainMob::ChildStartUpdate()
{
	//�����b���Ȃ�
	if (isTalk_)
		Instantiate<TalkImage>(GetParent()->GetParent()->GetParent());
	else
	{
		//�A�j���[�V����
		Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
		Model::SetAnimFlag(hModel_, true);
	}		
}

//�X�V
void MainMob::ChildUpdate()
{
	//�����b���Ȃ�Player�̕�������
	if (isTalk_)
		LookPlayer();
}

//�`��
void MainMob::ChildDraw() 
{

}

//Player�̕�������
void MainMob::LookPlayer()
{
	//�������ł�Player�̕������Ă�����
	if(isLookPlayer_)
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

	//Player�Ƃ̋�����8�ȓ��Ȃ�Player�̕�������
	if (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < PLAYER_LOOK_DISTANCE)
	{
		toPlayer_ = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_), up_);
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

		ARGUMENT_INITIALIZE(isLookPlayer_, true);
	}
}