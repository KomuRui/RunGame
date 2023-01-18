#include "GameManager.h"
#include "../../Engine/Sprite.h"
#include "../CoinManager/CoinManager.h"
#include "../TextManager/TextManager.h"
#include "../../Engine/Text.h"
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

	//�t�F�[�h
	int FadeStatus_;					  //�t�F�[�h�̏��:0 �������Ȃ�,1 �t�F�[�h�C��, 2�t�F�[�h�A�E�g 
	float maxDistance_;					  //�t�F�[�h�Ŏg�p����ő勗��
	float nowDistance_;                   //�t�F�[�h�Ŏg�p���鍡�̋���
	Sprite* pSprite_[SCENE_ID_MAX]; 	  //�t�F�[�h�p�̉摜(�V�[���̐���)
	std::string fadeImage_[SCENE_ID_MAX]; //�t�F�[�h�p�̉摜�̕�����(�V�[���̐���)

	//�e�I�u�W�F�N�g
	Player* pNowPlayer_;          //���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	Stage* pNowStage_;            //���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	SceneManager* pSceneManager_; //�V�[���}�l�[�W���[�̃|�C���^�i�[�p
	
	//�R���{
	Text* pComboText_;           //�R���{���\������e�L�X�g
	XMFLOAT2 comboPositiom_;     //�e�L�X�g�̃|�W�V����
	int ComboTotalCount_;        //�ǂ̂��炢�R���{���Ă��邩


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
		ARGUMENT_INITIALIZE(ComboTotalCount_, 0);

		//�t�F�[�h�p�̉摜���[�h
		for (int i = 0; i < SCENE_ID_MAX; i++)
		{
			ARGUMENT_INITIALIZE(pSprite_[i], new Sprite);
			pSprite_[i]->Load(fadeImage_[i]);
		}

		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pComboText_, new Text);
		pComboText_->Initialize();

		//�e�L�X�g�̃|�W�V�����ݒ�
		comboPositiom_.x = 1300;
		comboPositiom_.y = 200;
	}

	//�V�[���J�ڂ̎��̏�����
	void GameManager::SceneTransitionInitialize()
	{
		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pComboText_, new Text);
		pComboText_->Initialize();
	}

	//Player�����S��������LifeManager����Ă΂��
	void GameManager::PlayerDie()
	{

	}

	//�`��(�R�C���̎擾����Player�R���{�̕\��)
	void Draw()
	{
		//����Play�V�[���Ȃ�
		if (pSceneManager_->GetSceneId() != SCENE_ID_TITLE)
		{

			//�R���{����0����Ȃ����
			if (ComboTotalCount_ != ZERO)
			{
				//���C�h������ɕϊ�
				wchar_t wtext[FILENAME_MAX];
				std::string text = std::to_string(ComboTotalCount_) + "�R���{";
				size_t ret;
				setlocale(LC_ALL, ".932");
				mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

				//�R���{�`��
				pComboText_->Draw(comboPositiom_.x, comboPositiom_.y, wtext);
			}

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

	///////////////////////////////Combo�֐�////////////////////////////////////

    //�R���{���Z
	void GameManager::AddCombo() { ComboTotalCount_++; }
}