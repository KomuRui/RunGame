#pragma once
#include "../Engine/GameObject.h"

//�^�C�g����Player���f��
class TitleModelPlayer : public GameObject
{
	//���f���ԍ�
	int hModel_;

public:

	//�R���X�g���N�^
	TitleModelPlayer(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

