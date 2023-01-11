#include "EnemyMoveState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//�X�V
void EnemyMoveState::Update2D(Enemy* enemy)
{
	//���͏���
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyMoveState::Update3D(Enemy* enemy)
{
    //�ړ�
	enemy->Move();

	//��ԕb�����₷
	enemy->SetStateCount(enemy->GetStateCount() + 1);

	//���͏���
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyMoveState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyMoveState::Enter(Enemy* enemy)
{
    enemy->SetOperationTime((rand() % 19 + 12) * 10);
    enemy->SetStateCount(ZERO);
}