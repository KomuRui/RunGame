#include "NormalBlock.h"

//定数
namespace
{
	static const float RAY_HIT_DISTANCE = 1.0f;				//レイの当たった距離
	static const float GRAVITY_STRENGTH = 0.083f;           //重力の強さ
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //法線を補間するときの補間係数
	static const float ADD_ROTATION_VALUE = 0.05f;          //回転するときの加算する角度
	static const int MAX_NORMAL_RADIANS = 50;               //法線との最大角度
}

//コンストラクタ
NormalBlock::NormalBlock(GameObject* parent)
	:Block(parent, "Stage/Block/Normalblock.fbx", "NormalBlock"), rotationAngle_(ZERO){}

//更新の前に一度だけ呼ばれる関数
void NormalBlock::BlockChildStartUpdate()
{
	///////////////明るさ///////////////////

	Model::SetBrightness(hModel_, 1.0f);
}

//更新
void NormalBlock::BlockChildUpdate()
{
	
	//複数個所で使うので先に宣言しておく
	RayCastData downData;
	downData.start = transform_.position_;         //レイのスタート位置
	downData.dir = VectorToFloat3(down_);          //レイの方向
	Model::AllRayCast(hGroundModel_, &downData);   //レイを発射(All)

	 //真下の法線を調べてキャラの上軸を決定する
	CheckUnderNormal(downData);

	//ステージとの当たり判定
	StageRayCast(downData);

	//回転
	transform_.mmRotate_ *= XMMatrixRotationAxis(STRAIGHT_VECTOR, rotationAngle_);

	//Angleが360までいったら0に戻す
	if (rotationAngle_ > TWOPI_DEGREES)
		rotationAngle_ = ZEROPI_DEGREES;

	//加算
	rotationAngle_ += ADD_ROTATION_VALUE;


	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();
}

//真下の法線を調べてキャラの上軸を決定する
void NormalBlock::CheckUnderNormal(const RayCastData& data)
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
void NormalBlock::StageRayCast(const RayCastData& data)
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