#pragma once
#include "Transform.h"
#include "GameObject.h"
#include "../Block/Block.h"

//�e�X�e�[�W�ŃJ�����J�ڂ���Ƃ��̕K�v�ȏ��
struct StageCameraTransition
{
	XMFLOAT3 CameraPosition;  //�J�����̃|�W�V����
	XMFLOAT3 CameraTarget;    //�J�����̃^�[�Q�b�g
	XMFLOAT3 CollisionSize;   //�R���C�_�[�̃T�C�Y
};

//�e�V�[���̃X�e�[�W����Ă����
class CreateStage
{
	//�X�e�[�W�쐬�ɕK�v�ȏ��
	struct CreateStageInfo
	{
		GameObject* parent;         //�e�I�u�W�F�N�g
		std::string ModelPathName;  //���f���p�X�l�[��
		std::string inName;         //�I�u�W�F�N�g�̖��O
		Transform   t;              //�g�����X�t�H�[��
		XMFLOAT3    camPos;         //�J�����̃|�W�V����(�K�v�ȃI�u�W�F�N�g�ƕK�v����Ȃ��I�u�W�F�N�g������)
	};

	//���郉�C�g�̃R���g���[���[����x�������Ȃ��̂�flag�ō�������ǂ����m�F����
	bool createShineController_;

	//�t�@�C�����[�h���ē�������ۑ����Ă���(LoadFile�Ƃ����֐��Ŏg��)
	//�D���ȃ^�C�~���O�ŃX�e�[�W����ł���悤��
	std::vector<CreateStageInfo> info_;

	//�e�X�e�[�W�̃u���b�N�̃g�����X�t�H�[����ۑ�
	std::vector<Block*> tBlock_;

public:

	//�R���X�g���N�^
	CreateStage();

	//�I�u�W�F�N�g�쐬
	void CreateObject(GameObject* parent,std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos);

	//�e�X�e�[�W�̃t�@�C�����[�h���X�e�[�W���쐬���Ă����
	void LoadFileCreateStage(GameObject* parent, std::string filename);

	//�e�X�e�[�W�̃t�@�C�����[�h�������Ă����
	void LoadFile(GameObject* parent, std::string filename);

	//LoadFile���g���ă��[�h�����t�@�C�������ɃX�e�[�W���쐬
	void LoadFileBasedCreateStage();

	//�e�u���b�N�̃|�C���^�Q�b�g
	std::vector<Block*> GetTransformBlock() { return tBlock_; }
};
