#include "TalkMainMob.h"
#include "../Engine/ImGuiSet.h"

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
TalkMainMob::TalkMainMob(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), isTalk_(false), toPlayer_(XMMatrixIdentity()), isLookPlayer_(false), hPict_(-1),
	pTalkImage_(nullptr)
{}

//�X�V�̑O�Ɉ�x�����Ă΂��
void TalkMainMob::ChildStartUpdate()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////

	hPict_ = Image::Load("Image/Text/Speak.png");
	assert(hPict_ >= ZERO);

	////////////�摜�̃g�����X�t�H�[���ݒ�///////////////

	ARGUMENT_INITIALIZE(tPict_.position_.x, GetPrivateProfilefloat("POSITION", "TalkX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tPict_.position_.y, GetPrivateProfilefloat("POSITION", "TalkY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tPict_.position_.z, 1.0f);

	ARGUMENT_INITIALIZE(tPict_.scale_.x, GetPrivateProfilefloat("SCALE", "TalkX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tPict_.scale_.y, GetPrivateProfilefloat("SCALE", "TalkY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tPict_.scale_.z, 1.0f);
}

//�X�V
void TalkMainMob::ChildUpdate()
{
	//Player�̕�������
	LookPlayer();

	//�����b���Ă����ԂȂ�
	if (isTalk_)
	{
		//�������Ō�܂ŕ`�悳��Ă��Ă���B�{�^�����������̂Ȃ�
		if (pTalkImage_->IsLastDraw() && Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
		{
			//�J����
			GameManager::GetpPlayer()->SetCamLong();

			//Player�����悤��
			GameManager::GetpPlayer()->SetAnimFlag(true);
			GameManager::GetpPlayer()->Enter();

			//�摜�폜
			pTalkImage_->KillMe();

			//�b���Ă��Ȃ���Ԃ�
			ARGUMENT_INITIALIZE(isTalk_, false);
		}
		else
		{
			//�J����
			GameManager::GetpPlayer()->SetCamShort();

			//Player�����̃I�u�W�F�N�g�̕������悤�ɂ���
			GameManager::GetpPlayer()->LookObject(transform_.position_, GameManager::GetpPlayer()->GetUp());

			//Player�����Ȃ��悤�ɂ���
			GameManager::GetpPlayer()->SetAnimFlag(false);
			GameManager::GetpPlayer()->Leave();
		}
	}
}

//�`��
void TalkMainMob::ChildDraw()
{
	//Player�Ƃ̋������w�苗���ȓ����b���Ă��Ȃ���ԂȂ�摜�\��
	if (IsInSpecifiedDistance() && !isTalk_)
	{
		Image::SetTransform(hPict_, tPict_);
		Image::Draw(hPict_);
	}
}

//Player�̕�������
void TalkMainMob::LookPlayer()
{
	//�������ł�Player�̕������Ă�����
	if (isLookPlayer_)
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

	//Player�Ƃ̋������w�苗���ȓ��Ȃ�Player�̕�������
	if (IsInSpecifiedDistance())
	{
		//�����b���Ă��Ȃ���Ԃ�B�{�^�����������̂Ȃ�
		if (!isTalk_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
		{
			//�b���Ă��鎞�̉摜�E�e�L�X�g�\��
			ARGUMENT_INITIALIZE(pTalkImage_,Instantiate<TalkImage>(GetParent()->GetParent()->GetParent()));

			//�b���Ă����Ԃ�
			ARGUMENT_INITIALIZE(isTalk_, true);
		}

		//Player�̕�������
		toPlayer_ = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_), up_);
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

		//��������true�ɂ���
		ARGUMENT_INITIALIZE(isLookPlayer_, true);
	}
}

//�w�苗�����ɓ����Ă��邩�ǂ���
bool TalkMainMob::IsInSpecifiedDistance()
{
	return (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < PLAYER_LOOK_DISTANCE);
}