#include "SetObject.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Gimmick/Coin.h"
#include "Enemy/PigEnemy.h"
#include "Block/NormalBlock.h"
#include "Block/BrickBlock.h"
#include "MiniGameTime.h"
#include "Manager/GameManager/GameManager.h"

//�萔
namespace
{
    static const float RADIUS_SMALL_VALUE = 3.0;  //���a�������������������鎞�̒l
    static const int   Z_DISTANCE = 200;          //PlayerZ�̈ʒu���玩�gZ�܂ł̋���
    static const int   MIN_GENERATION_SPEED = 30; //�ŏ������X�s�[�h(FPS)
    static const int   MAX_GENERATION_SPEED = 60;//�ő吶���X�s�[�h(FPS)
    static const int   MIN_ANGLE = 0;             //�ŏ��p�x
    static const int   MAX_ANGLE = 360;           //�ő�p�x
}

//�R���X�g���N�^
SetObject::SetObject(GameObject* parent)
	:GameObject(parent, "SetObject"),radius_(ZERO), generatingSpeed_(ZERO), fpsCount_(ZERO)
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
    //Player�����Ȃ���΂��̐揈�����Ȃ�
    if (GameManager::GetpPlayer() == nullptr) return;

    //�~�j�Q�[�����X�^�[�g���Ă��邩��Player������ł��Ȃ��̂Ȃ�I�u�W�F�N�g����
    if (MiniGameTime::IsPlay() && !GameManager::GetpPlayer()->isDie())
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
        //����
        Generation();

        //���̐����X�s�[�h�ݒ�
        ARGUMENT_INITIALIZE(generatingSpeed_, Random(MIN_GENERATION_SPEED, MAX_GENERATION_SPEED));

        //�J�E���g������
        ARGUMENT_INITIALIZE(fpsCount_, ZERO);
    }

    //�J�E���g���₷
    fpsCount_++;
}

//����
void SetObject::Generation()
{	
    //��]�s��쐬
    XMMATRIX m = XMMatrixRotationZ(XMConvertToRadians(Random(MIN_ANGLE, MAX_ANGLE)));

    //�x�N�g������
    XMVECTOR v = XMVector3Normalize(XMVector3TransformCoord(DOWN_VECTOR, m)) * radius_;

    //�I�u�W�F�N�g�̈ʒu�����߂�
    XMFLOAT3 pos = Float3Add(transform_.position_, VectorToFloat3(v));
    
    int num = rand() % 4;

    //�R�C��
    if (num == 0)
    {
        Coin* pCoin = Instantiate<Coin>(GetParent());
        pCoin->SetPosition(pos);
    }
    //�؂̓G
    else if (num == 1)
    {
        //���̏o�����邩
        int r = Random(1, 3);

        //r�̕��o��������
        for (int i = 0; i < r; i++)
        {
            pos.z += i * 8;
            PigEnemy* pCoin = Instantiate<PigEnemy>(GetParent());
            pCoin->SetPosition(pos); 
        }
    }
    //�u���b�N
    else if (num == 2)
    {
        NormalBlock* pNormalBlock = Instantiate<NormalBlock>(GetParent());
        pNormalBlock->SetPosition(pos);
    }
    else if (num == 3)
    {
        BrickBlock* pBrickBlock = Instantiate<BrickBlock>(GetParent());
        pBrickBlock->SetPosition(transform_.position_);
    }
}