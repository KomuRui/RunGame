#include "PlayScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/CreateStage.h"
#include "../../OtherObject/TitleModel.h"
#include "../PlayScene/PlayStage.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	//���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g
	GameManager::SetpStage(Instantiate<PlayStage>(this));

	//Player�\��(���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g)
	GameManager::SetpPlayer(Instantiate<Player>(this));

	//�t�F�[�h�C��
	GameManager::SetStatus(FADE_IN);
}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void PlayScene::StartUpdate()
{
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}