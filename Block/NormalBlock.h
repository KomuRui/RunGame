#pragma once
#include "Block.h"

/// <summary>
/// �m�[�}���u���b�N�N���X
/// </summary>
class NormalBlock : public Block
{

	//��]�p�x
	float rotationAngle_;

public:

	//�R���X�g���N�^
	NormalBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name){}

	//�R���X�g���N�^
	NormalBlock(GameObject* parent);

	//�X�V
	void BlockChildUpdate() override;

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void BlockChildStartUpdate() override;

	/// <summary>
	/// �^���̖@���𒲂ׂăL�����̏㎲�����肷��
	/// </summary>
	/// <param name="data">�����蔻��ɕK�v�ȃf�[�^</param>
	void CheckUnderNormal(const RayCastData& data);

	/// <summary>
	/// ���C�œ����蔻��(3D�p)
	/// </summary>
	/// <param name="data">�����蔻��ɕK�v�ȃf�[�^</param>
	void StageRayCast(const RayCastData& data);
};
