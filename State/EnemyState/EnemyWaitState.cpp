#include "EnemyWaitState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//�X�V
void EnemyWaitState::Update2D(Enemy* enemy)
{
	//���͏���
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyWaitState::Update3D(Enemy* enemy)
{
	//�ҋ@
	enemy->Wait();

	//��ԕb�����₷
	enemy->SetStateCount(enemy->GetStateCount()+ 1);

	//���͏���
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyWaitState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyWaitState::Enter(Enemy* enemy)
{
	enemy->SetOperationTime((rand() % 13 + 6) * 10);
	enemy->SetStateCount(ZERO);
}