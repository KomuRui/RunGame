#include "EnemyState.h"
#include "EnemyDieState.h"
#include "EnemyKnockBackState.h"
#include "EnemyMoveState.h"
#include "EnemyRotationState.h"
#include "EnemyWaitState.h"

//��Ԃ̃��X�g
namespace EnemyStateList
{
	//�e��ԕϐ�
	static EnemyDieState* EnemyDie_ = new EnemyDieState;                   //���S
	static EnemyKnockBackState* EnemyKnockBack_ = new EnemyKnockBackState; //�m�b�N�o�b�N
	static EnemyMoveState* EnemyMove_ = new EnemyMoveState;		           //�ړ�
	static EnemyRotationState* EnemyRotation_ = new EnemyRotationState;    //��]
	static EnemyWaitState* EnemyWait_ = new EnemyWaitState;		           //�ҋ@

	EnemyState* GetEnemyWaitState() { return EnemyWait_; }			 //�ҋ@��Ԃ̃C���X�^���X�Ԃ�
	EnemyState* GetEnemyMoveState() { return EnemyMove_; }			 //�ړ���Ԃ̃C���X�^���X�Ԃ�
	EnemyState* GetEnemyRotationState() { return EnemyRotation_; }	 //��]��Ԃ̃C���X�^���X�Ԃ�
	EnemyState* GetEnemyDieState() { return EnemyDie_; }			 //���S��Ԃ̃C���X�^���X�Ԃ�
	EnemyState* GetEnemyKnockBackState() { return EnemyKnockBack_; };//�m�b�N�o�b�N��Ԃ̃C���X�^���X�Ԃ�
}

