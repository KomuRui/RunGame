#pragma once
#include "../Mob.h"

/// <summary>
/// �u���b�N�̊��N���X(�S�Ẵu���b�N�͂��̃N���X���p�����č��)
/// </summary>
class Block : public Mob
{
protected:

	XMFLOAT3 hitMovePos_;   //Player�ƏՓ˂����ꍇ�̃u���b�N�̃|�W�V����
	XMFLOAT3 initialPos_;   //�����|�W�V����
	bool     isHit_;        //Player�Ɠ������Ă��邩
	bool     roundTripEnd_; //�������I��������ǂ���

public:
	//�R���X�g���N�^
	Block(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void ChildStartUpdate() override;

	///////////�Z�b�^�[////////////

	/// <summary>
	/// �������Ă���̂����Z�b�g����
	/// </summary>
	/// <param name="flag">�������Ă���Ȃ�true,�������Ă��Ȃ��̂Ȃ�false</param>
	void SetIsHit(const bool& flag) { isHit_ = flag; }

	///////////////////�p����p�֐�/////////////////////

	/// <summary>
	/// �p���悲�Ƃ�Update�ł̓�������ς���
	/// </summary>
	virtual void BlockChildUpdate() {};

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void BlockChildInitialize() {};

	/// <summary>
	/// �p����p�̕`��
	/// </summary>
	virtual void BlockChildDraw() {};

	/// <summary>
	/// �p����p�̃X�^�[�g�A�b�v�f�[�g
	/// </summary>
	virtual void BlockChildStartUpdate() {};

	/// <summary>
	/// Player�������瓖���������̋���
	/// </summary>
	virtual void HitToLowerPlayer();

	/// <summary>
	/// �p����p��Player�������瓖���������̋���
	/// </summary>
	virtual void BlockChildHitToLowerPlayer() {};

	/// <summary>
	/// �p����p�̃R���C�_�[�����������ɌĂ΂��֐�
	/// </summary>
	/// <param name="pTarget">������������̃|�C���^</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// �p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	/// </summary>
	virtual void TimeMethod() override {};

};

