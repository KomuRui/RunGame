#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Text.h"

//Play�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{

	//�X�^�[�g����܂ł̃J�E���g��\�����邽�߂̕����\���ϐ�
	Text* pStartCountText_;

	//�X�^�[�g����܂ł̃J�E���g
	int startCount_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

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

};

