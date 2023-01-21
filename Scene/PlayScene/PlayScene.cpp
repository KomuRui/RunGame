#include "PlayScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../SetObject.h"
#include "../../Player.h"
#include "../../MiniGameTime.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "../../Engine/Light.h"
#include "../../Engine/CreateStage.h"
#include "../../Engine/Time.h"
#include "../../OtherObject/TitleModel.h"
#include "../PlayScene/PlayStage.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), startCount_(3), pStartCountText_(new Text)
{
}

//������
void PlayScene::Initialize()
{
	//����������
	pStartCountText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g
	GameManager::SetpStage(Instantiate<PlayStage>(this));

	//Player�\��(���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g)
	GameManager::SetpPlayer(Instantiate<Player>(this));

	//�I�u�W�F�N�g�Z�b�g�p
	Instantiate<SetObject>(this);

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
	pStartCountText_->NumberDraw(960, 540, startCount_, 5.0f);
}

//�J��
void PlayScene::Release()
{
}