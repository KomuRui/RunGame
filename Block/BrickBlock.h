#pragma once
#include "Block.h"

/// <summary>
/// �����K�u���b�N�N���X
/// </summary>
class BrickBlock : public Block
{

public:

	//�R���X�g���N�^
	BrickBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name) {}

};