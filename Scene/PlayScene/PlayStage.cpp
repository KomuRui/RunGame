#include "PlayStage.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Engine/CreateStage.h"

//�R���X�g���N�^
PlayStage::PlayStage(GameObject* parent)
	:Stage(parent, "PlayStage")
{
	//��p
	fieldAngle_ = 45;

	//���C�g�̋���
	lightIntensity_ = 4;
}

//������
void PlayStage::Initialize()
{

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//////�X�e�[�W�쐬
	CreateStage* pCreateStage = new CreateStage;
	//pCreateStage->LoadFileCreateStage(this, "Stage/Tutorial/StageInformation/TutorialStage2.txt");

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Base] = Model::Load("Stage/Play/StraightStage.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	//hModel_[PolyModel] = Model::Load("Stage/Play/StraightStage.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//���C�̔����Base�����ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_[Base], true);

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space], 0.5f);
	Model::SetBrightness(hModel_[Base], 1.0f);

	//PolyModel�𓧖��ɐݒ�(�����m�F���邽�߂����Ɏg������)
	//Model::SetAlpha(hModel_[PolyModel], 0);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(XMVectorSet(0, 1, 0, 0));

	//���C�g�̋���
	Light::SetPlayerIntensity(lightIntensity_);

	//3D�Ȃ̂�true�ɂ���
	threeDflag_ = true;

	//���̎g�p���Ă���̂�true
	circleFlag_ = true;

}

//�X�V
void PlayStage::Update()
{
	tSpace_.rotate_.y += 0.1;
}

//�`��
void PlayStage::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);
}

//���
void PlayStage::Release()
{
}
