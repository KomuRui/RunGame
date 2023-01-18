#include "sceneManager.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Light.h"
#include "../Scene/TitleScene/TitleScene.h"
#include "../Scene/PlayScene/PlayScene.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"), loadDrawFlag_(true)
{
}

//������
void SceneManager::Initialize()
{
	//���g��ǉ�
	GameManager::SetpSceneManager(this);

	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���[�h���ɕ`�悷��Ȃ�
		if (loadDrawFlag_)
		{
			//���[�h���Ă���Ƃ��p�̉摜�\��(�����\���������̂ŕ`��I�����Ă�)
			GameManager::SetStatus(DRAW);
			Direct3D::EndDraw();
		}

		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		PlayerEffectManager::AllRelease();
		EnemyEffectManager::AllRelease();
		CoinEffectManager::AllRelease();
		Audio::AllRelease();
		Model::AllRelease();
		Image::AllRelease();

		//���낢�돉������Ԃɂ��Ă���
		Light::Initialize();
		CoinManager::SceneTransitionInitialize();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:     Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY:      Instantiate<PlayScene>(this); break;
		}
		currentSceneID_ = nextSceneID_;

		//���[�h���ɕ`�悷��ɏ��������Ă���
		ARGUMENT_INITIALIZE(loadDrawFlag_, true);
	}

}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

void SceneManager::StartUpdate()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;

}

//���݂̃V�[��ID�Q�b�g
SCENE_ID SceneManager::GetSceneId()
{
	return nextSceneID_;
}

//���[�h�����Ă鎞�ɉ摜�\�����邩�Z�b�g����
void SceneManager::SetLoadDrawFlag(bool flag)
{
	ARGUMENT_INITIALIZE(loadDrawFlag_, flag);
}