#pragma once
#include "Engine/GameObject.h"
#include <vector>

//�O���錾
class Block;

//�e�X�e�[�W�N���X�̂��ƂƂȂ�N���X
class Stage : public GameObject
{
protected:

	/////////////////////////Stage�ɕK�v�ȏ��/////////////////////////////////
	
	//���f���̎��
	enum StageCategory
	{
		Base = 0,      //�X�e�[�W�̃��f��
		Space,		   //�w�i�̉F�����f��
		PolyModel,     //���̂ɕ��̂��悹�邽�߂ɋ^�����f��
		MAX
	};

	////2D�̍ۂ̃u���b�N�Ƃ̓����蔻��Ɏg��
	enum BlockHitTest2D
	{
		Right = 0,     //�E
		Left,          //��
		Under,         //��
		Top,           //��
	};

	//���f���ԍ�
	int hModel_[MAX];

	//�w�i���f���p�̃g�����X�t�H�[��
	Transform tSpace_;

	//��p
	int fieldAngle_;

	//���C�g�̋���
	int lightIntensity_;

	/////////////////////////���̃N���X�ŕK�v�ȏ��/////////////////////////////////

	//Player�̏����ʒu
	XMFLOAT3 pos_;

	//���[�v�̈ړ���
	XMFLOAT3 warpPos_;

	//3D�̃��f�����g�p���Ă��邩�ǂ���
	bool threeDflag_;

	//���̃��f�����g�p���Ă��邩�ǂ���
	bool circleFlag_;

	//�u���b�N��ۑ����Ă���Vector(��Ƀu���b�N�Ƃ̓����蔻����s�����߂Ɏg��)
	std::vector<Block*> tBlock_;

public:

	//�R���X�g���N�^
	Stage(GameObject* parent,std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	virtual void Initialize() override {};

	//�X�V�̑O�Ɉ��Ă΂��֐�
	virtual void StartUpdate() override {};

	//�X�V
	virtual void Update() override {};

	//�`��
	virtual void Draw() override {};

	//�J��
	virtual void Release() override {};

	//////////////////////////////�֐�////////////////////////////////////
	
	//�����Ƀu���b�N�����邩�ǂ���,������������d�Ȃ��Ă��镪���炷
	//����:status 0:�E 1:�� 2:�� 3:�� 
	bool IsBlock(XMFLOAT3* pos, int status);

	////////////////////////�Q�b�g�E�Z�b�g�֐�///////////////////////////

	//���f���ԍ��̃Q�b�g�֐�
	int GethModel() { return hModel_[Base]; }

	//���̂ɕ��̂��悹�邽�߂ɋ^�����f���ԍ��̃Q�b�g�֐�
	int GetPolyModell() { return hModel_[PolyModel]; }

	//Pos�̃Q�b�g�֐�
	XMFLOAT3 GetPos() { return pos_; }

	//���[�v�̈ړ���擾
	XMFLOAT3 GetWarpTargetPos() { return warpPos_; }

	//3D�̓���������������
	bool GetthreeDflag() { return threeDflag_; }

	//���̏�œ���������������
	bool GetCircleflag() { return circleFlag_; }
};

