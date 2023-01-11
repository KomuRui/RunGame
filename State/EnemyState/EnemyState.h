#pragma once
#include "EnemyState.h"

//�O��`
class Enemy;

//��Ԃ̊��N���X
class EnemyState
{
public:

	/// <summary>
	/// 2D�p�X�V
	/// </summary>
	/// <param name="enemy">��Ԃ��g���Ă�G�̃|�C���^</param>
	virtual void Update2D(Enemy* enemy) {};

	/// <summary>
	/// 3D�p�X�V
	/// </summary>
	/// <param name="enemy">��Ԃ��g���Ă�G�̃|�C���^</param>
	virtual void Update3D(Enemy* enemy) {};

	/// <summary>
	/// ���͂ɂ���ď�ԕω�����
	/// </summary>
	/// <param name="enemy">��Ԃ��g���Ă�G�̃|�C���^</param>
	virtual void HandleInput(Enemy* enemy) {};

	/// <summary>
	/// ��ԕω������Ƃ���񂾂��Ă΂��֐�
	/// </summary>
	/// <param name="enemy">��Ԃ��g���Ă�G�̃|�C���^</param>
	virtual void Enter(Enemy* enemy) {};
};


//��Ԃ̃��X�g
namespace EnemyStateList
{
	EnemyState* GetEnemyWaitState();      //�ҋ@��Ԃ̃C���X�^���X�Ԃ�
	EnemyState* GetEnemyMoveState();      //�ړ���Ԃ̃C���X�^���X�Ԃ�
	EnemyState* GetEnemyRotationState();  //��]��Ԃ̃C���X�^���X�Ԃ�
	EnemyState* GetEnemyDieState();	      //���S��Ԃ̃C���X�^���X�Ԃ�
	EnemyState* GetEnemyKnockBackState(); //�m�b�N�o�b�N��Ԃ̃C���X�^���X�Ԃ�
};
