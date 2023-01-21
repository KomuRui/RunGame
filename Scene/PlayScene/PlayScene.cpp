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

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	//これから使うステージのポインタをGameManagerにセット
	GameManager::SetpStage(Instantiate<PlayStage>(this));

	//Player表示(これから使うステージのポインタをGameManagerにセット)
	GameManager::SetpPlayer(Instantiate<Player>(this));

	//オブジェクトセット用
	Instantiate<SetObject>(this);

	//フェードイン
	GameManager::SetStatus(FADE_IN);
}

//更新の前に一度だけ呼ばれる更新
void PlayScene::StartUpdate()
{
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}