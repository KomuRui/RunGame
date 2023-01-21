#include "GameManager.h"
#include "../../Engine/Sprite.h"
#include "../CoinManager/CoinManager.h"
#include "../TextManager/TextManager.h"
#include "../../MiniGameTime.h"
#include "../../Engine/Text.h"
#include <cmath>

//定数
namespace
{
	static const float FADE_ADD_DISTANCE = 10.0f; //フェードするときの加算する距離
}

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////変数//////////////////////////////////

	//フェード
	int FadeStatus_;					  //フェードの状態:0 何もしない,1 フェードイン, 2フェードアウト 
	float maxDistance_;					  //フェードで使用する最大距離
	float nowDistance_;                   //フェードで使用する今の距離
	Sprite* pSprite_[SCENE_ID_MAX]; 	  //フェード用の画像(シーンの数分)
	std::string fadeImage_[SCENE_ID_MAX]; //フェード用の画像の文字列(シーンの数分)

	//各オブジェクト
	Player* pNowPlayer_;          //現在使用されているプレイヤーのポインタ格納用
	Stage* pNowStage_;            //現在の使用されているステージのポインタ格納用
	SceneManager* pSceneManager_; //シーンマネージャーのポインタ格納用
	
	//コンボ
	Text* pComboText_;           //コンボの文字表示するテキスト
	Text* pComboNumText_;        //コンボ数表示するテキスト
	XMFLOAT2 comboPositiom_;     //テキストのポジション
	XMFLOAT2 numberPositiom_;    //数字のポジション
	int ComboTotalCount_;        //どのくらいコンボしているか
	float scale_;                //拡大率


	///////////////////////////////関数//////////////////////////////////

	//初期化
	void GameManager::Initialize()
	{
		//コインマネージャーの初期化
		CoinManager::Initialize();

		//テキストマネージャの初期化
		TextManager::Initialize();

		//ミニゲームの初期化
		MiniGameTime::Initialize();

		//変数初期化
		fadeImage_[SCENE_ID_TITLE] = "Image/Fade/Tutorial1Fade.png";
		fadeImage_[SCENE_ID_PLAY] = "Image/Fade/Tutorial1Fade.png";
		ARGUMENT_INITIALIZE(FadeStatus_, NOOP);
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(maxDistance_,std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		ARGUMENT_INITIALIZE(nowDistance_, ZERO);
		ARGUMENT_INITIALIZE(ComboTotalCount_, ZERO);
		ARGUMENT_INITIALIZE(scale_, 1);

		//フェード用の画像ロード
		for (int i = 0; i < SCENE_ID_MAX; i++)
		{
			ARGUMENT_INITIALIZE(pSprite_[i], new Sprite);
			pSprite_[i]->Load(fadeImage_[i]);
		}

		//テキストの初期化
		ARGUMENT_INITIALIZE(pComboText_, new Text);
		pComboText_->Initialize();
		ARGUMENT_INITIALIZE(pComboNumText_, new Text);
		pComboNumText_->Initialize("Text/NumberFont.png", 128, 256, 10);

		//テキストのポジション設定
		comboPositiom_.x = 1450;
		comboPositiom_.y = 400;

		//数字のポジション設定
		numberPositiom_.x = 1590;
		numberPositiom_.y = 260;
	}

	//シーン遷移の時の初期化
	void GameManager::SceneTransitionInitialize()
	{
		//テキストの初期化
		ARGUMENT_INITIALIZE(pComboText_, new Text);
		pComboText_->Initialize();
		ARGUMENT_INITIALIZE(pComboNumText_, new Text);
		pComboNumText_->Initialize("Text/NumberFont.png", 128, 256, 10);
	}

	//Playerが死亡した時にLifeManagerから呼ばれる
	void GameManager::PlayerDie()
	{

	}

	//描画(コインの取得数やPlayerコンボの表示)
	void Draw()
	{
		//もしPlayシーンなら
		if (pSceneManager_->GetSceneId() != SCENE_ID_TITLE)
		{

			//コンボ数が0じゃなければ
			if (ComboTotalCount_ != ZERO)
			{
				//コンボ描画
				pComboText_->Draw(comboPositiom_.x, comboPositiom_.y, L"COMBO", 0.5f);
				pComboNumText_->NumberDraw(numberPositiom_.x, numberPositiom_.y, ComboTotalCount_, scale_);
			}

			//ミニゲーム時間の表示
			MiniGameTime::Draw();

			//コインの取得数の表示
			CoinManager::Draw();
		}

		//フェード用の描画
		FadeDraw();
	}

	///////////////////////////////セットゲット関数//////////////////////////////////
	
	//プレイヤーのポインタセット
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//プレイヤーのポインタゲット
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//ステージのポインタセット
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//ステージのポインタゲット
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//シーンマネージャーのポインタセット
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//シーンマネージャーのポインタゲット
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

	//状態セット
	void GameManager::SetStatus(int status)
	{
		FadeStatus_ = status;

		//状態によって分ける
		switch (FadeStatus_)
		{
			//画像だけ描画
		case DRAW:

			NormalDraw();

			//フェードイン
		case FADE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, ZERO);
			break;

			//フェードアウト
		case FADE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
			break;

			//それ以外
		default:

			break;
		}
	}

	//状態ゲット
	int GameManager::GetStatus() { return FadeStatus_; }

	///////////////////////////////フェード用関数////////////////////////////////////

	//フェード描画
	void GameManager::FadeDraw()
	{
		//状態によって変える
		switch (FadeStatus_)
		{
			//画像だけ描画
			case DRAW:

				NormalDraw();
				break;

			//フェードイン
			case FADE_IN:

				FadeInDraw();
				break;

			//フェードアウト
			case FADE_OUT:

				FadeOutDraw();
				break;

			//それ以外
			default:

				break;
		}
	
	}

	//描画
	void GameManager::NormalDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//描画
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t,rect);
	}

	//フェードイン描画
	void GameManager::FadeInDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//描画
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t, nowDistance_,rect);
	};

	//フェードアウト描画
	void GameManager::FadeOutDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ -= FADE_ADD_DISTANCE;

		if (nowDistance_ < ZERO)
			ARGUMENT_INITIALIZE(nowDistance_, ZERO);

		//描画
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t, nowDistance_, rect);
	};

	///////////////////////////////Combo関数////////////////////////////////////

    //コンボ加算
	void GameManager::AddCombo() { ComboTotalCount_++; }

	//文字の拡大率をセット
	void GameManager::SetTextScale(const float& scale) { scale_ = scale; }

	//コンボの数リセット
	void GameManager::ComboReset() { ComboTotalCount_ = ZERO; }
}