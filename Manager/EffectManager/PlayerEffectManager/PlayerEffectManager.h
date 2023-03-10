#pragma once
#include "../../../Engine/Particle.h"
#include "../../../Engine/GameObject.h"

/// <summary>
/// Playerのエフェクトを管理する
/// </summary>
namespace PlayerEffectManager
{
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	void Initialize(GameObject* player);

	/// <summary>
	/// 解放
	/// </summary>
	void AllRelease();

	/// <summary>
	/// 回転エフェクト
	/// </summary>
	/// <param name="modelnum">playerのモデル番号</param>
	void RotationEffect(const int& modelnum);

	/// <summary>
	/// 落下エフェクト
	/// </summary>
	/// <param name="position">エフェクトを発生させたいポジション</param>
	void FallEffect(const XMFLOAT3& position);

	/// <summary>
	/// 死亡ポジション
	/// </summary>
	void DieEffect(const XMFLOAT3& position, const XMVECTOR& dir);
}

