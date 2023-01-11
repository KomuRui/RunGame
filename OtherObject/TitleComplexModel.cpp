#include "TitleComplexModel.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//�萔
namespace
{
	static const float SPEED = 0.1f;               //�X�s�[�h
	static const float VIBRATION_INTENSITY = 0.2f; //�U���̋���
	static const float LIMIT_Y = -20.0f;           //y���̃|�W�V�������E�l
	static const float ATTENUATION = 0.003f;       //�����l
}

//�R���X�g���N�^
TitleComplexModel::TitleComplexModel(GameObject* parent)
	:GameObject(parent, "TitleComplexModel"), hModel_(-1)
{
}

//������
void TitleComplexModel::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load("Stage/Title/Model/TitleComplexModel.fbx");
	assert(hModel_ >= ZERO);

	//�^�C�g����ʂȂǕ\�����邽�߂ɐ�Ƀt�@�C�����[�h���Ă���
	pCreateStage = new CreateStage;
	pCreateStage->LoadFile(GetParent(), "Stage/Title/StageInformation/TitleScene2.txt");
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleComplexModel::StartUpdate()
{
}

//�X�V
void TitleComplexModel::Update()
{
	//y���̃|�W�V���������X�ɉ����Ă���
	transform_.position_.y -= SPEED;

	//y��-20��艺�ɗ�������
	if (transform_.position_.y < LIMIT_Y)
	{
		//�J�����U��
		Camera::SetCameraVibration(VIBRATION_INTENSITY, ATTENUATION);

		//�^�C�g���Ȃǂ�\��
		pCreateStage->LoadFileBasedCreateStage();

		//���g���폜
		KillMe();
	}
}

//�`��
void TitleComplexModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleComplexModel::Release()
{
}
