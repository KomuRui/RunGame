#pragma once
#include "PlayerState.h"

class Player;

class StandingState : public PlayerState
{
public:

	//2D�p�X�V
	void Update2D(Player* player) override;

	//3D�p�X�V
	void Update3D(Player* player) override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput(Player* player) override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter(Player* player) override;
};

