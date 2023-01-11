#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// �摜��\����������N���X
/// </summary>
class ImageBase : public GameObject
{

	int hPict_;                   //�摜�ԍ�
	std::string ModelNamePath_;   //�t�@�C���l�[���p�X

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ImageBase(GameObject* parent, std::string modelPath, std::string name);

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
};

