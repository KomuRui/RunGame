#include "Player.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include <cmath>
#include "Engine/Light.h"
#include "Engine/BoxCollider.h"
#include "Engine/SphereCollider.h"
#include "Manager/GameManager/GameManager.h"
#include "Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "Block/Block.h"
#include <algorithm>
#include <iostream>

////�萔
namespace
{
    //Player�̃p�����[�^��ۑ����Ă���p�X
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////�L�����̕K�v�ȏ��///////////////////

    static const float NORMAL_INTERPOLATION_FACTOR = GetPrivateProfilefloat("PLAYER", "NormalFactor", "0.3", parameterPath); //�@�����Ԃ���Ƃ��̕�ԌW��
    static const float PLAYER_ANIM_SPEED = GetPrivateProfilefloat("PLAYER", "AnimSpeed", "1.0", parameterPath);                //�A�j���[�V�����̍Đ����x
    static const int ANIM_START_FRAME = GetPrivateProfilefloat("PLAYER", "AnimStartFrame", "1", parameterPath);                //�A�j���[�V�����̊J�n�t���[��
    static const int ANIM_END_FRAME = GetPrivateProfilefloat("PLAYER", "AnimEndFrame", "60", parameterPath);			       //�A�j���[�V�����̏I���t���[��
    static const int MAX_NORMAL_RADIANS = GetPrivateProfilefloat("PLAYER", "MaxNormalRadians", "50", parameterPath);   	       //�@���Ƃ̍ő�p�x			
    static const float PLAYER_MODEL_SIZE_X = 1.0f;  //Player��X�̃��f���T�C�Y
    static const float PLAYER_MODEL_SIZE_Y = 2.0f;  //Player��Y�̃��f���T�C�Y
    static const float GRAVITY_ADDITION = 0.03f;    //�d�͂̉��Z�l

    ////////////////���C�g///////////////////
    
    static const float LIGHT_POS_Z = GetPrivateProfilefloat("LIGHT", "LightZPos", "2", parameterPath);  //���C�g��Z�̃|�W�V����

    ////////////////�J����///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //�J�����̈ړ����Ԃ���Ƃ��̕�ԌW��
    static const float CAM_POS_2D_Z = GetPrivateProfilefloat("CAMERA", "CamPos2DZ", "20", parameterPath);                   //2D�̎��̃J������Z�̈ʒu
    static const float CAM_SHOULDER_ADD_VALUE = 0.5f; //�V�����_�[�ŃJ�������삷�鎞�̉��Z����l
    static const float CAM_STICR_ADD_VALUE = 0.03f;   //�X�e�B�b�NR�ŃJ�����𑀍삷��Ƃ��̉��Z����l

    ////////////////�R���C�_�[///////////////////

    static const XMFLOAT3 COLLIDER_POS = { ZERO,ZERO,ZERO };  //�R���C�_�[�̈ʒu
    static const float    COLLIDER_SIZE = 1.0f;               //�R���C�_�[�̃T�C�Y
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), 

    ///////////////�L�����̕K�v�ȏ��///////////////////

    //���f��
    hModel_(-1),
    hGroundModel_(ZERO),

    //�e�����x�N�g��
    vNormal_(XMVectorSet(ZERO, -1, ZERO, ZERO)),
    up_(XMVectorSet(ZERO, 1, ZERO, ZERO)),
    down_(XMVectorSet(ZERO, -1, ZERO, ZERO)),
    front_(XMVectorSet(ZERO, ZERO, 1, ZERO)),

    //�L�����̎���]�ɕK�v�ȕϐ�
    totalMx_(XMMatrixIdentity()),
    jampRotationPreviousAngle_(ZERO),
    angle_(ZERO),
    normalFlag_(true),

    //�W�����v
    vJamp_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),

    //���̑�
    acceleration_(1),
    pState_(new PlayerStateManager),
    beforePos_(ZERO, ZERO, ZERO),
    runSpeed_(5.0f),
    runMode_(false),

    ///////////////////�J����///////////////////////

    camMat_(XMMatrixIdentity()),
    vCam_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
    camStatus_(LONG),
    camAngle_(1),
    camPosFlag_(true),
    camFlag_(true),
    camLong_(true)
    
{
    camVec_[LONG] = XMVectorSet(ZERO, 5, -15, ZERO);
    camVec_[SHORT] = XMVectorSet(ZERO, 4, -4, ZERO);
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void Player::Initialize()
{
    ///////////////Player�̏�ԏ�����///////////////////

    PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;

	///////////////���f���E�摜�f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= ZERO);

    hPictWind_ = Image::Load("Image/kaze2.png");
    assert(hPictWind_ >= ZERO);

    hPictWind2_ = Image::Load("Image/kaze3.png");
    assert(hPictWind2_ >= ZERO);

    ///////////////Player�͌��X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

    transform_.mFlag_ = true;

    ///////////////Player�̓����蔻��ݒ�///////////////////

    SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
    AddCollider(collision);

    ///////////////�G�t�F�N�g�ƃA�j���[�V�����ݒ�///////////////////

    //�G�t�F�N�g�o�����߂ɕK�v
    PlayerEffectManager::Initialize(this);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    ///////////////Stage�̃f�[�^�擾///////////////////

    //���f���ԍ��擾
    pstage_ = GameManager::GetpStage();
    hGroundModel_ = pstage_->GethModel();

    //���C���΂��Ď��g�̎���ݒ肷��
    RayCastData dataNormal;
    dataNormal.start = transform_.position_;      
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, down_);
    dataNormal.dir = moveY2;
    Model::RayCast(hGroundModel_, &dataNormal);   

    //���g�̏㎲�ݒ�
    vNormal_ = XMLoadFloat3(&dataNormal.normal);


    ///////////////�J���������ݒ�///////////////////

    ARGUMENT_INITIALIZE(vCam_, camVec_[camStatus_]);

}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Player::StartUpdate()
{
}

//�X�V
void Player::Update()
{
    //�X�e�[�W���null�Ȃ炱�̐�͎��s���Ȃ�
    if (pstage_ == nullptr) return;

    //�^���̖@���𒲂ׂ�
    CheckUnderNormal();

    //�X�e�[�W��3D�Ȃ�
    if (pstage_->GetthreeDflag())
    {
        MovingOperation();       //Player����
        RotationInStage();       //�X�e�[�W�ɍ��킹�ĉ�]
        StageRayCast();          //�X�e�[�W�Ƃ̓����蔻��
    }
    //�X�e�[�W���^��2D�Ȃ�
    else
    {
        MovingOperation2D();     //Player����
        RotationInStage2D();     //�X�e�[�W�ɍ��킹�ĉ�]
        StageRayCast2D();        //�X�e�[�W�Ƃ̓����蔻��
    }

    //�J�����̋���
    CameraBehavior();
} 

//�`��
void Player::Draw()
{
    //Player�`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

    //�������郂�[�h�Ȃ�
    if (runMode_ && camLong_)
    {
        Transform t;

        //�����ŕ\������摜��ς���
        if (rand() % 2 == 1)
        {
            Image::SetTransform(hPictWind_, t);
            Image::Draw(hPictWind_);
        }
        else
        {
            Image::SetTransform(hPictWind2_, t);
            Image::Draw(hPictWind2_);
        }
    }
}

//�J��
void Player::Release()
{
}

/////////////////////�֐�//////////////////////

//�J�����̏���
void Player::CameraBehavior()
{
    static XMFLOAT3 camTar = transform_.position_;
    static XMFLOAT3 campos = transform_.position_;

    //�J������������邩���Ȃ���Flag��false�Ȃ炱�̐揈�����Ȃ�
    if (!camFlag_)
    {
        //�J�����̃|�W�V������y����Player�Ɠ����ɂ���(���������Ōv�Z����������)
        XMFLOAT3 camPos = Camera::GetPosition();
        camPos.y = transform_.position_.y;
        
        //�J��������Player�ւ̕����x�N�g��
        XMVECTOR dir = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&camPos);

        //�p�x���߂�
        float dotX = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(dir), front_)));

        //���߂��p�x��������]
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, dotX);

        //Player����]���Ă���Ȃ�
        if (IsRotation()) mPreviousAngle_ *= XMMatrixRotationAxis(vNormal_, dotX);

        ARGUMENT_INITIALIZE(camAngle_, ZERO);
        ARGUMENT_INITIALIZE(campos, Camera::GetPosition());
        ARGUMENT_INITIALIZE(camTar, Camera::GetTarget());

        //���C�g�ݒ�
        XMFLOAT3 lightPos;
        XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
        Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));

        return;
    }

    //���郂�[�h�Ȃ�
    if (runMode_)
    {
        //�������ɂ���
        if (camLong_)
        {
            //�J�������Ԃœ�����
            ARGUMENT_INITIALIZE(vCam_, XMVectorLerp(vCam_, XMVectorSet(ZERO, 5, -55, ZERO), 0.1f));

            //������1�ȓ��Ȃ�
            if (RangeCalculation(vCam_, XMVectorSet(ZERO, 5, -55, ZERO)) < 1.0f)
            {
                ARGUMENT_INITIALIZE(camLong_, false);
                ARGUMENT_INITIALIZE(runSpeed_, 5.0f);
                GameManager::SetTextScale(1.0f);
            }
        }
        //�ʏ�ɂ���
        else
        {
            //�J�������Ԃœ�����
            ARGUMENT_INITIALIZE(vCam_, XMVectorLerp(vCam_, camVec_[camStatus_], 0.1f));

            //������1�ȓ��Ȃ�
            if (RangeCalculation(vCam_, camVec_[camStatus_]) < 1.0f)
            {
                ARGUMENT_INITIALIZE(vCam_, camVec_[camStatus_]);
                ARGUMENT_INITIALIZE(camLong_, true);
                ARGUMENT_INITIALIZE(runMode_, false);
                GameManager::ComboReset();
            }
        }

    }
    else
        ARGUMENT_INITIALIZE(vCam_, camVec_[camStatus_]);

    //3D
    if (pstage_->GetthreeDflag())
    {
        XMFLOAT3 camPos;                                             //�ŏI�I�ȃJ�����̈ʒu������ϐ�
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);         //transform_.position_��Vector�^
        XMVECTOR vCamDis_ = XMVector3TransformCoord(vCam_, camMat_); //vCam����

        vPos += vCamDis_;                //Player��Pos��Player����J�����̃x�N�g��������
        XMStoreFloat3(&camPos, vPos);    //camPos��vPos��XMFLOAT3�ɕς��Ă����

        //�J�����̏���������߂邽�߂�StagePotision�������ď�����̃x�N�g�����쐬
        XMFLOAT3 UpDirection = { XMVectorGetX(-vNormal_), XMVectorGetY(-vNormal_), XMVectorGetZ(-vNormal_) };

        XMStoreFloat3(&camTar, XMVectorLerp(XMLoadFloat3(&camTar), XMLoadFloat3(&transform_.position_), CAMERA_INTERPOLATION_FACTOR));
        camTar = Float3Add(transform_.position_,VectorToFloat3(vNormal_ * 3));

        campos = camPos;

        //�J�����̂��낢��ݒ�
        Camera::SetUpDirection(vNormal_);
        Camera::SetPosition(campos);
        Camera::SetTarget(camTar);

        //���C�g�ݒ�
        XMFLOAT3 lightPos;
        XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));

        Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));

    }
    //2D
    else
    {

        XMFLOAT3 camTar2 = { transform_.position_.x,transform_.position_.y,transform_.position_.z };
        XMFLOAT3 camPos2 = { transform_.position_.x, transform_.position_.y, CAM_POS_2D_Z };

        //flag��true�Ȃ�ʒu������
        if (camPosFlag_)
            XMStoreFloat3(&campos, XMVectorLerp(XMLoadFloat3(&campos), XMLoadFloat3(&camPos2), CAMERA_INTERPOLATION_FACTOR));

        XMStoreFloat3(&camTar, XMVectorLerp(XMLoadFloat3(&camTar), XMLoadFloat3(&camTar2), CAMERA_INTERPOLATION_FACTOR));

        //�J�����̂��낢��ݒ�
        Camera::SetPosition(campos);
        Camera::SetTarget(camTar);

        //Player�ɂ��Ă郉�C�g�̈ʒu����
        Light::SetPlayerPosition(XMFLOAT4(transform_.position_.x, transform_.position_.y, LIGHT_POS_Z, ZERO));
    }

}

//�^���̖@���𒲂ׂ�
void Player::CheckUnderNormal()
{
    //���C��^���ɑł�
    RayCastData data;
    data.start = transform_.position_;
    data.dir = VectorToFloat3(down_);
    Model::AllRayCast(hGroundModel_, &data);

    //�@���𒲂ׂ邩�ǂ�����Flag��true�Ȃ�
    if (normalFlag_)
    {
        //���C���������Ă��Ă������ł���x�N�g����vNormal_�̒l���Ⴄ�̂Ȃ�
        if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
        {
            //���̃L�����̏�x�N�g��vNormal�Ɖ��̖@���̓��ς����߂�
            float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

            //�p�x��50�x�ȓ��Ɏ��܂��Ă�����(�ǂƂ��ɏ�点�Ȃ�����)
            if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
            {
                //������ƕ��
                vNormal_ = XMVector3Normalize((XMVectorLerp( XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
                down_ = -vNormal_;
            }

        }
    }
}

//�X�e�[�W�ɍ��킹��Player����](3D�p)
void Player::RotationInStage()
{
    //X�̃x�N�g���𔲂����
    float dotX = ZERO;

    //�O�ς̌��ʓ����p
    XMVECTOR cross;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_)));

        //�O�ς����߂�(���̌��ʂ̎��������ɂ���)
        cross = XMVector3Cross(up_, vNormal_);
    }
    else
        cross = XMVectorSet(ZERO,ZERO,ZERO,ZERO);

    //�G���[�͈͓̔��ł͂Ȃ����
    if (dotX != ZERO && dotX <= 1 && dotX >= -1 && !VectorNotZero(cross))
    {
        //Player����]�����邽�߂ɓ�̎��ŉ�]������
        totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Player����]���Ă���Ȃ�
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_);

        //�J�����̍s��p��
        camMat_ = totalMx_;
    }
    else
    {
        //Player����]�����邽�߂Ɏ��ŉ�]������
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Player����]���Ă���Ȃ�
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_));
    }

    //���g�̏�x�N�g���X�V
    up_ = vNormal_;
}

//�X�e�[�W�ɍ��킹��Player����](2D�p)
void Player::RotationInStage2D()
{
    //Player�̌����̊p�x�����x�N�g������]������
    transform_.mmRotate_ = XMMatrixRotationAxis(UP_VECTOR, angle_);

    //Player����]���Ă���Ȃ�
    if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(UP_VECTOR, jampRotationPreviousAngle_));
}

//�v���C���[����(3D�p)
void Player::MovingOperation()
{
    //�ړ�����O�̃|�W�V�������i�[
    ARGUMENT_INITIALIZE(beforePos_, transform_.position_);

    //���̏�Ԃ̓���
    pState_->Update3D(this);

    //���V�����_�[����������p�x�ύX
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER)) camAngle_ += CAM_SHOULDER_ADD_VALUE;
    
    //�E�V�����_�[����������p�x�ύX
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)) camAngle_ -= CAM_SHOULDER_ADD_VALUE;

    //�E�X�e�B�b�N�ŃJ�����̊p�x������
    if (Input::GetPadStickR().x) camAngle_ += CAM_STICR_ADD_VALUE * Input::GetPadStickR().x;
}

//�v���C���[����(2D�p)
void Player::MovingOperation2D()
{
    //���̏�Ԃ̓���
    pState_->Update2D(this);
}

//���C(3D�p)
void Player::StageRayCast()
{

     //�e����
    RayCastData rightData;
    RayCastData leftData;
    RayCastData straightData;
    RayCastData upData;
    RayCastData downData;

    //�������Ă邩�m�F
    HitTest(&rightData, RIGHT_VECTOR);
    HitTest(&leftData, LEFT_VECTOR);
    HitTest(&straightData, STRAIGHT_VECTOR);
    HitTest(&upData, UP_VECTOR);
    HitTest(&downData, DOWN_VECTOR);

    ////////////////////////////////�͂ݏo������������//////////////////////////////////////

    //��Ƀx�N�g���^�̃|�W�V����������Ă���
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //�E
    if (rightData.dist <= 1.0)
    {
        XMVECTOR dis = { rightData.dist,ZERO,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(RIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //��
    if (leftData.dist <= 1.0)
    {
        XMVECTOR dis = { -leftData.dist,ZERO,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(LEFT_VECTOR, transform_.mmRotate_) - dis));
    }

    //�O
    if (straightData.dist <= 1.0)
    {
        XMVECTOR dis = { ZERO,ZERO,straightData.dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //��
    if (upData.dist <= 1.0)
    {
        XMVECTOR dis = { ZERO,upData.dist,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(UP_VECTOR, transform_.mmRotate_) - dis));

        //��ԕύX
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        //�u���b�N���nullptr����Ȃ��̂Ȃ�
        if (upData.block != nullptr)
        {
            //�u���b�N�𓖂����Ă����Ԃɂ���
            upData.block->SetIsHit(true);
        }
    }

    //��
    if (downData.dist >= 1.0)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((down_ / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //��]����Ȃ��Ȃ�
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //��ԕύX
            PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }
}

//���C(2D�p)
void Player::StageRayCast2D()
{
    //�u���b�N�Ƃ̓����蔻������邽�߂Ƀg�����X�t�H�[����ۑ�
    XMFLOAT3 Colpos = transform_.position_;
    Colpos.x -= (PLAYER_MODEL_SIZE_X / 2);

    //�E
    if (pstage_->IsBlock(&Colpos, Right))
    {
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);
    }

    ARGUMENT_INITIALIZE(Colpos,transform_.position_);
    Colpos.x += (PLAYER_MODEL_SIZE_X / 2);

    //��
    if (pstage_->IsBlock(&Colpos,Left))
    {
        ARGUMENT_INITIALIZE(transform_.position_,Colpos);
    }

    ARGUMENT_INITIALIZE(Colpos,transform_.position_);
    Colpos.y -= (PLAYER_MODEL_SIZE_Y / 2);

    //��
    if (pstage_->IsBlock(&Colpos, Under))
    {
        ARGUMENT_INITIALIZE(transform_.position_,Colpos);
        
        //��]����Ȃ��Ȃ�
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //��ԕύX
            ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_,1);
    }

    ARGUMENT_INITIALIZE(Colpos,transform_.position_);
    Colpos.y += (PLAYER_MODEL_SIZE_Y / 2);

    //��
    if (pstage_->IsBlock(&Colpos, Top))
    {
        ARGUMENT_INITIALIZE(transform_.position_,Colpos);

        //��ԕύX
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        ARGUMENT_INITIALIZE(acceleration_,1);
    }

    //�e����
    RayCastData rightData;
    RayCastData leftData;
    RayCastData upData;
    RayCastData downData;

    //�������Ă邩�m�F
    HitTest2D(&rightData, RIGHT_VECTOR);
    HitTest2D(&leftData, LEFT_VECTOR);
    HitTest2D(&upData, UP_VECTOR);
    HitTest2D(&downData, DOWN_VECTOR);

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    if (rightData.dist <= 1)
    {
        XMVECTOR dis = { rightData.dist,ZERO,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (RIGHT_VECTOR - dis));
    }
    if (leftData.dist <= 1)
    {
        XMVECTOR dis = { -leftData.dist,ZERO,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (LEFT_VECTOR - dis));
    }

    if (upData.dist <= 1)
    {
        XMVECTOR dis = { ZERO,upData.dist,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (UP_VECTOR - dis));
    }

    if (downData.dist >= 0.9)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((DOWN_VECTOR / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //��]����Ȃ��Ȃ�
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //��ԕύX
            PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_,1);
    }

}

//�����蔻��
void Player::HitTest(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;                                               //���C�̔��ˈʒu  
    XMStoreFloat3(&data->dir, XMVector3TransformCoord(dir, transform_.mmRotate_));    //���C�̕���
    Model::AllRayCast(hGroundModel_, data);                                           //���C�𔭎�
}

//�����蔻��
void Player::HitTest2D(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;       //���C�̔��ˈʒu  
    XMStoreFloat3(&data->dir, dir);           //���C�̕���
    Model::RayCast(hGroundModel_, data);      //���C�𔭎�
}

//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
void Player::TimeMethod()
{
    Enter();
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //Warp�Ɠ��������Ȃ�
    if (pTarget->GetObjectName() == "Warp")
    {
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        ARGUMENT_INITIALIZE(acceleration_,1);
    }
}

