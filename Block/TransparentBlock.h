#pragma once
#include "Block.h"

/// <summary>
/// �����u���b�N�N���X
/// </summary>
class TransparentBlock : public Block
{

public:

	//�R���X�g���N�^
	TransparentBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name) {}

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void BlockChildStartUpdate() override;
};