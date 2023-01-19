#include "PlayStage.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Engine/CreateStage.h"

//コンストラクタ
PlayStage::PlayStage(GameObject* parent)
	:Stage(parent, "PlayStage")
{
	//画角
	fieldAngle_ = 45;

	//ライトの強さ
	lightIntensity_ = 4;
}

//初期化
void PlayStage::Initialize()
{

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	//////ステージ作成
	CreateStage* pCreateStage = new CreateStage;
	//pCreateStage->LoadFileCreateStage(this, "Stage/Tutorial/StageInformation/TutorialStage2.txt");

	/////////////////////モデルデータのロード///////////////////////

	hModel_[Base] = Model::Load("Stage/Play/StraightStage.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	//hModel_[PolyModel] = Model::Load("Stage/Play/StraightStage.fbx");

	///////////////////////////各種設定/////////////////////////////

	//レイの判定にBaseをいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_[Base], true);

	//Spaceモデルの明るさ設定
	Model::SetBrightness(hModel_[Space], 0.5f);
	Model::SetBrightness(hModel_[Base], 1.0f);

	//PolyModelを透明に設定(軸を確認するためだけに使うため)
	//Model::SetAlpha(hModel_[PolyModel], 0);

	//画角
	Camera::SetFieldAngle(fieldAngle_);

	//カメラの上ベクトル
	Camera::SetUpDirection(XMVectorSet(0, 1, 0, 0));

	//ライトの強さ
	Light::SetPlayerIntensity(lightIntensity_);

	//3Dなのでtrueにする
	threeDflag_ = true;

	//球体使用しているのでtrue
	circleFlag_ = true;

}

//更新
void PlayStage::Update()
{
	tSpace_.rotate_.y += 0.1;
}

//描画
void PlayStage::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);
}

//解放
void PlayStage::Release()
{
}
