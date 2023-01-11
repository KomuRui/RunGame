#pragma once
#include "Block.h"
#include "../Engine/Particle.h"

//�A�C�e���u���b�N�̌^(�Ⴄ�ꏊ�ł��g�������̂ŊO�ɏo��)
enum ItemBlockType
{
	ItemBlockNormal = 0, //����
	ItemBlockRotation    //��]
};

//�A�C�e���u���b�N���h���b�v����A�C�e���̌^
enum DropItemType
{
	None = 0,    //�����Ȃ�     
	OneCoin,     //�R�C��1
	TenCoin      //�R�C��10
};

/// <summary>
/// �A�C�e���u���b�N�N���X
/// </summary>
class ItemBlock : public Block
{
	//�G�t�F�N�g�\������̂ɕK�v�ȕϐ�
	Particle* pParticle_;                   

	//�^
	int type_;

	//�h���b�v����A�C�e���̃^�C�v
	int dropItemType_;

	//�R�C�������o�������J�E���g����p
	int coinCount_;

public:

	//�R���X�g���N�^
	ItemBlock(GameObject* parent, std::string modelPath, std::string name);

	//�X�V
	void BlockChildUpdate() override;

	/// <summary>
	/// �u���b�N�̓���
	/// </summary>
	void Move();

	/// <summary>
	/// �����������̃G�t�F�N�g
	/// </summary>
	void HitEffect();

	/// <summary>
	/// �p����p��Player�������瓖���������̋���
	/// </summary>
	void BlockChildHitToLowerPlayer() override;

	/// <summary>
	/// �^�Z�b�g
	/// </summary>
	/// <param name="num">�Z�b�g�������^</param>
	void SetType(const int& num){ type_ = num;}

	/// <summary>
	/// �h���b�v����A�C�e���̃^�C�v�Z�b�g
	/// </summary>
	/// <param name="num">�Z�b�g�������A�C�e���̃^�C�v</param>
	void SetDropItemType(const int& num) { dropItemType_ = num; }
};
