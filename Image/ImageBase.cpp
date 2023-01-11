#include "ImageBase.h"
#include "../Engine/Image.h"

//�R���X�g���N�^
ImageBase::ImageBase(GameObject* parent, std::string modelPath, std::string name)
	: GameObject(parent, name), hPict_(-1), ModelNamePath_(modelPath)
{
}

//������
void ImageBase::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////
	
	hPict_ = Image::Load(ModelNamePath_);
	assert(hPict_ >= 0);
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void ImageBase::StartUpdate()
{
}

//�X�V
void ImageBase::Update()
{
}

//�`��
void ImageBase::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//���
void ImageBase::Release()
{
}
