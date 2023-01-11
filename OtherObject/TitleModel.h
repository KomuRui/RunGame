#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Particle.h"

//�^�C�g���̃��f��
class TitleModel : public GameObject
{
	////�ϐ�

	XMVECTOR  beforeScale_;		  //��Ԃ���O�̊g�嗦�ۑ�
	XMVECTOR  targetScale_;       //���̖ڕW�Ƃ���g�嗦
	Particle* pSceneChabgeEffect_;//�V�[���ύX�G�t�F�N�g
	int hModel_;   				  //���f���ԍ�

public:

	//�R���X�g���N�^
	TitleModel(GameObject* parent);

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

	////////////////////////////�֐�///////////////////////////////

	/// <summary>
	/// �V�[���ύX�G�t�F�N�g
	/// </summary>
	void SceneChangeEffect();
};

