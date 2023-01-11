#include "PlayerStateManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Model.h"


//�estatic�ϐ��̏�����
JumpingState* PlayerStateManager::playerJumping_ = new JumpingState;
JumpRotationningState* PlayerStateManager::playerJumpRotationning_ = new JumpRotationningState;
RotationningState* PlayerStateManager::playerRotationning_ = new RotationningState;
RunningState* PlayerStateManager::playerRunning_ = new RunningState;
StandingState* PlayerStateManager::playerStanding_ = new StandingState;
WalkingState* PlayerStateManager::playerWalking_ = new WalkingState;
PlayerState* PlayerStateManager::playerState_ = playerStanding_;

////�萔
namespace
{
    const float RUN_SPEED = 1.5f;                 // GetPrivateProfilefloat("PLAYER", "RunSpeed", "0.02", ".\\/Parameter/Player/PlayerParameter.ini");//�����Ă���Ƃ��̃L�����̃X�s�[�h
    const float PLAYER_WALK_ANIM_SPEED = 1.0f;    //�A�j���[�V�����̍Đ����x
    const float ANIM_RUN_SPEED = 2.0f;            //�A�j���[�V�����̍Đ����x(�����Ă�Ƃ�)
}

//�R���X�g���N�^
PlayerStateManager::PlayerStateManager():front_(XMVectorSet(0, 0, 1.0f, 0))
{
}

//�X�V
void PlayerStateManager::Update2D(Player* player)
{
    //////���ׂĂ̏�Ԃɋ��ʂ��鏈�������Ă���

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;
    
    if (PadLx > ZERO || PadLx < ZERO)
    {
        //����Player���������Ă��Ȃ��̂Ȃ�A�j���[�V�����J�n
        playerState_ == PlayerStateManager::playerStanding_ ? Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), true)
                                         : Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

        //�W�����v��]�����Ă��Ȃ��Ȃ�
        if (playerState_ != PlayerStateManager::playerJumpRotationning_ && playerState_ != PlayerStateManager::playerRotationning_)
        {
            //�L�����̏㎲�̊p�x���R���g���[���[�̊p�x�ɕϊ�
            GameManager::GetpPlayer()->SetAngle(-atan2(PadLx, -padLy));
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(GameManager::GetpPlayer()->GetAngle());
        }
        else
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(-atan2(PadLx, padLy));


        //Player�̈ړ�
        {

            //�ړ�����Ƃ���L�g���K�[�������Ă�����_�b�V��������
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), PLAYER_WALK_ANIM_SPEED);


            //�W�����v��]�����Ă��邩�ɂ����Player�̓�������������,Player�ړ�
            if (playerState_ != PlayerStateManager::playerJumpRotationning_ && playerState_ != PlayerStateManager::playerRotationning_)
                GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmmRotate()))));
            else
                GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmPreviousAngle()))));

            //Z�̃|�W�V��������0�ɂ���
            GameManager::GetpPlayer()->SetPositionZ(ZERO);

            //�O�x�N�g���̏�����
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));

        }
    }
    else
        Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

	//���݂̏�Ԃ̍X�V���Ă�
	playerState_->Update2D(player);
}

//3D�p�X�V
void PlayerStateManager::Update3D(Player* player)
{
    //////���ׂĂ̏�Ԃɋ��ʂ��鏈�������Ă���

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    //�����ł��������Ȃ�
    if (PadLx > ZERO || padLy > ZERO || PadLx < ZERO || padLy < ZERO)
    {
        //����Player���������Ă��Ȃ��̂Ȃ�A�j���[�V�����J�n
        playerState_ == PlayerStateManager::playerStanding_ ? Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), true)
                                         : Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

        //�W�����v��]�����Ă��Ȃ��Ȃ�
        if (playerState_ != PlayerStateManager::playerJumpRotationning_ && playerState_ != PlayerStateManager::playerRotationning_)
        {
            //�L�����̏㎲�̊p�x���R���g���[���[�̊p�x�ɕϊ�
            GameManager::GetpPlayer()->SetAngle(atan2(PadLx, padLy) + GameManager::GetpPlayer()->GetCamAngle());
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(GameManager::GetpPlayer()->GetAngle());
        }
        else
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(atan2(PadLx, padLy) + GameManager::GetpPlayer()->GetCamAngle());


        //Player�̈ړ�
        {

            //�ړ�����Ƃ���L�g���K�[�������Ă�����_�b�V��������
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), PLAYER_WALK_ANIM_SPEED);


            //�W�����v��]�����Ă��邩�ɂ����Player�̓�������������,Player�ړ�
            if (playerState_ != PlayerStateManager::playerJumpRotationning_ && playerState_ != PlayerStateManager::playerRotationning_)
                GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmmRotate()))));
            else
                GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmPreviousAngle()))));

            //�O�x�N�g���̏�����
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));
        }
    }
    else
        Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

    //���݂̏�Ԃ̍X�V���Ă�
    playerState_->Update3D(player);
}

//���͂ɂ���ď�ԕω�����
void PlayerStateManager::HandleInput(Player* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PlayerStateManager::Enter(Player* player)
{
}
