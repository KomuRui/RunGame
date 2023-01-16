#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ��Q����ݒu����N���X
/// </summary>
class SetObject : public GameObject
{
	int radius_;             //�X�e�[�W�̔��a
	int fpsCount_;           //�ǂ̂��炢fps�������Ă��邩
	int generatingSpeed_;    //�����X�s�[�h

public:

	//�R���X�g���N�^
	SetObject(GameObject* parent, std::string name);

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

	/////////////////////////�֐�//////////////////////////

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	void ObjectGeneration();
};

