#include "EnemyKnockBackState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//�X�V
void EnemyKnockBackState::Update2D(Enemy* enemy)
{
	//���͏���
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyKnockBackState::Update3D(Enemy* enemy)
{
	//�m�b�N�o�b�N
	enemy->KnockBackDie();

	//���͏���
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyKnockBackState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyKnockBackState::Enter(Enemy* enemy)
{
}