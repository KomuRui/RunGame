#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// �^�C�g���̃X�^�[�g�摜
/// </summary>
class TitleStartImage : public GameObject
{
	////�ϐ�

	int hPict_Default_;			//�f�t�H���g�摜�ԍ�
	int hPict_A_Select_;		//A�I���摜�ԍ�
	int hPict_RT_Select_;		//RT�I���摜�ԍ�
	int hPict_All_Select_;		//�S�đI���摜�ԍ�
	std::string ModelNamePath_; //�t�@�C���l�[���p�X

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleStartImage(GameObject* parent, std::string modelPath, std::string name);

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

