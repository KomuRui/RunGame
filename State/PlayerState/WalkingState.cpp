#include "WalkingState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"

//�X�V
void WalkingState::Update2D(Player* player)
{
	HandleInput(player);
}

//3D�p�X�V
void WalkingState::Update3D(Player* player)
{
}

//���͂ɂ���ď�ԕω�����
void WalkingState::HandleInput(Player* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void WalkingState::Enter(Player* player)
{
}