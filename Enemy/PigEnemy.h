#pragma once
#include "Enemy.h"
#include "../Engine/Particle.h"

/// <summary>
/// �؂̓G�N���X
/// </summary>
class PigEnemy : public Enemy
{

	///////////////�G�t�F�N�g///////////////////

	//�G�t�F�N�g�̔ԍ�
	int effectNum_;

	///////////////�m�b�N�o�b�N///////////////////

	//�m�b�N�o�b�N�̕����Ƌ���
	XMVECTOR knockBackDir_;

	//���ԂƂ��̌��ƂȂ��x�N�g��
	XMVECTOR vFly_;

	//���ƂȂ�t���C�x�N�g����ۑ����Ă���
	XMVECTOR keepFly_;

	//�m�b�N�o�b�N�������ǂ���
	bool isKnockBack_;

	///////////////���̑�///////////////////

	//�^�C�����\�b�h�ŌĂ΂�郁�\�b�h��؂�ւ��Ă��邩�ǂ���
	bool isTimeMethodChange_;

public:

	//�R���X�g���N�^
	PigEnemy(GameObject* parent, std::string modelPath, std::string name);
	PigEnemy(GameObject* parent);

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void EnemyChildStartUpdate() override;

	//�X�V
	void EnemyChildUpdate() override;

	/// <summary>
	/// Player�����g�̏�ɂ��邩�ǂ���
	/// </summary>
	/// <returns>true�Ȃ炢��,false�Ȃ炢�Ȃ�</returns>
	bool IsPlayerTop();

	//�m�b�N�o�b�N���Ď��S
	void KnockBackDie() override;

	//���S
	void Die() override;

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
	void OnCollision(GameObject* pTarget) override;
};