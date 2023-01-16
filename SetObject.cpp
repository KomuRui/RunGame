#include "SetObject.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Manager/GameManager/GameManager.h"

//�萔
namespace
{
    static const float RADIUS_SMALL_VALUE = 0.5;  //���a�������������������鎞�̒l
    static const int   Z_DISTANCE = 100;          //PlayerZ�̈ʒu���玩�gZ�܂ł̋���
    static const int   MIN_GENERATION_SPEED = 30; //�ŏ������X�s�[�h(FPS)
    static const int   MAX_GENERATION_SPEED = 120;//�ő吶���X�s�[�h(FPS)
}

//�R���X�g���N�^
SetObject::SetObject(GameObject* parent, std::string name)
	:GameObject(parent, name),radius_(ZERO), generatingSpeed_(ZERO), fpsCount_(ZERO)
{
}

//������
void SetObject::Initialize()
{
    ARGUMENT_INITIALIZE(generatingSpeed_, Random(MIN_GENERATION_SPEED, MAX_GENERATION_SPEED));
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void SetObject::StartUpdate()
{
    //���g��transform������
    ARGUMENT_INITIALIZE(transform_.position_,GameManager::GetpStage()->GetPosition());
    ARGUMENT_INITIALIZE(transform_.position_.z, GameManager::GetpPlayer()->GetPosition().z + Z_DISTANCE);

    //���C���΂��Ĕ��a��ݒ肷��
    RayCastData dataNormal;
    ARGUMENT_INITIALIZE(dataNormal.start,transform_.position_);
    ARGUMENT_INITIALIZE(dataNormal.dir,VectorToFloat3(DOWN_VECTOR));
    Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

    //�����𔼌a��(���߂�������菭����������������)
    ARGUMENT_INITIALIZE(radius_, dataNormal.dist - RADIUS_SMALL_VALUE);
}

//�X�V
void SetObject::Update()
{
    //�I�u�W�F�N�g����
    ObjectGeneration();

    //Z�̈ʒu�X�V
    ARGUMENT_INITIALIZE(transform_.position_.z, GameManager::GetpPlayer()->GetPosition().z + Z_DISTANCE);
}

//�`��
void SetObject::Draw()
{
}

//���
void SetObject::Release()
{
}

//�I�u�W�F�N�g����
void SetObject::ObjectGeneration()
{
    //���������̃^�C�~���O�������Ȃ�
    if (generatingSpeed_ <= fpsCount_)
    {



        //���̐����X�s�[�h�ݒ�
        ARGUMENT_INITIALIZE(generatingSpeed_, Random(MIN_GENERATION_SPEED, MAX_GENERATION_SPEED));

        //�J�E���g������
        ARGUMENT_INITIALIZE(fpsCount_, ZERO);
    }

    //�J�E���g���₷
    fpsCount_++;
}