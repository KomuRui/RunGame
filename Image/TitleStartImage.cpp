#include "TitleStartImage.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"

//�萔
namespace
{
	const XMFLOAT3 BEFORE_SCALE = { 1.0,1.0,1.0 }; //�ύX�O�̊g�嗦
	const XMFLOAT3 AFTER_SCALE = { 1.1,1.1,1.1 };  //�ύX��̊g�嗦
}

//�R���X�g���N�^
TitleStartImage::TitleStartImage(GameObject* parent, std::string modelPath, std::string name)
	: GameObject(parent, name), ModelNamePath_(modelPath), hPict_Default_(-1), hPict_A_Select_(-1), hPict_RT_Select_(-1), hPict_All_Select_(-1)
{
}

//������
void TitleStartImage::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////

	//�f�t�H���g
	hPict_Default_ = Image::Load(ModelNamePath_);
	assert(hPict_Default_ >= ZERO);

	//A��������Ă�Ƃ�
	hPict_A_Select_ = Image::Load("Image/Title/Start_A_Select.png");
	assert(hPict_A_Select_ >= ZERO);

	//RT��������Ă�Ƃ�
	hPict_RT_Select_ = Image::Load("Image/Title/Start_RT_Select.png");
	assert(hPict_RT_Select_ >= ZERO);

	//���ׂĂ�������Ă�Ƃ�
	hPict_All_Select_ = Image::Load("Image/Title/Start_ALL_Select.png");
	assert(hPict_All_Select_ >= ZERO);
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void TitleStartImage::StartUpdate()
{
}

//�X�V
void TitleStartImage::Update()
{
	//����A��RT��������Ă�Ȃ�
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) || Input::GetPadTrrigerR())
	{
		ARGUMENT_INITIALIZE(transform_.scale_, AFTER_SCALE);
	}
	else
		ARGUMENT_INITIALIZE(transform_.scale_, BEFORE_SCALE);
}

//�`��
void TitleStartImage::Draw()
{
	//����A��RT��������������Ă�Ȃ�
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) && Input::GetPadTrrigerR())
	{
		Image::SetTransform(hPict_All_Select_, transform_);
		Image::Draw(hPict_All_Select_);
	}
	//����A��������Ă���Ȃ�
	else if (Input::IsPadButton(XINPUT_GAMEPAD_A))
	{
		Image::SetTransform(hPict_A_Select_, transform_);
		Image::Draw(hPict_A_Select_);
	}
	//����RT��������Ă���Ȃ�
	else if (Input::GetPadTrrigerR())
	{
		Image::SetTransform(hPict_RT_Select_, transform_);
		Image::Draw(hPict_RT_Select_);
	}
	//��������������Ă��Ȃ��Ȃ�
	else
	{
		Image::SetTransform(hPict_Default_, transform_);
		Image::Draw(hPict_Default_);
	}
	
}

//���
void TitleStartImage::Release()
{
}
