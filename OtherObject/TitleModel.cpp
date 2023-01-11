#include "TitleModel.h"
#include "../Engine/Model.h"

//�萔
namespace
{
	static const XMVECTOR MIN_SCALE = { 0.2f,0.2f,1.0f };    //�Œ�g�嗦
	static const XMVECTOR MAX_SCALE = { 0.25f,0.25f,1.0f };  //�ō��g�嗦
	static const float INTERPOLATION_FACTOR = 0.03f;      //��ԌW��
	static const float CHANGE_TARGET_DISTANCE = 0.01f;    //�^�[�Q�b�g�ύX����Ƃ��̋���
}

//�R���X�g���N�^
TitleModel::TitleModel(GameObject* parent)
	:GameObject(parent,"TitleModel"),hModel_(-1), beforeScale_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)), targetScale_(XMVectorSet(0, 0, 0, 0)),
	pSceneChabgeEffect_(nullptr)
{
}

//������
void TitleModel::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/Title/Model/TitleModel.fbx");
	assert(hModel_ >= ZERO);


	///////////////�G�t�F�N�g�ݒ�///////////////////

   //�G�t�F�N�g�o�����߂ɕK�v�ȃN���X
	pSceneChabgeEffect_ = Instantiate<Particle>(this);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModel::StartUpdate()
{
	//��Ԃ���O�̊g�嗦�ۑ�
	ARGUMENT_INITIALIZE(beforeScale_, MIN_SCALE);

	//���̖ڕW�Ƃ���g�嗦�̕ۑ�
	ARGUMENT_INITIALIZE(targetScale_, MAX_SCALE);
}

//�X�V
void TitleModel::Update()
{
	//�g�嗦���Ԃ��Ȃ���ς��Ă���
	XMStoreFloat3(&transform_.scale_,XMVectorLerp(XMLoadFloat3(&transform_.scale_), targetScale_, INTERPOLATION_FACTOR));

	//������0.01���Z���̂Ȃ�
	if (RangeCalculation(transform_.scale_, VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
	{
		//�^�[�Q�b�g����
		std::swap(beforeScale_, targetScale_);
	}
}

//�`��
void TitleModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModel::Release()
{
}

//�V�[���ύX�G�t�F�N�g
void TitleModel::SceneChangeEffect()
{
	EmitterData data;
	data.textureFileName = "Cloud.png";
	data.position = transform_.position_;
	data.delay = 0;
	data.number = 20;
	data.lifeTime = 150;
	data.dir = XMFLOAT3(0, 1, 0);
	data.dirErr = XMFLOAT3(90, 90, 90);
	data.speed = 0.05f;
	data.speedErr = 0.8;
	data.size = XMFLOAT2(5, 5);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.05, 1.05);
	data.color = XMFLOAT4(1, 1, 1, 1);
	data.deltaColor = XMFLOAT4(-0.03, -0.03, 0, -1.0 / 50);
	pSceneChabgeEffect_->Start(data);
}