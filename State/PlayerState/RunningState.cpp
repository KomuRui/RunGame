#include "RunningState.h"
#include "../../Engine/Input.h"
#include "PlayerStateManager.h"

//�X�V
void RunningState::Update2D(Player* player)
{
	HandleInput(player);
}

//3D�p�X�V
void RunningState::Update3D(Player* player)
{
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void RunningState::HandleInput(Player* player)
{
	//�W�����v��ԂɕύX
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
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
void RunningState::Enter(Player* player)
{
}