#include "Coin.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"

//�萔
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.08f;		    //��]����Ƃ��̉��Z����p�x
	static const float BLOCK_ADD_ROTATION_ANGLE = 0.3f;		//��]����Ƃ��̉��Z����p�x
	static const float COLLIDER_POS_Y = 1.0f;				//�R���C�_�[��Y���̃|�W�V����
	static const float COLLIDER_RADIUS = 1.0f;			    //�R���C�_�[�̔��a
	static const float UP_SPEED = 0.1f;					    //�R�C������ɍs���Ƃ��̑��x
	static const float KILL_CALL_TIME_METHOD = 0.1f;	    //�폜�^�C�����\�b�h���ĂԎ���
	static const float SIGN_CALL_TIME_METHOD = 0.5f;	    //�����^�C�����\�b�h���ĂԎ���
	static const float RAY_HIT_DISTANCE = 1.0f;				//���C�̓�����������
	static const float GRAVITY_STRENGTH = 0.083f;           //�d�͂̋���
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //�@�����Ԃ���Ƃ��̕�ԌW��
	static const int MAX_NORMAL_RADIANS = 50;               //�@���Ƃ̍ő�p�x
}

//�R���X�g���N�^
Coin::Coin(GameObject* parent, std::string modelPath, std::string name)
	: Mob(parent, modelPath, name),type_(RotationType), sign_(1), timeMethodStatus_(SignChange), effectNumber_(-1)
{
}

//�R���X�g���N�^
Coin::Coin(GameObject* parent)
	: Mob(parent, "Stage/Gimmick/Coin.fbx", "Coin"), type_(RotationType), sign_(1), timeMethodStatus_(Kill), effectNumber_(-1)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void Coin::ChildStartUpdate()
{
	//���邳
	Model::SetBrightness(hModel_, 1.0f);

	//�G�t�F�N�g
	ARGUMENT_INITIALIZE(effectNumber_, CoinEffectManager::Add(this));


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


	//�������Ŏg���̂Ő�ɐ錾���Ă���
	RayCastData downData;
	downData.start = transform_.position_;         //���C�̃X�^�[�g�ʒu
	downData.dir = VectorToFloat3(down_);          //���C�̕���
	Model::AllRayCast(hGroundModel_, &downData);   //���C�𔭎�(All)

	 //�^���̖@���𒲂ׂăL�����̏㎲�����肷��
	CheckUnderNormal(downData);

	//�X�e�[�W�Ƃ̓����蔻��
	StageRayCast(downData);

	//Player�����ɍs�����玀�S
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5 && this->IsVisibled())
		KillMe();
}

//�^���̖@���𒲂ׂăL�����̏㎲�����肷��
void Coin::CheckUnderNormal(const RayCastData& data)
{
	if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
	{
		//���̃L�����̏�x�N�g��vNormal�Ɖ��̖@���̓��ς����߂�
		float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

		//�p�x��50�x�ȓ��Ɏ��܂��Ă�����(�ǂƂ��ɏ�点�Ȃ�����)
		if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
		{
			//������ƕ��
			vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
			down_ = -vNormal_;
		}
	}
}

//���C(�~�p)
void Coin::StageRayCast(const RayCastData& data)
{
	//�O
	RayCastData straightData;
	straightData.start = transform_.position_;                                                          //���C�̃X�^�[�g�ʒu
	straightData.dir = VectorToFloat3(XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_));  //���C�̕���
	Model::AllRayCast(hGroundModel_, &straightData);                                                    //���C�𔭎�

	//////////////////////////////�͂ݏo������������//////////////////////////////////////

	//�O�̋�����1.0�ȉ��Ȃ�
	if (straightData.dist <= RAY_HIT_DISTANCE)
	{
		XMVECTOR dis = { ZERO,ZERO,straightData.dist };
		dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));

		//�A�j���[�V������~
		Model::SetAnimFlag(hModel_, false);
	}

	//���̋�����1.0�ȏォ�d�͓K�p����Ȃ�
	if (data.dist >= RAY_HIT_DISTANCE)
	{
		transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((-vNormal_) * GRAVITY_STRENGTH));
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

//�J��
void Coin::ChildRelease()
{
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
		//���g�̍폜
		KillMe();
	}
}

//�����蔻��
void Coin::OnCollision(GameObject* pTarget)
{
	//Player�ȊO�Ȃ牽�����Ȃ�
	if (pTarget->GetObjectName() != "Player" || !this->IsVisibled())
		return;

	//�G�t�F�N�g�\��
	CoinEffectManager::HitEffect(effectNumber_);

	//���L�R�C���̗ʂ𑝂₷(�R�C���̑傫���ɂ���đ��₷�ʕς���)
	CoinManager::AddCoin(transform_.scale_.y);

	//�`�悵�Ȃ�
	Invisible();

	//1�b��Ɏ��g���폜
	SetTimeMethod(1.0f);
}
