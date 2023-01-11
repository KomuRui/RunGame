#include "JumpRotationningState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "PlayerStateManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"

//�萔
namespace
{
	const float JUMP_VECTOR_SIZE = 0.5f;   //�W�����v�x�N�g���̑傫��
	const float ADD_ROTATION_ANGLE = 0.5f; //��]����Ƃ����Z����p�x
	const float JUMP_VECTOR_DOWN = 0.015f; //�W�����v�x�N�g�������������Ă����Ƃ��̒l
}

//�X�V
void JumpRotationningState::Update2D(Player* player)
{
	//�����������Ȃ�
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Player�W�����v�ړ�
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		ARGUMENT_INITIALIZE(vJamp_, vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN));
	}
	
	//�G�t�F�N�g�̕\��
	PlayerEffectManager::RotationEffect(GameManager::GetpPlayer()->GetPlayerhModel());

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + ADD_ROTATION_ANGLE);

	//���͏������Ă�
	HandleInput(player);
}

//3D�p�X�V
void JumpRotationningState::Update3D(Player* player)
{
	//��ƂȂ�W�����v�x�N�g���ƕ����������Ȃ�
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Player�W�����v�ړ�
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(vJamp_ - (GameManager::GetpPlayer()->GetNormal() * JUMP_VECTOR_DOWN))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		vJamp_ = vJamp_ - (GameManager::GetpPlayer()->GetNormal() * JUMP_VECTOR_DOWN);
	}

	//�G�t�F�N�g�̕\��
	PlayerEffectManager::RotationEffect(GameManager::GetpPlayer()->GetPlayerhModel());

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + ADD_ROTATION_ANGLE);

	//���͏������Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void JumpRotationningState::HandleInput(Player* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void JumpRotationningState::Enter(Player* player)
{
	//�W�����v�̃x�N�g���E�t���O������
	//3D��2D�ŏ������̒l�ς���
	if (GameManager::GetpStage()->GetthreeDflag())
	{
		ARGUMENT_INITIALIZE(vJamp_, GameManager::GetpPlayer()->GetNormal() * JUMP_VECTOR_SIZE);
	}
	else
		ARGUMENT_INITIALIZE(vJamp_, UP_VECTOR * JUMP_VECTOR_SIZE);

	//��ƂȂ�W�����v�x�N�g����ۑ����Ă���
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//3D��2D�ŌĂԊ֐��ς���
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D(player);
	else
		Update2D(player);
}