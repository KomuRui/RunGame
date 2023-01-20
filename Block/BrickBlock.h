#pragma once
#include "Block.h"

/// <summary>
/// レンガブロッククラス
/// </summary>
class BrickBlock : public Block
{

public:

	//コンストラクタ
	BrickBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name) {}

	//コンストラクタ
	BrickBlock(GameObject* parent);

	//更新
	void BlockChildUpdate() override;

	//更新の前に一度だけ呼ばれる関数
	void BlockChildStartUpdate() override;
};
