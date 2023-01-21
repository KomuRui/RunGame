#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Text.h"

//Playシーンを管理するクラス
class PlayScene : public GameObject
{

	//スタートするまでのカウントを表示するための文字表示変数
	Text* pStartCountText_;

	//スタートするまでのカウント
	int startCount_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新の前に一度だけ呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

