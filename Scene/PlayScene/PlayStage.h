#pragma once
#include "../../Stage.h"

//ステージクラス
class PlayStage : public Stage
{
	const XMFLOAT3 CAM_POS = { 0, 30, 30 }; //カメラの位置
	const XMFLOAT3 CAM_TAR = { 0, 0, 0 };   //カメラのターゲット

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayStage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};


