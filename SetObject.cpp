#include "SetObject.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Gimmick/Coin.h"
#include "Enemy/PigEnemy.h"
#include "Block/NormalBlock.h"
#include "Block/BrickBlock.h"
#include "MiniGameTime.h"
#include "Manager/GameManager/GameManager.h"

//定数
namespace
{
    static const float RADIUS_SMALL_VALUE = 3.0;  //半径を少しだけ小さくする時の値
    static const int   Z_DISTANCE = 200;          //PlayerZの位置から自身Zまでの距離
    static const int   MIN_GENERATION_SPEED = 30; //最小生成スピード(FPS)
    static const int   MAX_GENERATION_SPEED = 60;//最大生成スピード(FPS)
    static const int   MIN_ANGLE = 0;             //最小角度
    static const int   MAX_ANGLE = 360;           //最大角度
}

//コンストラクタ
SetObject::SetObject(GameObject* parent)
	:GameObject(parent, "SetObject"),radius_(ZERO), generatingSpeed_(ZERO), fpsCount_(ZERO)
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
    //Playerがいなければこの先処理しない
    if (GameManager::GetpPlayer() == nullptr) return;

    //ミニゲームがスタートしているかつPlayerが死んでいないのならオブジェクト生成
    if (MiniGameTime::IsPlay() && !GameManager::GetpPlayer()->isDie())
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
        //生成
        Generation();

        //次の生成スピード設定
        ARGUMENT_INITIALIZE(generatingSpeed_, Random(MIN_GENERATION_SPEED, MAX_GENERATION_SPEED));

        //カウント初期化
        ARGUMENT_INITIALIZE(fpsCount_, ZERO);
    }

    //カウント増やす
    fpsCount_++;
}

//生成
void SetObject::Generation()
{	
    //回転行列作成
    XMMATRIX m = XMMatrixRotationZ(XMConvertToRadians(Random(MIN_ANGLE, MAX_ANGLE)));

    //ベクトルを回す
    XMVECTOR v = XMVector3Normalize(XMVector3TransformCoord(DOWN_VECTOR, m)) * radius_;

    //オブジェクトの位置を求める
    XMFLOAT3 pos = Float3Add(transform_.position_, VectorToFloat3(v));
    
    int num = rand() % 4;

    //コイン
    if (num == 0)
    {
        Coin* pCoin = Instantiate<Coin>(GetParent());
        pCoin->SetPosition(pos);
    }
    //豚の敵
    else if (num == 1)
    {
        //何体出現するか
        int r = Random(1, 3);

        //r体分出現させる
        for (int i = 0; i < r; i++)
        {
            pos.z += i * 8;
            PigEnemy* pCoin = Instantiate<PigEnemy>(GetParent());
            pCoin->SetPosition(pos); 
        }
    }
    //ブロック
    else if (num == 2)
    {
        NormalBlock* pNormalBlock = Instantiate<NormalBlock>(GetParent());
        pNormalBlock->SetPosition(pos);
    }
    else if (num == 3)
    {
        BrickBlock* pBrickBlock = Instantiate<BrickBlock>(GetParent());
        pBrickBlock->SetPosition(transform_.position_);
    }
}