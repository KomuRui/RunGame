#pragma once
#include "Block.h"

/// <summary>
/// �m�[�}���u���b�N�N���X
/// </summary>
class NormalBlock : public Block
{

public:

	//�R���X�g���N�^
	NormalBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name){}

};
