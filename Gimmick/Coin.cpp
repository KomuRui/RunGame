#include "Coin.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"

//定数
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.08f;		    //回転するときの加算する角度
	static const float BLOCK_ADD_ROTATION_ANGLE = 0.3f;		//回転するときの加算する角度
	static const float COLLIDER_POS_Y = 1.0f;				//コライダーのY軸のポジション
	static const float COLLIDER_RADIUS = 1.0f;			    //コライダーの半径
	static const float UP_SPEED = 0.1f;					    //コインが上に行くときの速度
	static const float KILL_CALL_TIME_METHOD = 0.1f;	    //削除タイムメソッドを呼ぶ時間
	static const float SIGN_CALL_TIME_METHOD = 0.5f;	    //符号タイムメソッドを呼ぶ時間
	static const float RAY_HIT_DISTANCE = 1.0f;				//レイの当たった距離
	static const float GRAVITY_STRENGTH = 0.083f;           //重力の強さ
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //法線を補間するときの補間係数
	static const int MAX_NORMAL_RADIANS = 50;               //法線との最大角度
}

//コンストラクタ
Coin::Coin(GameObject* parent, std::string modelPath, std::string name)
	: Mob(parent, modelPath, name),type_(RotationType), sign_(1), timeMethodStatus_(SignChange), effectNumber_(-1)
{
}

//コンストラクタ
Coin::Coin(GameObject* parent)
	: Mob(parent, "Stage/Gimmick/Coin.fbx", "Coin"), type_(RotationType), sign_(1), timeMethodStatus_(Kill), effectNumber_(-1)
{
}

//更新の前に一度だけ呼ばれる関数
void Coin::ChildStartUpdate()
{
	//明るさ
	Model::SetBrightness(hModel_, 1.0f);

	//エフェクト
	ARGUMENT_INITIALIZE(effectNumber_, CoinEffectManager::Add(this));


	//コライダー追加
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_RADIUS * transform_.scale_.y);
	AddCollider(collision);
}

void Coin::ChildUpdate()
{
	//型によって処理を分ける
	switch (type_)
	{
	//回転
	case RotationType:

		Rotation();
		break;

	//ブロックからコイン出る
	case BlockCoinType:

		Rotation();
		BlockCoinBehavior();
		break;

	//その他は処理しない
	default:
		break;
	}


	//複数個所で使うので先に宣言しておく
	RayCastData downData;
	downData.start = transform_.position_;         //レイのスタート位置
	downData.dir = VectorToFloat3(down_);          //レイの方向
	Model::AllRayCast(hGroundModel_, &downData);   //レイを発射(All)

	 //真下の法線を調べてキャラの上軸を決定する
	CheckUnderNormal(downData);

	//ステージとの当たり判定
	StageRayCast(downData);

	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5 && this->IsVisibled())
		KillMe();
}

//真下の法線を調べてキャラの上軸を決定する
void Coin::CheckUnderNormal(const RayCastData& data)
{
	if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
	{
		//元のキャラの上ベクトルvNormalと下の法線の内積を求める
		float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

		//角度が50度以内に収まっていたら(壁とかに上らせないため)
		if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
		{
			//ちょっと補間
			vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
			down_ = -vNormal_;
		}
	}
}

//レイ(円用)
void Coin::StageRayCast(const RayCastData& data)
{
	//前
	RayCastData straightData;
	straightData.start = transform_.position_;                                                          //レイのスタート位置
	straightData.dir = VectorToFloat3(XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_));  //レイの方向
	Model::AllRayCast(hGroundModel_, &straightData);                                                    //レイを発射

	//////////////////////////////はみ出した分下げる//////////////////////////////////////

	//前の距離が1.0以下なら
	if (straightData.dist <= RAY_HIT_DISTANCE)
	{
		XMVECTOR dis = { ZERO,ZERO,straightData.dist };
		dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));

		//アニメーション停止
		Model::SetAnimFlag(hModel_, false);
	}

	//下の距離が1.0以上かつ重力適用するなら
	if (data.dist >= RAY_HIT_DISTANCE)
	{
		transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((-vNormal_) * GRAVITY_STRENGTH));
	}

}


//ブロックからコイン出た時の挙動
void Coin::BlockCoinBehavior()
{
	//上方向に行く
	transform_.position_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(vNormal_) * UP_SPEED * sign_));

	//状態によって呼ぶメソッド変更
	if (!GetTimeMethod() && timeMethodStatus_ == SignChange)
		SetTimeMethod(SIGN_CALL_TIME_METHOD);
	else if (!GetTimeMethod() && timeMethodStatus_ == Kill)
		SetTimeMethod(KILL_CALL_TIME_METHOD);
}

//回転
void Coin::Rotation()
{
	//普通の回転とそれ以外の時の回転の速度を変える
	if(type_ == RotationType)
		angle_ += ADD_ROTATION_ANGLE;
	else
		angle_ += BLOCK_ADD_ROTATION_ANGLE;

	//Angleが360までいったら0に戻す
	if (angle_ > TWOPI_DEGREES)
		angle_ = ZEROPI_DEGREES;
}

//開放
void Coin::ChildRelease()
{
}

//指定した時間で呼ばれるメソッド
void Coin::TimeMethod()
{
	//符号チェンジ状態なら
	if (timeMethodStatus_ == SignChange)
	{
		//符号チェンジ
		sign_ *= -2;

		//状態変更
		ARGUMENT_INITIALIZE(timeMethodStatus_, Kill);
	}
	//自身削除状態なら
	else if (timeMethodStatus_ == Kill)
	{
		//自身の削除
		KillMe();
	}
}

//当たり判定
void Coin::OnCollision(GameObject* pTarget)
{
	//Player以外なら何もしない
	if (pTarget->GetObjectName() != "Player" || !this->IsVisibled())
		return;

	//エフェクト表示
	CoinEffectManager::HitEffect(effectNumber_);

	//所有コインの量を増やす(コインの大きさによって増やす量変える)
	CoinManager::AddCoin(transform_.scale_.y);

	//描画しない
	Invisible();

	//1秒後に自身を削除
	SetTimeMethod(1.0f);
}
