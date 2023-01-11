#include "GameManager.h"
#include "../../Engine/Sprite.h"
#include "../CoinManager/CoinManager.h"
#include "../TextManager/TextManager.h"
#include <cmath>

//�萔
namespace
{
	static const float FADE_ADD_DISTANCE = 10.0f; //�t�F�[�h����Ƃ��̉��Z���鋗��
}

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//�t�F�[�h�̏��:0 �������Ȃ�,1 �t�F�[�h�C��, 2�t�F�[�h�A�E�g 
	int FadeStatus_;

	//�t�F�[�h�Ŏg�p����ő勗��
	float maxDistance_;

	//�t�F�[�h�Ŏg�p���鍡�̋���
	float nowDistance_;

	//�t�F�[�h�p�̉摜(�V�[���̐���)
	Sprite* pSprite_[SCENE_ID_MAX];

	//���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	Player* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	//�V�[���}�l�[�W���[�̃|�C���^�i�[�p
	SceneManager* pSceneManager_;

	//�t�F�[�h�p�̉摜�̕�����(�V�[���̐���)
	std::string fadeImage_[SCENE_ID_MAX];

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void GameManager::Initialize()
	{

		//�R�C���}�l�[�W���[�̏�����
		CoinManager::Initialize();

		//�e�L�X�g�}�l�[�W���̏�����
		TextManager::Initialize();

		//�ϐ�������
		fadeImage_[SCENE_ID_TITLE] = "Image/Fade/Tutorial1Fade.png";
		fadeImage_[SCENE_ID_PLAY] = "Image/Fade/Tutorial1Fade.png";
		ARGUMENT_INITIALIZE(FadeStatus_, NOOP);
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(maxDistance_,std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		ARGUMENT_INITIALIZE(nowDistance_, 0);

		//�t�F�[�h�p�̉摜���[�h
		for (int i = 0; i < SCENE_ID_MAX; i++)
		{
			ARGUMENT_INITIALIZE(pSprite_[i], new Sprite);
			pSprite_[i]->Load(fadeImage_[i]);
		}
	}

	//Player�����S��������LifeManager����Ă΂��
	void GameManager::PlayerDie()
	{

	}

	/// <summary>
	/// �`��(�R�C���̎擾����Player���C�t�̕\��)
	/// </summary>
	void Draw()
	{
		//����Play�V�[���Ȃ�
		if (pSceneManager_->GetSceneId() != SCENE_ID_TITLE)
		{
			//�R�C���̎擾���̕\��
			CoinManager::Draw();
		}

		//�t�F�[�h�p�̕`��
		FadeDraw();
	}

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////
	
	//�v���C���[�̃|�C���^�Z�b�g
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//�v���C���[�̃|�C���^�Q�b�g
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//�X�e�[�W�̃|�C���^�Z�b�g
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

	//��ԃZ�b�g
	void GameManager::SetStatus(int status)
	{
		FadeStatus_ = status;

		//��Ԃɂ���ĕ�����
		switch (FadeStatus_)
		{
			//�摜�����`��
		case DRAW:

			NormalDraw();

			//�t�F�[�h�C��
		case FADE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, ZERO);
			break;

			//�t�F�[�h�A�E�g
		case FADE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
			break;

			//����ȊO
		default:

			break;
		}
	}

	//��ԃQ�b�g
	int GameManager::GetStatus() { return FadeStatus_; }

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////

	//�t�F�[�h�`��
	void GameManager::FadeDraw()
	{
		//��Ԃɂ���ĕς���
		switch (FadeStatus_)
		{
			//�摜�����`��
			case DRAW:

				NormalDraw();
				break;

			//�t�F�[�h�C��
			case FADE_IN:

				FadeInDraw();
				break;

			//�t�F�[�h�A�E�g
			case FADE_OUT:

				FadeOutDraw();
				break;

			//����ȊO
			default:

				break;
		}
	
	}

	//�`��
	void GameManager::NormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//�`��
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t,rect);
	}

	//�t�F�[�h�C���`��
	void GameManager::FadeInDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//�`��
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t, nowDistance_,rect);
	};

	//�t�F�[�h�A�E�g�`��
	void GameManager::FadeOutDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ -= FADE_ADD_DISTANCE;

		if (nowDistance_ < ZERO)
			ARGUMENT_INITIALIZE(nowDistance_, ZERO);

		//�`��
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t, nowDistance_, rect);
	};
}