#include "CreateStage.h"
#include "../Gimmick/Coin.h"
#include "../Block/ItemBlock.h"
#include "../Enemy/Enemy.h"
#include "../Block/BrickBlock.h"
#include "../Block/NormalBlock.h"
#include "../Block/TransparentBlock.h"
#include "../Mob/MainMob.h"
#include "../Mob/TalkMainMob.h"
#include "../Gimmick/Signboard.h"
#include "Light.h"
#include "CameraTransitionObject.h"
#include "../OtherObject/TitleModel.h"
#include "../OtherObject/TitleModelPlayer.h"
#include "../OtherObject/TitleModelPrincess.h"
#include "../OtherObject/TitleComplexModel.h"
#include "../Image/ImageBase.h"
#include "../Image/TitleStartImage.h"
#include "GameObject.h"
#include <fstream>

//�R���X�g���N�^
CreateStage::CreateStage()
	:createShineController_(false)
{
}

//�I�u�W�F�N�g�쐬
void CreateStage::CreateObject(GameObject* parent, std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos)
{
	/////////////////////Mob///////////////////////

	if (inName == "Mob")
	{
		Mob* pNewObject = new Mob(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "MainMob" || inName == "2DTalkMainMob")
	{
		MainMob* pNewObject = new MainMob(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->SetAngle(t.rotate_.y);
		pNewObject->Initialize();

		//�����b���Ȃ�
		if (inName == "2DTalkMainMob")
			pNewObject->SetTalk(true);
	}
	if (inName == "TalkMainMob")
	{
		TalkMainMob* pNewObject = new TalkMainMob(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->SetAngle(t.rotate_.y);
		pNewObject->Initialize();
	}

	/////////////////////Image///////////////////////

	if (inName == "ImageBase")
	{
		ImageBase* pNewObject = new ImageBase(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "TitleStartImage")
	{
		TitleStartImage* pNewObject = new TitleStartImage(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}

	/////////////////////OtherObject///////////////////////

	if (inName == "TitleModel")
	{
		TitleModel* pNewObject = new TitleModel(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "TitleModelPlayer")
	{
		TitleModelPlayer* pNewObject = new TitleModelPlayer(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "TitleModelPrincess")
	{
		TitleModelPrincess* pNewObject = new TitleModelPrincess(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "TitleComplexModel")
	{
		TitleComplexModel* pNewObject = new TitleComplexModel(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}

	/////////////////////Camera////////////////////////

	if (inName == "Camera")
	{
		//�J������������ϐ��p��
		StageCameraTransition information;

		//�e��񏉊���
		information.CameraPosition = camPos;
		information.CameraTarget = t.rotate_;
		information.CollisionSize = t.scale_;

		//�R���X�g���N�^�Ă�
		CameraTransitionObject* pNewObject = new CameraTransitionObject(parent, information);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}

		//��]�Ɗg���0�ɏ���������
		ARGUMENT_INITIALIZE(t.rotate_, XMFLOAT3(0, 0, 0));
		ARGUMENT_INITIALIZE(t.scale_, XMFLOAT3(0, 0, 0));

		pNewObject->SetTransform(t);
		pNewObject->Initialize();

	}

	/////////////////////Light/////////////////////////

	if (inName == "Light")
	{
		Light::CreateLight(XMFLOAT4(t.position_.x, t.position_.y, t.position_.z, 0), t.scale_.x);
	}

	/////////////////////Gimmick///////////////////////

	if (inName == "Coin")
	{
		Coin* pNewObject = new Coin(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "Signboard" || inName == "LookCamSignboard")
	{
		Signboard* pNewObject = new Signboard(parent, ModelPathName, inName);

		//�ŔȂ̂ŃV�[���}�l�[�W���[�̎q�ɂ���
		GameManager::GetpSceneManager()->PushBackChild(pNewObject);

		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//�����J�����̕�������Ȃ�
		if (inName == "LookCamSignboard")
			pNewObject->SetLookCamera(true);
	}

	/////////////////////Block///////////////////////

	if (inName == "ItemBlock" || inName == "ItemBlock1")
	{

		ItemBlock* pNewObject = new ItemBlock(parent, ModelPathName, "ItemBlock");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//��]����悤�ɐݒ�
		if (inName == "ItemBlock1")pNewObject->SetType(1);

		//�u���b�N�Ȃ̂Œǉ�
		tBlock_.push_back(pNewObject);
	}
	if (inName == "BrickBlock")
	{

		BrickBlock* pNewObject = new BrickBlock(parent, ModelPathName, "BrickBlock");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//�u���b�N�Ȃ̂Œǉ�
		tBlock_.push_back(pNewObject);
	}
	if (inName == "NormalBlock")
	{

		NormalBlock* pNewObject = new NormalBlock(parent, ModelPathName, "NormalBlock");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//�u���b�N�Ȃ̂Œǉ�
		tBlock_.push_back(pNewObject);
	}
	if (inName == "TransparentBlock")
	{

		TransparentBlock* pNewObject = new TransparentBlock(parent, ModelPathName, "TransparentBlock");

		//�����Ȃ̂ŃV�[���}�l�[�W���̎q���ɂ���
		GameManager::GetpSceneManager()->PushBackChild(pNewObject);
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//�u���b�N�Ȃ̂Œǉ�
		tBlock_.push_back(pNewObject);
	}

	/////////////////////Enemy///////////////////////

	if (inName == "Enemy")
	{
		Enemy* pNewObject = new Enemy(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
}

//�e�X�e�[�W�̃t�@�C�����[�h���X�e�[�W���쐬���Ă����
void CreateStage::LoadFileCreateStage(GameObject* parent, std::string filename)
{
	//�t�@�C���I�[�v��
	const char* fileName = filename.c_str();
	std::ifstream ifs(fileName);

	//�f�[�^��1������ϐ�
	std::string buf;

	//�K�v�Ȋe�p�����[�^��ۑ�����p�̕�����z��(pos.x,pos,y,pos.z�Ƃ�)
	std::string data[14] = { "" };

	//,�̐�
	int sum = 0;

	//�����܂œǂ�
	while (!ifs.eof())
	{
		//1��buf�Ɋi�[
		std::getline(ifs, buf);

		//buf�̃T�C�Y�����[�v
		for (int i = 0; i < buf.size(); i++)
		{
			//�e�p�����[�^�������data�Ɋi�[���Ă���
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//�e�p�����[�^��ϐ��Ɋi�[���Ă���
		std::string ModelPathName = data[0];
		std::string Name = data[1];

		Transform t;

		t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
		t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
		t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };

		//�J�����̃|�W�V���������ϐ�
		XMFLOAT3 camPos;

		//�J�����̃|�W�V������K�v�Ƃ���I�u�W�F�N�g�Ȃ�
		if (Name.find("Camera") != std::string::npos || Name == "ShineLight")
			camPos = { std::stof(data[11]),std::stof(data[12]),std::stof(data[13]) };
		//����ȊO�͎g��Ȃ��̂�0�ɂ��Ă���
		else
			camPos = { 0,0,0 };

		//�p�����[�^����ɃI�u�W�F�N�g�쐬
		CreateObject(parent,ModelPathName, Name, t, camPos);

		//���ׂď�����
		for (int i = 0; i < 14; i++)
		{
			data[i] = "";
		}
		sum = 0;
	}


}

//�e�X�e�[�W�̃t�@�C�����[�h�������Ă����
void CreateStage::LoadFile(GameObject* parent, std::string filename)
{
	//�t�@�C���I�[�v��
	const char* fileName = filename.c_str();
	std::ifstream ifs(fileName);

	//�f�[�^��1������ϐ�
	std::string buf;

	//�K�v�Ȋe�p�����[�^��ۑ�����p�̕�����z��(pos.x,pos,y,pos.z�Ƃ�)
	std::string data[14] = { "" };

	//,�̐�
	int sum = 0;

	//�����܂œǂ�
	while (!ifs.eof())
	{
		//1��buf�Ɋi�[
		std::getline(ifs, buf);

		//buf�̃T�C�Y�����[�v
		for (int i = 0; i < buf.size(); i++)
		{
			//�e�p�����[�^�������data�Ɋi�[���Ă���
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//�����i�[���Ă����ϐ�
		CreateStageInfo info;


		//�e�p�����[�^��ϐ��Ɋi�[���Ă���
		info.parent = parent;
		info.ModelPathName = data[0];
		info .inName = data[1];

		Transform t;

		info.t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
		info.t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
		info.t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };


		//�J�����̃|�W�V������K�v�Ƃ���I�u�W�F�N�g�Ȃ�
		if (info.inName.find("Camera") != std::string::npos || info.inName == "ShineLight")
			info.camPos = { std::stof(data[11]),std::stof(data[12]),std::stof(data[13]) };
		//����ȊO�͎g��Ȃ��̂�0�ɂ��Ă���
		else
			info.camPos = { 0,0,0 };

		info_.push_back(info);

		//���ׂď�����
		for (int i = 0; i < 14; i++)
		{
			data[i] = "";
		}
		sum = 0;
	}

}

//LoadFile���g���ă��[�h�����t�@�C�������ɃX�e�[�W���쐬
void CreateStage::LoadFileBasedCreateStage()
{
	for (auto i = info_.begin(); i != info_.end(); i++)
	{
		CreateObject((*i).parent, (*i).ModelPathName, (*i).inName, (*i).t, (*i).camPos);
	}
}