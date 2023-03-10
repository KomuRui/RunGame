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

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"), loadDrawFlag_(true)
{
}

//初期化
void SceneManager::Initialize()
{
	//自身を追加
	GameManager::SetpSceneManager(this);

	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//ロード中に描画するなら
		if (loadDrawFlag_)
		{
			//ロードしているとき用の画像表示(すぐ表示したいので描画終了を呼ぶ)
			GameManager::SetStatus(DRAW);
			Direct3D::EndDraw();
		}

		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		PlayerEffectManager::AllRelease();
		EnemyEffectManager::AllRelease();
		CoinEffectManager::AllRelease();
		Audio::AllRelease();
		Model::AllRelease();
		Image::AllRelease();

		//いろいろ初期化状態にしておく
		Light::Initialize();
		CoinManager::SceneTransitionInitialize();
		GameManager::SceneTransitionInitialize();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:     Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY:      Instantiate<PlayScene>(this); break;
		}
		currentSceneID_ = nextSceneID_;

		//ロード中に描画するに初期化しておく
		ARGUMENT_INITIALIZE(loadDrawFlag_, true);
	}

}

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

void SceneManager::StartUpdate()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;

}

//現在のシーンIDゲット
SCENE_ID SceneManager::GetSceneId()
{
	return nextSceneID_;
}

//ロードをしてる時に画像表示するかセットする
void SceneManager::SetLoadDrawFlag(bool flag)
{
	ARGUMENT_INITIALIZE(loadDrawFlag_, flag);
}