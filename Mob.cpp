#include "Mob.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Manager/GameManager/GameManager.h"

//�R���X�g���N�^
Mob::Mob(GameObject* parent, std::string modelPath,std::string name)
	: GameObject(parent, name), hModel_(-1), modelNamePath_(modelPath), hGroundModel_(ZERO), angle_(ZERO),

    ///////////////////�J����///////////////////////
    totalMx_(XMMatrixIdentity()),
    vNormal_(XMVectorSet(ZERO, -1, ZERO, ZERO)),
    up_(XMVectorSet(ZERO, 1, ZERO, ZERO)),
    down_(XMVectorSet(ZERO, -1, ZERO, ZERO))
{
}

//������
void Mob::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load(modelNamePath_);
	assert(hModel_ >= ZERO);

	////////////////////�p����ŐV���ɏ������̓��e�ǉ�����p///////////////////////

	ChildInitialize();
}

//�X�V�̑O�Ɉ�񂾂��Ă΂��֐�
void Mob::StartUpdate()
{
    if (GameManager::GetpStage() == nullptr) return;

    ///////////////Stage�̃f�[�^�擾///////////////////

    //���f���ԍ��擾
    ARGUMENT_INITIALIZE(pstage_,GameManager::GetpStage());
    int polyModel = pstage_->GetPolyModell();

    //3D�Ȃ�
    if (pstage_->GetthreeDflag())
    {
        //�߂��̃|���S���𒲂ׂ�
        NearPolyData dataNormal;
        dataNormal.start = transform_.position_;
        Model::NearPolyNormal(polyModel, &dataNormal);

        //�@����ǉ�
        ARGUMENT_INITIALIZE(vNormal_,XMLoadFloat3(&dataNormal.normal));
    }
    else
        ARGUMENT_INITIALIZE(vNormal_,UP_VECTOR);

    ///////////////���X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

    ARGUMENT_INITIALIZE(transform_.mFlag_,true);

    //�p�����StartUpdate
	ChildStartUpdate();
}

//�X�V
void Mob::Update()
{
    //null�Ȃ珈�������Ȃ�
    if (pstage_ == nullptr) return;

    //�X�e�[�W�ɍ��킹��Mob����]������
    RotationInStage();

    //�p���悲�Ƃɓ�����ς����
    ChildUpdate();
}

//�X�e�[�W�ɍ��킹��Mob����]
void Mob::RotationInStage()
{
    //X�̃x�N�g���𔲂����
    float dotX = 0;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_));

        //X�̃x�N�g���𔲂����
        dotX = XMVectorGetX(vecDot);
    }

    //�O�ϋ��߂�
    XMVECTOR cross = XMVector3Cross(up_, vNormal_);

    //2D
    if (!pstage_->GetthreeDflag())
    {
        totalMx_ = XMMatrixIdentity();
        transform_.mmRotate_ = totalMx_;

        transform_.mmRotate_ *= XMMatrixRotationAxis(UP_VECTOR, angle_);
    }
    //3D
    else
    {
        if (dotX != ZERO && dotX <= 1 && dotX >= -1)
        {
            totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));

            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);
        }
        else
        {
            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);
        }
    }

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
        up_ = vNormal_;
}

//�`��
void Mob::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	ChildDraw();
}

//�J��
void Mob::Release()
{
    ChildRelease();
}



