#pragma once
#include  "EnemyState.h"

//�O��`
class Enemy;

/// <summary>
/// �m�b�N�o�b�N��Ԃ̃N���X
/// </summary>
class EnemyKnockBackState : public EnemyState
{

public:

	//2D�p�X�V
	void Update2D(Enemy* enemy) override;

	//3D�p�X�V
	void Update3D(Enemy* enemy) override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput(Enemy* enemy) override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter(Enemy* enemy) override;
};