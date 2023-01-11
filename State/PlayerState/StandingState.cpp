#include "StandingState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "PlayerStateManager.h"

//�X�V
void StandingState::Update2D(Player* player)
{
	//���C�����ɔ�΂�
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(DOWN_VECTOR);
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//���C�̓�������������1.0f��菬�����Ȃ�
	if (dataNormal.dist < 1.0f)
	{
		dataNormal.pos.y += 1.0f;
		GameManager::GetpPlayer()->SetPosition(dataNormal.pos);
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void StandingState::Update3D(Player* player)
{
	//���C�����ɔ�΂�
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(GameManager::GetpPlayer()->GetDown());
	Model::AllRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//��������������0.9f��菬�����Ȃ�
	if (dataNormal.dist < 0.9f)
	{
		//�n�`�ɍ������킹��
		GameManager::GetpPlayer()->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + GameManager::GetpPlayer()->GetNormal()));
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void StandingState::HandleInput(Player* player)
{
	//�W�����v��ԂɕύX
	if(Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumping_;
		PlayerStateManager::playerState_->Enter(player);
	}

	//��]��ԂɕύX
	if (Input::GetPadTrrigerR())
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerRotationning_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter(Player* player)
{
}
