#include "CoinManager.h"
#include "../../Engine/Transform.h"
#include "../../Engine/Text.h"
#include "../../Engine/Global.h"
#include "../../Engine/Sprite.h"
#include "../GameManager/GameManager.h"

/// <summary>
/// Player�̎����Ă�R�C���Ǘ�
/// </summary>
namespace CoinManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//�R�C���̑���
	int coinTotalCount;

	//�摜
	Sprite* pCoinImage;             //�R�C���̉摜
	Sprite* pCrossImage;            //�~UI�̉摜
	Transform coinImageTransform_;  //�R�C���摜�̈ʒu�E�g�嗦
	Transform crossImageTransform_; //�~�摜�̈ʒu�E�g�嗦

	//�e�L�X�g
	Text* pCoinText_;           //�R�C���̐��\������e�L�X�g
	XMFLOAT2 textPositiom_;     //�e�L�X�g�̃|�W�V����

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void CoinManager::Initialize()
	{
		//�R�C���̑���������
		ARGUMENT_INITIALIZE(coinTotalCount, ZERO);

		//�摜�̃��[�h
		ARGUMENT_INITIALIZE(pCoinImage, new Sprite);
		ARGUMENT_INITIALIZE(pCrossImage, new Sprite);
		pCoinImage->Load("Image/Coin/Coin.png");
		pCrossImage->Load("Image/Coin/Cross.png");

		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pCoinText_, new Text);
		pCoinText_->Initialize("Text/NumberFont.png", 128, 256, 10);

		//�摜�̃|�W�V�����ݒ�
		ARGUMENT_INITIALIZE(coinImageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "coinImageX", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(coinImageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "coinImageY", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(crossImageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "crossImageX", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(crossImageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "crossImageY", "1", "Image/Coin/CoinPosition.ini"));

		//�e�L�X�g�̃|�W�V�����ݒ�
		ARGUMENT_INITIALIZE(textPositiom_.x, GetPrivateProfilefloat("POSITION", "coinTextX", "1", "Image/Coin/CoinPosition.ini"))
		ARGUMENT_INITIALIZE(textPositiom_.y, GetPrivateProfilefloat("POSITION", "coinTextY", "1", "Image/Coin/CoinPosition.ini"))
	}

	//�V�[���J�ڂ̎��̏�����
	void CoinManager::SceneTransitionInitialize()
	{
		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pCoinText_, new Text);
		pCoinText_->Initialize("Text/NumberFont.png", 128, 256, 10);
	}

	//�R�C�����������Ă��邩�`��
	void CoinManager::Draw()
	{
		//�摜
		{
			//�R�C����1���ȏ�Ȃ�
			if (coinTotalCount > 0)
			{
				if(!GameManager::GetpPlayer()->IsRunMode())
					GameManager::GetpPlayer()->SetRunSpeed(5.0f * (1.0f + (coinTotalCount * 0.2f)));
				else
					GameManager::GetpPlayer()->SetRunSpeed(8.0f * (1.0f + (coinTotalCount * 0.2f)));
			}

			//�e�N�X�`���̃T�C�Y�擾
			XMFLOAT3 size = pCoinImage->GetTextureSize();

			//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
			RECT rect;
			rect.left = ZERO;
			rect.top = ZERO;
			rect.right = (long)size.x;
			rect.bottom = (long)size.y;

			//�`��
			pCoinImage->Draw(coinImageTransform_, rect);
		}

		//�e�L�X�g
		{
			pCoinText_->NumberDraw(textPositiom_.x, textPositiom_.y, coinTotalCount, coinImageTransform_.scale_.x);
		}
	}


	//�R�C���̒ǉ�
	void AddCoin(int num){ coinTotalCount += num; }
}