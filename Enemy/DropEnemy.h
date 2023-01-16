#pragma once
#include "Enemy.h"
#include "../Engine/Particle.h"

/// <summary>
/// ���ʂ݂����ȓG�̃N���X
/// </summary>
class DropEnemy : public Enemy
{
	///////////////�G�t�F�N�g///////////////////

	//�G�t�F�N�g�̔ԍ�
	int effectNum_;

	///////////////���f��///////////////////

	//���̃��f��
	int hHedModel_; 

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
	DropEnemy(GameObject* parent, std::string modelPath, std::string name);
	DropEnemy(GameObject* parent);

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void EnemyChildStartUpdate() override;

	//�X�V
	void EnemyChildUpdate() override;

	//�`��
	void EnemyChildDraw() override;

	//Player�����p���A�w�苗�����ɂ��鎞�̏���
	void PlayerWithIf() override;

	//Player�����p���A�w�苗�����ɂ��Ȃ����̏���
	void NotPlayerWithIf() override;

	//�m�b�N�o�b�N���Ď��S
	void KnockBackDie() override;

	//���S
	void Die() override;

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
	void OnCollision(GameObject* pTarget) override;
};

