#include "Block.h"
#include "../Engine/Model.h"

//�萔
namespace
{
	static const float INTERPOLATION_COEFFICIENT = 0.2f;	//��ԌW��
	static const float HIT_ADD_LENGTH = 0.5f;				//�����������ɉ��Z���钷��
	static const float TARGET_CHANGE_DISTANCE = 0.1f;       //�ړI�n��ς��鋗��
}

//�R���X�g���N�^
Block::Block(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), isHit_(false), hitMovePos_(ZERO, ZERO, ZERO), initialPos_(ZERO, ZERO, ZERO), roundTripEnd_(false)
{
}

//������
void Block::ChildInitialize()
{
	//�p����p
	BlockChildInitialize();
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void Block::ChildStartUpdate()
{
	//�����������̈ړ���|�W�V�����ݒ�(���a�����)
	hitMovePos_ = VectorToFloat3((XMLoadFloat3(&transform_.position_) + XMVector3Normalize(vNormal_) * HIT_ADD_LENGTH));

	//�����l�̃|�W�V�����ݒ�
	ARGUMENT_INITIALIZE(initialPos_,transform_.position_);

	//���g��ǉ�
	Model::SetBlockObj(hModel_, this);

	//�p����p
	BlockChildStartUpdate();
}

//�X�V
void Block::ChildUpdate()
{
	//�������Ă���Ȃ�֐��Ăяo��
	if (isHit_) HitToLowerPlayer();

	//�p����p
	BlockChildUpdate();
}

//�`��
void Block::ChildDraw()
{
	//�p����p
	BlockChildDraw();
}

//Player�������瓖���������̋���
void Block::HitToLowerPlayer()
{
	//��Ԃ��Ȃ���ړI�̃|�W�V�����܂ŕύX���Ă���
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&hitMovePos_), INTERPOLATION_COEFFICIENT));

	//������0.1��菬�����Ȃ玟�̖ړI�n��ݒ�
	if (RangeCalculation(transform_.position_, hitMovePos_) < TARGET_CHANGE_DISTANCE)
	{
		//�������I����Ă���Ȃ�
		if (roundTripEnd_)
		{
			//�ۑ����Ă���
			XMFLOAT3 KeepPos = initialPos_;

			//���ׂď�����Ԃɂ��Ă���
			ARGUMENT_INITIALIZE(transform_.position_,hitMovePos_);
			ARGUMENT_INITIALIZE(isHit_,false);
			ARGUMENT_INITIALIZE(initialPos_,hitMovePos_);
			ARGUMENT_INITIALIZE(hitMovePos_,KeepPos);
			ARGUMENT_INITIALIZE(roundTripEnd_,false);
		}
		else
		{
			//�ۑ����Ă���
			XMFLOAT3 KeepPos = hitMovePos_;

			//�ړI�n�ύX
			ARGUMENT_INITIALIZE(transform_.position_,hitMovePos_);
			ARGUMENT_INITIALIZE(hitMovePos_,initialPos_);
			ARGUMENT_INITIALIZE(initialPos_,KeepPos);
			ARGUMENT_INITIALIZE(roundTripEnd_,true);
		}
	}

	//�p����p�̋���
	BlockChildHitToLowerPlayer();
}

