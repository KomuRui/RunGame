#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 障害物を設置するクラス
/// </summary>
class SetObject : public GameObject
{
	int radius_;             //ステージの半径
	int fpsCount_;           //どのくらいfpsがたっているか
	int generatingSpeed_;    //生成スピード

public:

	//コンストラクタ
	SetObject(GameObject* parent, std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	/////////////////////////関数//////////////////////////

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	void ObjectGeneration();
};

