#pragma once
#include "../../Stage.h"

//�X�e�[�W�N���X
class PlayStage : public Stage
{
	const XMFLOAT3 CAM_POS = { 0, 30, 30 }; //�J�����̈ʒu
	const XMFLOAT3 CAM_TAR = { 0, 0, 0 };   //�J�����̃^�[�Q�b�g

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayStage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};


