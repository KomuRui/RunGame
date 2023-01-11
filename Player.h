#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Particle.h"
#include "Engine/Fbx.h"
#include "State/PlayerState/PlayerStateManager.h"
#include "Engine/Model.h"


/// <summary>
/// Player�̊�{�N���X
/// </summary>
class Player : public GameObject
{

	///////////////�L�����̕K�v�ȏ��///////////////////

	////�ϐ�

	Particle* pParticle_;                   //�G�t�F�N�g�\������̂ɕK�v�ȕϐ�
	 
	XMMATRIX mPreviousAngle_;               //�W�����v���Ă���Ƃ��̃}�g���N�X
	XMMATRIX totalMx_;					    //�L�����̉����̂��܂܂ł̃}�g���N�X�̑����}�g���N�X

	XMFLOAT3 beforePos_;                    //�ړ�����O�̃|�W�V����
	XMVECTOR front_;                        //�L�����̑O�����̃x�N�g��
	XMVECTOR up_;                           //�L�����̏�x�N�g��
	XMVECTOR down_;					        //�L�����̉��x�N�g��
	XMVECTOR vNormal_;                      //�L�����̉��̃X�e�[�W�̖@��
	XMVECTOR vJamp_;                        //�W�����v����Ƃ��̌��ƂȂ��x�N�g��
	XMVECTOR keepJamp_;                     //���ƂƂȂ�W�����v�x�N�g����ۑ����Ă���

	float angle_;                           //�L�����̏�̎��̊p�x
	float jampRotationPreviousAngle_;       //�W�����v���Ă���Ƃ��̊p�x
	float acceleration_;                    //�d�͂̉����x

    int   hModel_;                          //���f���ԍ�
	int   rotationCount_;                   //��]���Ă���ǂ̂��炢�̃t���[������������

	bool  normalFlag_;                      //�@���𒲂ׂ邩�ǂ���

	///////////////�J����///////////////////

	////�ϐ�

	enum Cam
	{
		LONG,          //������
		SHORT,         //�ߋ���
		MAX_CAM_SIZE
	};

	XMVECTOR camVec_[MAX_CAM_SIZE];    //Player����J�����܂ł̋���  
	XMMATRIX camMat_;                  //�J�����̊p�x��ύX���邽�߂̃}�g���N�X
	
    int   camStatus_;                  //�J�����̏��
	float camAngle_;                   //�J�����̊p�x
	bool  camPosFlag_;                 //�J�����̃|�W�V�����������ǂ���
	bool  camFlag_;                    //�J�������삷�邩�ǂ���

	///////////////�����蔻��///////////////////

	////�ϐ�

	Stage* pstage_;                           //�X�e�[�W�N���X�̃|�C���^
	int      hGroundModel_;                   //�X�e�[�W�̃��f���ԍ�������ϐ�

	////2D�̍ۂ̃u���b�N�Ƃ̓����蔻��Ɏg��

	enum BlockHitTest2D						  
	{
		Right = 0,                            //�E
		Left,                                 //��
		Under,                                //��
		Top,                                  //��
	};

public:

	/// <summary>
	/// Player�̏�Ԃ�\���ϐ�
	/// </summary>
	PlayerStateManager* pState_;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	/////////////////////�֐�//////////////////////

	/// <summary>
	/// �J�����̏���
	/// </summary>
	void CameraBehavior();

	/// <summary>
	/// �^���̖@���𒲂ׂăL�����̏㎲�����肷��
	/// </summary>
	void CheckUnderNormal();

	/// <summary>
	/// �X�e�[�W�ɍ��킹��Player����]����(3D�p)
	/// </summary>
	void RotationInStage();

	/// <summary>
	/// �X�e�[�W�ɍ��킹��Player����]����(2D�p)
	/// </summary>
	void RotationInStage2D();

	/// <summary>
	/// ���C�œ����蔻��(3D�p)
	/// </summary>
	void StageRayCast();

	/// <summary>
	/// ���C�œ����蔻��(2D�p)
	/// </summary>
	void StageRayCast2D();

	/// <summary>
	/// �����蔻��(3D�p)
	/// </summary>
	/// <param name="data"></param>
	/// <param name="dir">�����蔻�肷�����</param>
	void HitTest(RayCastData* data, const XMVECTOR& dir);

	/// <summary>
	/// �����蔻��(2D�p)
	/// </summary>
	/// <param name="data"></param>
	/// <param name="dir">�����蔻�肷�����</param>
	void HitTest2D(RayCastData* data,const XMVECTOR& dir);

	/// <summary>
	/// �v���C���[����(3D�p)
	/// </summary>
	void MovingOperation();

	/// <summary>
	/// �v���C���[����(2D�p)
	/// </summary>
	void MovingOperation2D();

	/// <summary>
	/// �w�肵�����ԂŌĂ΂�郁�\�b�h
	/// </summary>
	void TimeMethod() override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="pTarget">������������̃|�C���^</param>
	void OnCollision(GameObject* pTarget) override;

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	/// <summary>
	/// Player��^�t�̏�Ԃɐݒ�(�܂��������΂ɐݒ肷��ƊO�ς��O�ɂȂ��Ă��܂��̂ŏ������炷)
	/// </summary>
	void SetInverseNormalAndDown() { vNormal_ += {0, 0.1f, 0, 0}; vNormal_ = -vNormal_;down_ = -vNormal_; }

	/// <summary>
	/// �J�����̈ʒu�𓮂������Z�b�g
	/// </summary>
	void SetCamPosNotMove() { camPosFlag_ = false; }

	/// <summary>
	/// �L���������̖@�����ׂ邩�ǂ������Z�b�g
	/// </summary>
	/// <param name="flag">���ׂ�Ȃ�true,���ׂȂ��Ȃ�false</param>
	void SetCheckNormal(const bool& flag) { normalFlag_ = flag; }

	/// <summary>
	/// �J�������삵�Ă��邩�ǂ���
	/// </summary>
	/// <returns>���삵�Ă�Ȃ�true,���ĂȂ��Ȃ�false</returns>
	bool IsCamBehavior() { return camFlag_; }

	/// <summary>
	/// Player����]���Ă��邩�ǂ���
	/// </summary>
	/// <returns>��]���Ă���Ȃ�true,���Ă��Ȃ��Ȃ�false</returns>
	bool IsRotation() { return (PlayerStateManager::playerState_ == PlayerStateManager::playerJumpRotationning_ || PlayerStateManager::playerState_ == PlayerStateManager::playerRotationning_); }

	/// <summary>
	/// �L�����̉��̃X�e�[�W�̖@�����Q�b�g
	/// </summary>
	/// <returns>�X�e�[�W�̖@��</returns>
	XMVECTOR GetNormal() { return vNormal_; }

	/// <summary>
	/// �L�����̏㎲�Q�b�g
	/// </summary>
	/// <returns>�L�����̏㎲</returns>
	XMVECTOR GetUp() { return up_; }

	/// <summary>
	/// �L�����̏㎲�̊p�x���Q�b�g
	/// </summary>
	/// <returns>�L�����̏㎲�̊p�x</returns>
	float GetAngle() { return angle_; }

	/// <summary>
	/// �L�����̏㎲�̊p�x���Z�b�g����
	/// </summary>
	/// <param name="angle">�Z�b�g�������p�x</param>
	void SetAngle(const float& angle) { angle_ = angle; }

	/// <summary>
	/// �d�͂��Z�b�g
	/// </summary>
	/// <param name="acceleration">�Z�b�g�������d�͂̒l</param>
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }

	/// <summary>
	/// Player�̃��f���ԍ����Q�b�g
	/// </summary>
	/// <returns>Player�̃��f���ԍ�</returns>
	int GetPlayerhModel() { return hModel_; }

	/// <summary>
	/// �W�����v�������̎��̊p�x�ݒ�
	/// </summary>
	/// <param name="angle">�Z�b�g�������W�����v�������̎��̊p�x</param>
	void SetJampRotationPreviousAngle(const float& angle) { jampRotationPreviousAngle_ = angle; }

	/// <summary>
	/// �W�����v���Ă鎞��Player�̉�]�}�g���N�X�Q�b�g
	/// </summary>
	/// <returns>�W�����v���Ă鎞��Player�̉�]�}�g���N�X</returns>
	XMMATRIX GetmPreviousAngle() { return mPreviousAngle_; }

	/// <summary>
	/// Player�̉�]�}�g���N�X�Q�b�g
	/// </summary>
	/// <returns>Player�̉�]�}�g���N�X</returns>
	XMMATRIX GetmmRotate() { return transform_.mmRotate_; }

	/// <summary>
	/// Player�̉��x�N�g���Q�b�g
	/// </summary>
	/// <returns>Player�̉��x�N�g��</returns>
	XMVECTOR GetDown() { return down_; }

	/// <summary>
	/// �J�����̊p�x�Q�b�g
	/// </summary>
	/// <returns>�J�����̊p�x</returns>
	float GetCamAngle() { return camAngle_; }

	/// <summary>
	/// �J�������삷�邩�ǂ������Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ瓮�삳����,false�Ȃ瓮�삳���Ȃ�</param>
	void SetCamFlag(const bool& flag) { camFlag_ = flag; }

	/// <summary>
	/// �A�j���[�V�������邩�ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�A�j���[�V��������,false�Ȃ�A�j���[�V�������Ȃ�</param>
	void SetAnimFlag(const bool& flag) { Model::SetAnimFlag(hModel_,flag); }

	/// <summary>
	/// �J�����̃A���O���ߋ����ɃZ�b�g
	/// </summary>
	void SetCamShort() { camStatus_ = SHORT; CameraBehavior();}

	/// <summary>
	/// �J�����̃A���O���������ɃZ�b�g
	/// </summary>
	void SetCamLong() { camStatus_ = LONG; CameraBehavior(); }
};

