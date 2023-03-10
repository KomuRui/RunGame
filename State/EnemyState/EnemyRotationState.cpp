#include "EnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//更新
void EnemyRotationState::Update2D(Enemy* enemy)
{
	//入力処理
	HandleInput(enemy);
}

//3D用更新
void EnemyRotationState::Update3D(Enemy* enemy)
{
	//回転
	enemy->Rotation();

	//入力処理
	HandleInput(enemy);
}

//入力によって状態変化する
void EnemyRotationState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void EnemyRotationState::Enter(Enemy* enemy)
{
    //回転する方向設定
    enemy->SetRotationSign(rand() % 2 == 1 ? 1 : -1);

    //回転角度設定
    enemy->SetRotationAngle(XMConvertToRadians((rand() % 141) + 40));

    //どのくらい回転したかを初期化
    enemy->SetRotationTotal(ZERO);
}