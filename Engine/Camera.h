#pragma once
#include "GameObject.h"

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//�J�����̐U��
	XMFLOAT3 Vibration();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(const XMFLOAT3& position);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(const XMFLOAT3& target);

	//������̃x�N�g����ݒ�
	void SetUpDirection(XMVECTOR direction);

	//��p��ݒ�
	void SetFieldAngle(int angle);

	//�J�����U����ݒ�
	//���� : �U���̋���
	void SetCameraVibration(float strength, float attenuation = 0.01f);

	//�ʒu���擾
	XMFLOAT3 GetPosition();

	//�œ_���擾
	XMFLOAT3 GetTarget();

	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();

	//�r���{�[�h�p��]�s����擾
	XMMATRIX GetBillboardMatrix();
};