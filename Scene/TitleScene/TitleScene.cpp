#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/CreateStage.h"
#include "../../OtherObject/TitleModel.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hModel_(-1)
{
}

//������
void TitleScene::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/Title/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	//�w�i�̃��f�����������点��
	Model::SetBrightness(hModel_, BRIGHTNESS);


	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(GetParent(), "Stage/Title/StageInformation/TitleScene1.txt");

	///////////////�J����///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);

}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void TitleScene::StartUpdate()
{
}

//�X�V
void TitleScene::Update()
{
	//�w�i��]������
	transform_.rotate_.y += RATATION_SPEED;

	//A��R�g���K�[���������ŃV�[���ړ�
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) && Input::GetPadTrrigerR())
	{
		//�V�[���ړ��̍ۂ̃G�t�F�N�g�\��
		TitleModel* pTitleModel = (TitleModel*)FindObject("TitleModel");

		//nullptr����Ȃ����
		if(pTitleModel !=nullptr)
			pTitleModel->SceneChangeEffect();

		//�G�t�F�N�g���L�������Ƃ��ɃV�[���ڍs�������̂Ń^�C�����\�b�h���g���Ďw�肵�����Ԃ�����������ɌĂ�
		SetTimeMethod(0.5f);
	}
}

//�`��
void TitleScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void TitleScene::Release()
{
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void TitleScene::TimeMethod()
{
	//���[�h�̎��̕`���ݒ肵�Ȃ�
	GameManager::GetpSceneManager()->SetLoadDrawFlag(false);
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_USER_SELECT);
}