#include "PigEnemy.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/ImGuiSet.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"

//定数
namespace
{
	//////////////////////アニメーション//////////////////////

	static const int ANIM_START_FRAME = 1; //開始フレーム
	static const int ANIM_END_FRAME = 60;  //終了フレーム
	static const int ANIM_DIE_FRAME = 70;  //死亡フレーム
	static const float ANIM_SPEED = 2.0f;  //アニメスピード

	//////////////////////キャラの必要な情報//////////////////////

	static const int FEED_BACK_ANGLE = 25;					  //反応角度
	static const int RAY_DISTANCE = 1;                        //レイの距離
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 10;	  //ノックバック想定距離
	static const float KNOCKBACK_DIFFERENCIAL_DISTANCE = 5.0f;//ノックバックの差分距離
	static const float INTERPOLATION_COEFFICIENT = 0.08f;     //補間係数
	static const float HIT_STOP_TIME = 0.15f;                 //ヒットストップ演出の時間
	static const float FLY_VECTOR_SIZE = 1.0f;				  //FLYベクトルの大きさ
	static const float FLY_VECTOR_DOWN = 0.015f;			  //FLYベクトルを小さくしていくときの値
	static const float COLLIDER_SIZE = 1.7f;                  //コライダーサイズ
	static const float DIE_TIME = 1.0f;                       //死ぬまでの時間

	//////////////////////カメラ//////////////////////

	static const float VIBRATION_INTENSITY = 0.4f; //振動の強さ
}

//コンストラクタ
PigEnemy::PigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), isKnockBack_(false),knockBackDir_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),isTimeMethodChange_(false)
{
}

PigEnemy::PigEnemy(GameObject* parent)
	: Enemy(parent,"Enemy/Model/Pig.fbx","PigEnemy"), isKnockBack_(false), knockBackDir_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)), isTimeMethodChange_(false)
{
}

//更新の前に一回呼ばれる関数
void PigEnemy::EnemyChildStartUpdate()
{
	///////////////明るさ///////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////エフェクト///////////////////

	//エフェクトの番号保存
	ARGUMENT_INITIALIZE(effectNum_, EnemyEffectManager::Add(this));

	///////////////当たり判定設定///////////////////

	//玉
	collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * 1, ZERO), COLLIDER_SIZE);
	AddCollider(collision);

	///////////////アニメーション///////////////////

	//開始
	Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, ANIM_SPEED);
}

//更新
void PigEnemy::EnemyChildUpdate()
{
	//コライダーのポジション変更
	SetPosCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)), ZERO));

	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();
}

//Playerが自身の上にいるかどうか
bool PigEnemy::IsPlayerTop()
{
	//自身の上ベクトルとPlayerまでのベクトルの内積を求める
	float topAngle = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)), XMVector3Normalize(vNormal_))));

	//視角内,指定距離内にいるなら
	return (topAngle < XMConvertToRadians(FEED_BACK_ANGLE) && topAngle > XMConvertToRadians(-FEED_BACK_ANGLE)) ? true : false;
}

//ノックバックして死亡
void PigEnemy::KnockBackDie()
{
	//ノックバックしていないのなら
	if (!isKnockBack_)
	{
		//ノックバックどこまでするか設定(単位ベクトルにして定数分倍にする)
		knockBackDir_ = (XMVectorSet(0,0,10,0) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(&transform_.position_);

		//どのくらい空飛ぶか設定
		ARGUMENT_INITIALIZE(vFly_, GameManager::GetpPlayer()->GetNormal() * FLY_VECTOR_SIZE);

		//基となるFlyベクトルを保存しておく
		ARGUMENT_INITIALIZE(keepFly_, vFly_);

		//ノックバックした
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);
	}

	//ノックバック(指定の場所まで補間してゆっくり行くように)
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), knockBackDir_, INTERPOLATION_COEFFICIENT));

	//距離
	float dist = RangeCalculation(transform_.position_, VectorToFloat3(knockBackDir_));

	//壁に埋まらないようにするためにノックバック方向にレイを飛ばす
	RayCastData data;
	data.start = transform_.position_;    
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)));
	Model::AllRayCast(hGroundModel_, &data);  

	//埋まった分戻す
	if (data.dist <= 5)
	{
		//死亡状態に変更
		ChangeEnemyState(EnemyStateList::GetEnemyDieState());
	}

	//ノックバックしているなら
	if (isKnockBack_)
	{
		//基となるジャンプベクトルと符号が同じなら
		if (signbit(XMVectorGetY(vFly_)) == signbit(XMVectorGetY(keepFly_)))
		{
			//ベクトルの長さ調べる
			float len = sqrtf(XMVectorGetX(vFly_) * XMVectorGetX(vFly_) + XMVectorGetY(vFly_) * XMVectorGetY(vFly_) + XMVectorGetZ(vFly_) * XMVectorGetZ(vFly_));

			//フライベクトルをキャラの上軸に直す
			ARGUMENT_INITIALIZE(vFly_, vNormal_ * len);

			//空飛ばせる
			ARGUMENT_INITIALIZE(transform_.position_, Float3Add(transform_.position_, VectorToFloat3(vFly_ - (vNormal_ * FLY_VECTOR_DOWN))));

			//どんどんジャンプベクトルを小さくしていく
			ARGUMENT_INITIALIZE(vFly_, vFly_ - (vNormal_ * FLY_VECTOR_DOWN));
		}

		Model::SetAnimFrame(hModel_, 80, 80, ZERO);
	}

	//ノックバックした距離がノックバックの想定距離と1以内の距離なら
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//ノックバックしてない状態に
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);

		//死亡状態に変更
		ChangeEnemyState(EnemyStateList::GetEnemyDieState());
	}
}

//死亡
void PigEnemy::Die()
{
	//待機状態に変更
	ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

	//吹っ飛ばされるアニメーションに
	Model::SetAnimFrame(hModel_, 80, 80, ZERO);

	//死ぬエフェクト
	EnemyEffectManager::DieEffect(effectNum_, transform_.position_, up_);

	KillCollider(collision);

	//描画しない
	Invisible();

	//呼ぶメソッド切り替える
	ARGUMENT_INITIALIZE(isTimeMethodChange_, true);

	//指定した時間後にメソッド呼ぶ
	SetTimeMethod(DIE_TIME);
}

//何かのオブジェクトに当たった時に呼ばれる関数
void PigEnemy::TimeMethod()
{
	//もし切り替えているのなら
	if (isTimeMethodChange_)
	{
		KillMe();
	}
	else
		Enter();
}

//何かのオブジェクトに当たった時に呼ばれる関数
void PigEnemy::OnCollision(GameObject* pTarget)
{
	//もしPlayerと当たったら
	if (pTarget->GetObjectName() == "Player")
	{
		
		//もしPlayerが回転していたらかつ自身が死んでいないなら
		if (GameManager::GetpPlayer()->IsRotation() && pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		{
			GameManager::GetpPlayer()->SetRunSpeed(8.0f);
			GameManager::GetpPlayer()->SetRunMode(true);
			GameManager::AddCombo();
			GameManager::SetTextScale(1.3f);
			
			//当たった位置を調べる
			XMFLOAT3 hitPos = VectorToFloat3(XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * GetColliderRadius()));

			//エフェクト表示
			EnemyEffectManager::HitEffect(effectNum_, hitPos, transform_.position_);

			//カメラ振動
			Camera::SetCameraVibration(VIBRATION_INTENSITY,0.02f);

			//ノックバックして死亡させる
			ChangeEnemyState(EnemyStateList::GetEnemyKnockBackState());

			//終了
			return;

		}
	}
}
