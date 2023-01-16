#include "Enemy.h"
#include "../Engine/Model.h"

////�萔
namespace
{
    static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //�@�����Ԃ���Ƃ��̕�ԌW��
    static const int MAX_NORMAL_RADIANS = 50;               //�@���Ƃ̍ő�p�x
    static const float RAY_HIT_DISTANCE = 1.0f;             //���C�̓�����������
    static const float MOVE_RAY_HIT_DISTANCE = 0.9f;        //�����Ă���Ƃ��̃��C�̓�����������
    static const float GRAVITY_STRENGTH = 0.083f;           //�d�͂̋���
    static const float ADD_ROTATION_ANGLE = 0.02f;          //��]����Ƃ��̉��Z����p�x
    static const float MOVE_SPEED = 0.1f;                   //�ړ��X�s�[�h
    static const int SIGN_CHANGE = -1;                      //�����`�F���W���邽�߂ɕK�v
    static const int FEED_BACK_ANGLE = 50;					//�����p�x
    static const float FEED_BACK_DISTANCE = 15.0f;			//��������
    static const float MIN_PLAYER_DISTANCE = 3.0f;          //Player�Ƃ̍ŏ�����
}

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath,name),acceleration(1), operationTime_(ZERO), hGroundModel_(-1), stateCount_(ZERO),
    rotationAngle_(ZERO), rotationTotal_(ZERO), front_(XMVectorSet(ZERO, ZERO,1, ZERO)), dotX_(ZERO), rotationSign_(1),
    pState_(new EnemyState), isUseGravity_(true), basePos_(ZERO,ZERO,ZERO)
{
}

//������
void Enemy::ChildInitialize()
{
    EnemyChildInitialize();
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Enemy::ChildStartUpdate()
{
    ///////////////������Ԑݒ�///////////////////
    
    //�ҋ@���
    ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

    //�T������Ƃ��̃x�[�X�|�W�V�����ݒ�
    ARGUMENT_INITIALIZE(basePos_, transform_.position_);

    //�p�x���]
    angle_ += XMConvertToRadians(180);

    ///////////////Stage�̃f�[�^�擾///////////////////

    //���f���ԍ��擾
    hGroundModel_ = pstage_->GethModel();

    ///////////////�p����p�̏�����///////////////////

    EnemyChildStartUpdate();

}

//�X�V
void Enemy::ChildUpdate()
{

    //�������Ŏg���̂Ő�ɐ錾���Ă���
    RayCastData downData;
    downData.start = transform_.position_;         //���C�̃X�^�[�g�ʒu
    downData.dir = VectorToFloat3(down_);          //���C�̕���
    Model::AllRayCast(hGroundModel_, &downData);   //���C�𔭎�(All)

    //�^���̖@���𒲂ׂăL�����̏㎲�����肷��
    CheckUnderNormal(downData);

    //Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
    PlayerNearWithIsCheck();

    //�L�����̓���
    MovingOperation();

    //�p����p�̃A�b�v�f�[�g
    EnemyChildUpdate();

    //�X�e�[�W�Ƃ̓����蔻��
    StageRayCast(downData);
}

//�`��
void Enemy::ChildDraw()
{
    //�p����p�̕`��
    EnemyChildDraw();
}

//�^���̖@���𒲂ׂăL�����̏㎲�����肷��
void Enemy::CheckUnderNormal(const RayCastData& data)
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
void Enemy::StageRayCast(const RayCastData& data)
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

        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);
        ZERO_INITIALIZE(stateCount_);

        //�ҋ@���
        ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

        //�A�j���[�V������~
        Model::SetAnimFlag(hModel_, false);
    }

    //���̋�����1.0�ȏォ�d�͓K�p����Ȃ�
    if (data.dist >= RAY_HIT_DISTANCE && isUseGravity_)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((-vNormal_) * GRAVITY_STRENGTH));
    }

}

//�L�����̓���
void Enemy::MovingOperation()
{
    //��Ԃ̍X�V���Ă�
    pState_->Update3D(this);
}

//�T���͈͓��ɂ��邩�ǂ���
bool Enemy::IsInSearchRange()
{
    //�T���͈͓��ɂ���
    if (RangeCalculation(basePos_, transform_.position_) < 8)
        return true;
    else
    {
        //Player�̃|�W�V�����Q�b�g
        XMFLOAT3 playerPos = GameManager::GetpPlayer()->GetPosition();

        //�x�[�X�|�W�V��������Player�ւ̃x�N�g��
        XMVECTOR vToPlayer = XMLoadFloat3(&basePos_) - XMLoadFloat3(&transform_.position_);

        //���g����Player�ւ̃x�N�g���Ǝ��g�̑O�x�N�g���Ƃ̓��ς𒲂ׂ�
        dotX_ = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer))));

        //����Enemy�������Ă�������ƃx�[�X�|�W�V�����܂ł̕����̊p�x��FEED_BACK_ANGLE���Ȃ��Ȃ�
        if (dotX_ < XMConvertToRadians(FEED_BACK_ANGLE) && dotX_ > XMConvertToRadians(-FEED_BACK_ANGLE))
            return true;
        else
            return false;
    }
}

///////////////////AI�s���֐�////////////////////

//�ҋ@
void Enemy::Wait()
{
    //�A�j���[�V������~
    Model::SetAnimFlag(hModel_, true);


    //��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    if (stateCount_ > operationTime_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);

        //�ҋ@���
        ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
    }
}

//�s��
void Enemy::Move()
{
    //�����T���͈͂ɂ��Ȃ��̂Ȃ�
    if (!IsInSearchRange())
    {
        //�ҋ@���
        ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

        //��]��Ԃ̉�]�p�x���x�[�X�|�W�V�����ɓ����悤�ɐݒ肷��
        ARGUMENT_INITIALIZE(rotationAngle_,dotX_);
    }

    //�A�j���[�V�����J�n
    Model::SetAnimFlag(hModel_, true);

    //�ړ����Ď��g��transform�ɔ��f
    transform_.position_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)) * MOVE_SPEED));

    //�������킹�邽�߂Ƀ��C���΂�
    RayCastData downData;
    downData.start = transform_.position_;         //���C�̃X�^�[�g�ʒu
    downData.dir = VectorToFloat3(down_);          //���C�̕���
    Model::AllRayCast(hGroundModel_, &downData);   //���C�𔭎�(All)

    //�n�`�̍����ɍ��킹��
    //��������������0.9f��菬�����Ȃ�
    if (downData.dist < MOVE_RAY_HIT_DISTANCE)
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&downData.pos) + vNormal_);

    //��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    if (stateCount_ > operationTime_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(stateCount_);

        //�ҋ@���
        ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

        //�A�j���[�V������~
        Model::SetAnimFlag(hModel_, false);
    }
}

//��]
void Enemy::Rotation()
{
    //�A�j���[�V������~
    Model::SetAnimFlag(hModel_, false);

    //��]
    angle_ += ADD_ROTATION_ANGLE * rotationSign_;
    rotationTotal_ += ADD_ROTATION_ANGLE;

    //��]�p�x����]�����������Ȃ�����
    if (rotationTotal_ > rotationAngle_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);

        //�ҋ@���
        ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
    }
}

//Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
void Enemy::PlayerNearWithIsCheck()
{
    ////����Player�̃|�C���^��Null�ɂȂ��Ă����珈�������Ȃ�
    //if (GameManager::GetpPlayer() == nullptr) return;

    ////Player�̃|�W�V�����Q�b�g
    //XMFLOAT3 playerPos = GameManager::GetpPlayer()->GetPosition();

    ////���g����Player�ւ̃x�N�g��
    //XMVECTOR vToPlayer = XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_);

    ////���g����Player�ւ̃x�N�g���Ǝ��g�̑O�x�N�g���Ƃ̓��ς𒲂ׂ�
    //dotX_ = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer))));

    ////�ǂ��������ɉ�]�����邩���߂邽�߂ɊO�ς����߂�
    //XMVECTOR cross = XMVector3Cross(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer));

    ////�������Ⴄ�Ȃ�
    //if (signbit(XMVectorGetY(cross)) != signbit(XMVectorGetY(vNormal_)))
    //    dotX_ *= SIGN_CHANGE;


    ////���p��,�w�苗�����ɂ���Ȃ�
    //if (dotX_ < XMConvertToRadians(FEED_BACK_ANGLE) && dotX_ > XMConvertToRadians(-FEED_BACK_ANGLE) &&
    //    RangeCalculation(playerPos, transform_.position_) < FEED_BACK_DISTANCE)
    //{
    //    //����łȂ��Ȃ�Player�̕���������
    //    if(pState_ != EnemyStateList::GetEnemyDieState())
    //        angle_ += dotX_;

    //    //����ł��Ȃ��̂Ȃ�ړ���Ԃ�
    //    if(pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
    //        ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

    //    //Player�Ƃ̋������ŏ������ȓ�������łȂ��̂Ȃ�ҋ@��Ԃ�
    //    if (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < MIN_PLAYER_DISTANCE && pState_ != EnemyStateList::GetEnemyKnockBackState() && EnemyStateList::GetEnemyDieState())
    //        ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

    //    //�p����p�̊֐�(���p���A�˒�����Player������Ȃ�)
    //    PlayerWithIf();
    //}
    //else
    //    //�p����p�̊֐�(���p���A�˒�����Player���Ȃ��Ȃ�)
    //    NotPlayerWithIf();
}

//��ԃ`�F���W
void Enemy::ChangeEnemyState(EnemyState* state)
{
    //������Ԃ���Ȃ��̂Ȃ�
    if (pState_ != state)
    {
        //��ԕύX
        ARGUMENT_INITIALIZE(pState_, state);
        pState_->Enter(this);
    }
}

