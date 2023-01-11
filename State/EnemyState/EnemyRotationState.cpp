#include "EnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//�X�V
void EnemyRotationState::Update2D(Enemy* enemy)
{
	//���͏���
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyRotationState::Update3D(Enemy* enemy)
{
	//��]
	enemy->Rotation();

	//���͏���
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyRotationState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyRotationState::Enter(Enemy* enemy)
{
    //��]��������ݒ�
    enemy->SetRotationSign(rand() % 2 == 1 ? 1 : -1);

    //��]�p�x�ݒ�
    enemy->SetRotationAngle(XMConvertToRadians((rand() % 141) + 40));

    //�ǂ̂��炢��]��������������
    enemy->SetRotationTotal(ZERO);
}