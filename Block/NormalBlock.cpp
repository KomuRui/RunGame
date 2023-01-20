#include "NormalBlock.h"

//�萔
namespace
{
	static const float RAY_HIT_DISTANCE = 1.0f;				//���C�̓�����������
	static const float GRAVITY_STRENGTH = 0.083f;           //�d�͂̋���
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //�@�����Ԃ���Ƃ��̕�ԌW��
	static const float ADD_ROTATION_VALUE = 0.05f;          //��]����Ƃ��̉��Z����p�x
	static const int MAX_NORMAL_RADIANS = 50;               //�@���Ƃ̍ő�p�x
}

//�R���X�g���N�^
NormalBlock::NormalBlock(GameObject* parent)
	:Block(parent, "Stage/Block/Normalblock.fbx", "NormalBlock"), rotationAngle_(ZERO){}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void NormalBlock::BlockChildStartUpdate()
{
	///////////////���邳///////////////////

	Model::SetBrightness(hModel_, 1.0f);
}

//�X�V
void NormalBlock::BlockChildUpdate()
{
	
	//�������Ŏg���̂Ő�ɐ錾���Ă���
	RayCastData downData;
	downData.start = transform_.position_;         //���C�̃X�^�[�g�ʒu
	downData.dir = VectorToFloat3(down_);          //���C�̕���
	Model::AllRayCast(hGroundModel_, &downData);   //���C�𔭎�(All)

	 //�^���̖@���𒲂ׂăL�����̏㎲�����肷��
	CheckUnderNormal(downData);

	//�X�e�[�W�Ƃ̓����蔻��
	StageRayCast(downData);

	//��]
	transform_.mmRotate_ *= XMMatrixRotationAxis(STRAIGHT_VECTOR, rotationAngle_);

	//Angle��360�܂ł�������0�ɖ߂�
	if (rotationAngle_ > TWOPI_DEGREES)
		rotationAngle_ = ZEROPI_DEGREES;

	//���Z
	rotationAngle_ += ADD_ROTATION_VALUE;


	//Player�����ɍs�����玀�S
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();
}

//�^���̖@���𒲂ׂăL�����̏㎲�����肷��
void NormalBlock::CheckUnderNormal(const RayCastData& data)
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
void NormalBlock::StageRayCast(const RayCastData& data)
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