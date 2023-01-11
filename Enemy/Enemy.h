#pragma once
#include "../Mob.h"
#include "../Engine/Fbx.h"
#include "../State/EnemyState/EnemyState.h"

/// <summary>
/// �G�̊��N���X(�X�e�[�g�x�[�XAI)
/// </summary>
class Enemy : public Mob
{
protected:

	///////////////�L�����̕K�v�ȏ��///////////////////

	XMVECTOR front_;        //�L�����̑O�����̃x�N�g��
	XMFLOAT3 basePos_;      //�T������Ƃ��̃x�[�X�|�W�V����
	bool isUseGravity_;     //�d�͎g�����ǂ���
	int rotationAngle_;     //��]�p�x
	int rotationSign_;      //��]����
	float dotX_;            //���ς̌v�Z�����l������
	float rotationTotal_;   //�ǂ̂��炢��]������

	///////////////�G�̓����p�^�[��////////////////

	EnemyState* pState_;    //���

	int operationTime_;     //���̏�Ԃɕς��܂ł̎���
	int stateCount_;        //���̏�ԂɂȂ��Ă���ǂ̂��炢�̕b����������

	///////////////���̑�///////////////////

	int    hGroundModel_;   //�X�e�[�W�̃��f���ԍ�������ϐ�
	float acceleration;     //�d�͂̉����x


public:
	//�R���X�g���N�^
	Enemy(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void ChildStartUpdate() override;

	///////////////////�֐�/////////////////////

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
	/// �L�����̓���(�~�p)
	/// </summary>
	void MovingOperation();

	/// <summary>
	/// �T���͈͓��ɂ��邩�ǂ���
	/// </summary>
	/// <returns>true�Ȃ炢��,false�Ȃ炢�Ȃ�</returns>
	bool IsInSearchRange();

	/// <summary>
	/// ���f���ԍ��擾
	/// </summary>
	/// <returns>���f���ԍ�</returns>
	int GetModelNumber() { return hModel_; }

	/// <summary>
	/// �㎲�̊p�x�Q�b�g
	/// </summary>
	/// <returns>�㎲�̊p�x</returns>
	float GetAngle() { return angle_; }

	/// <summary>
	/// �㎲�̏㎲�̊p�x���Z�b�g
	/// </summary>
	/// <param name="angle">�Z�b�g�������p�x</param>
	void SetAngle(const float& angle) { angle_ = angle; }

	/// <summary>
	/// ���̏�Ԃɕς��܂ł̎��Ԃ��Z�b�g
	/// </summary>
	/// <param name="time">�Z�b�g���������̏�Ԃɕς��܂ł̎���</param>
	void SetOperationTime(const int& time) { operationTime_ = time; }

	/// <summary>
	/// ���̏�ԂɂȂ��Ă���ǂ̂��炢�̕b�������������Z�b�g
	/// </summary>
	/// <param name="count">�Z�b�g�������b��</param>
	void SetStateCount(const int& count) { stateCount_ = count; }

	/// <summary>
	/// ���̏�ԂɂȂ��Ă���ǂ̂��炢�̕b����������
	/// </summary>
	/// <returns>���̏�ԂɂȂ��Ă���ǂ̂��炢�̕b����������</returns>
	int GetStateCount() { return stateCount_; }

	/// <summary>
	/// �ǂ����ɉ�]���邩(����)
	/// </summary>
	/// <param name="sign">�Z�b�g����������(1��-1)</param>
	void SetRotationSign(const int& sign) { rotationSign_ = sign; }

	/// <summary>
	/// ��]�p�x�Z�b�g
	/// </summary>
	/// <param name="angle">�Z�b�g��������]�p�x</param>
	void SetRotationAngle(const int& angle) { rotationAngle_ = angle; }

	/// <summary>
	/// �ǂ̂��炢��]�������Z�b�g
	/// </summary>
	/// <param name="total">�ǂ̂��炢��]������</param>
	void SetRotationTotal(const float& total) { rotationTotal_ = total; }

	///////////////////AI�p�֐�/////////////////////

	/// <summary>
	/// �ҋ@
	/// </summary>
	virtual void Wait();

	/// <summary>
	/// �ړ�
	/// </summary>
	virtual void Move();

    /// <summary>
    /// ��]
    /// </summary>
	virtual void Rotation();

	/// <summary>
	/// �m�b�N�o�b�N���Ď��S
	/// </summary>
	virtual void KnockBackDie() {};

	/// <summary>
	/// ���S
	/// </summary>
	virtual void Die() {};

	/// <summary>
	/// Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
	/// </summary>
	virtual void PlayerNearWithIsCheck();

	/// <summary>
	/// ��Ԃ��Q�b�g
	/// </summary>
	/// <returns>���݂̏��</returns>
	EnemyState* GetEnemyState() { return pState_; }

	/// <summary>
	/// ��ԃ`�F���W
	/// </summary>
	/// <param name="state">�`�F���W���������</param>
	void ChangeEnemyState(EnemyState* state);

	///////////////////�p����p�֐�/////////////////////

	/// <summary>
	/// �p���悲�Ƃ�Update�ł̓�������ς���
	/// </summary>
	virtual void EnemyChildUpdate() {};

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void EnemyChildInitialize() {};

	/// <summary>
	/// �p����p�̕`��
	/// </summary>
	virtual void EnemyChildDraw() {};

	/// <summary>
	/// �p����p�̃X�^�[�g�A�b�v�f�[�g
	/// </summary>
	virtual void EnemyChildStartUpdate() {};

	/// <summary>
	/// Player�����p���A�w�苗�����ɂ������̏���(�p���p)
	/// </summary>
	virtual void PlayerWithIf() {};

	/// <summary>
	/// Player�����p���A�w�苗�����ɂ��Ȃ����̏���(�p���p)
	/// </summary>
	virtual void NotPlayerWithIf() {};

	/// <summary>
	/// �p����p�̃R���C�_�[�����������ɌĂ΂��֐�
	/// </summary>
	/// <param name="pTarget">���������I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// �p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	/// </summary>
	virtual void TimeMethod() override {};
};

