#include "Coin.h"
#include "../Manager/CoinManager/CoinManager.h"

//�萔
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.08f;      //��]����Ƃ��̉��Z����p�x
	static const float BLOCK_ADD_ROTATION_ANGLE = 0.3f; //��]����Ƃ��̉��Z����p�x
	static const float COLLIDER_POS_Y = 1.0f;           //�R���C�_�[��Y���̃|�W�V����
	static const float COLLIDER_RADIUS = 1.0f;          //�R���C�_�[�̔��a
	static const float UP_SPEED = 0.1f;                 //�R�C������ɍs���Ƃ��̑��x
	static const float KILL_CALL_TIME_METHOD = 0.1f;    //�폜�^�C�����\�b�h���ĂԎ���
	static const float SIGN_CALL_TIME_METHOD = 0.5f;    //�����^�C�����\�b�h���ĂԎ���
}

//�R���X�g���N�^
Coin::Coin(GameObject* parent, std::string modelPath, std::string name)
	: Mob(parent, modelPath, name),type_(RotationType), sign_(1), timeMethodStatus_(SignChange)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void Coin::ChildStartUpdate()
{
	//�R���C�_�[�ǉ�
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_RADIUS * transform_.scale_.y);
	AddCollider(collision);
}

void Coin::ChildUpdate()
{
	//�^�ɂ���ď����𕪂���
	switch (type_)
	{
	//��]
	case RotationType:

		Rotation();
		break;

	//�u���b�N����R�C���o��
	case BlockCoinType:

		Rotation();
		BlockCoinBehavior();
		break;

	//���̑��͏������Ȃ�
	default:
		break;
	}


}

//�u���b�N����R�C���o�����̋���
void Coin::BlockCoinBehavior()
{
	//������ɍs��
	transform_.position_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(vNormal_) * UP_SPEED * sign_));

	//��Ԃɂ���ČĂԃ��\�b�h�ύX
	if (!GetTimeMethod() && timeMethodStatus_ == SignChange)
		SetTimeMethod(SIGN_CALL_TIME_METHOD);
	else if (!GetTimeMethod() && timeMethodStatus_ == Kill)
		SetTimeMethod(KILL_CALL_TIME_METHOD);
}

//��]
void Coin::Rotation()
{
	//���ʂ̉�]�Ƃ���ȊO�̎��̉�]�̑��x��ς���
	if(type_ == RotationType)
		angle_ += ADD_ROTATION_ANGLE;
	else
		angle_ += BLOCK_ADD_ROTATION_ANGLE;

	//Angle��360�܂ł�������0�ɖ߂�
	if (angle_ > TWOPI_DEGREES)
		angle_ = ZEROPI_DEGREES;
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void Coin::TimeMethod()
{
	//�����`�F���W��ԂȂ�
	if (timeMethodStatus_ == SignChange)
	{
		//�����`�F���W
		sign_ *= -2;

		//��ԕύX
		ARGUMENT_INITIALIZE(timeMethodStatus_, Kill);
	}
	//���g�폜��ԂȂ�
	else if (timeMethodStatus_ == Kill)
	{
		//���L�R�C���̗ʂ𑝂₷(�R�C���̑傫���ɂ���đ��₷�ʕς���)
		CoinManager::AddCoin(transform_.scale_.y);

		//���g�̍폜
		KillMe();
	}
}

//�����蔻��
void Coin::OnCollision(GameObject* pTarget)
{
	//Player�ȊO�Ȃ牽�����Ȃ�
	if (pTarget->GetObjectName() != "Player")
		return;

	//���L�R�C���̗ʂ𑝂₷(�R�C���̑傫���ɂ���đ��₷�ʕς���)
	CoinManager::AddCoin(transform_.scale_.y);

	//���g�̍폜
	KillMe();
}
