#pragma once
#include "Block.h"

/// <summary>
/// ノーマルブロッククラス
/// </summary>
class NormalBlock : public Block
{

	//回転角度
	float rotationAngle_;

public:

	//コンストラクタ
	NormalBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name){}

	//コンストラクタ
	NormalBlock(GameObject* parent);

	//更新
	void BlockChildUpdate() override;

	//更新の前に一度だけ呼ばれる関数
	void BlockChildStartUpdate() override;

	/// <summary>
	/// 真下の法線を調べてキャラの上軸を決定する
	/// </summary>
	/// <param name="data">当たり判定に必要なデータ</param>
	void CheckUnderNormal(const RayCastData& data);

	/// <summary>
	/// レイで当たり判定(3D用)
	/// </summary>
	/// <param name="data">当たり判定に必要なデータ</param>
	void StageRayCast(const RayCastData& data);
};
