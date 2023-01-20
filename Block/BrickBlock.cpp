#include "BrickBlock.h"

//�R���X�g���N�^
BrickBlock::BrickBlock(GameObject* parent)
	:Block(parent, "Stage/Block/BrickBlock.fbx", "BrickBlock")
{}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void BrickBlock::BlockChildStartUpdate()
{
	///////////////���邳///////////////////

	Model::SetBrightness(hModel_, 1.0f);
}


//�X�V
void BrickBlock::BlockChildUpdate()
{
	//Player�����ɍs�����玀�S
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();
}