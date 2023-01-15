#pragma once
#include "../Mob.h"

//�R�C���̌^(�ʂ̃N���X�ł��ݒ肵�����̂ŊO�ɏo��)
enum CoinType
{
	RotationType = 0, //��]���
	BlockCoinType,    //�u���b�N����o�������R�C��
};

/// <summary>
/// �R�C���N���X
/// </summary>
class Coin : public Mob
{
	//�^
	int type_;

	//����
	int sign_;

	//�^�C�����\�b�h�̎��
	enum  TimeMethodType
	{
		SignChange = 0, //�����`�F���W
		Kill            //���g�폜
	};

	//�ǂ̃^�C�����\�b�h���ĂԂ�
	int timeMethodStatus_;

public:

	//�R���X�g���N�^
	Coin(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	/// <summary>
	/// �u���b�N����R�C���o�����̋���
	/// </summary>
	void BlockCoinBehavior();

	/// <summary>
	/// ��]
	/// </summary>
	void Rotation();

	/// <summary>
	/// �^���Z�b�g
	/// </summary>
	/// <param name="num">�Z�b�g�������^</param>
	void SetType(const int& num) { type_ = num; }
};