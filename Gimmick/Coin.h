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
	//�G�t�F�N�g�̔ԍ�
	int effectNumber_;

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

	//�R���X�g���N�^
	Coin(GameObject* parent);

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	//�J��
	void ChildRelease() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	/// <summary>
	/// �^���̖@���𒲂ׂăL�����̏㎲�����肷��
	/// </summary>
	/// <param name="data">�����蔻��ɕK�v�ȃf�[�^</param>
	void CheckUnderNormal(const RayCastData& data);

	/// <summary>
	/// ���C�œ����蔻��(3D�p)
	/// </summary>
	/// <param name="data">�����蔻��ɕK�v�ȃf�[�^</param>
	void StageRayCast(const RayCastData& data);

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
