#pragma once
#include "../../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	////�萔

	const float RATATION_SPEED = 0.5f;    //��]���x
	const float BRIGHTNESS = 1.5f;		  //�w�i���f���̖��邳
	const XMFLOAT3 CAM_POS = { 0, 0, 5 }; //�J�����̈ʒu
	const XMFLOAT3 CAM_TAR = { 0, 0, 0 }; //�J�����̃^�[�Q�b�g

	////�ϐ�

	int hModel_; 	//���f���ԍ��i�[�p

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

};

