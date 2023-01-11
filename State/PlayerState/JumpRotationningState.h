#pragma once
#include "PlayerState.h"

class Player;

class JumpRotationningState : public PlayerState
{
	XMVECTOR vJamp_;        //�W�����v����Ƃ��̌��ƂȂ��x�N�g��
	XMVECTOR keepJamp_;     //���ƂƂȂ�W�����v�x�N�g����ۑ����Ă���

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

