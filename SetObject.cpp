#include "SetObject.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Manager/GameManager/GameManager.h"

//定数
namespace
{
    static const float RADIUS_SMALL_VALUE = 0.5;  //半径を少しだけ小さくする時の値
    static const int   Z_DISTANCE = 100;          //PlayerZの位置から自身Zまでの距離
    static const int   MIN_GENERATION_SPEED = 30; //最小生成スピード(FPS)
    static const int   MAX_GENERATION_SPEED = 120;//最大生成スピード(FPS)
}

//コンストラクタ
SetObject::SetObject(GameObject* parent, std::string name)
	:GameObject(parent, name),radius_(ZERO), generatingSpeed_(ZERO), fpsCount_(ZERO)
{
}

//初期化
void SetObject::Initialize()
{
    ARGUMENT_INITIALIZE(generatingSpeed_, Random(MIN_GENERATION_SPEED, MAX_GENERATION_SPEED));
}

//更新の前に一度だけ呼ばれる
void SetObject::StartUpdate()
{
    //自身のtransform初期化
    ARGUMENT_INITIALIZE(transform_.position_,GameManager::GetpStage()->GetPosition());
    ARGUMENT_INITIALIZE(transform_.position_.z, GameManager::GetpPlayer()->GetPosition().z + Z_DISTANCE);

    //レイを飛ばして半径を設定する
    RayCastData dataNormal;
    ARGUMENT_INITIALIZE(dataNormal.start,transform_.position_);
    ARGUMENT_INITIALIZE(dataNormal.dir,VectorToFloat3(DOWN_VECTOR));
    Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

    //距離を半径に(求めた距離より少しだけ小さくする)
    ARGUMENT_INITIALIZE(radius_, dataNormal.dist - RADIUS_SMALL_VALUE);
}

//更新
void SetObject::Update()
{
    //オブジェクト生成
    ObjectGeneration();

    //Zの位置更新
    ARGUMENT_INITIALIZE(transform_.position_.z, GameManager::GetpPlayer()->GetPosition().z + Z_DISTANCE);
}

//描画
void SetObject::Draw()
{
}

//解放
void SetObject::Release()
{
}

//オブジェクト生成
void SetObject::ObjectGeneration()
{
    //もし生成のタイミングがきたなら
    if (generatingSpeed_ <= fpsCount_)
    {



        //次の生成スピード設定
        ARGUMENT_INITIALIZE(generatingSpeed_, Random(MIN_GENERATION_SPEED, MAX_GENERATION_SPEED));

        //カウント初期化
        ARGUMENT_INITIALIZE(fpsCount_, ZERO);
    }

    //カウント増やす
    fpsCount_++;
}