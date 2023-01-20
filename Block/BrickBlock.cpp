#include "BrickBlock.h"

//コンストラクタ
BrickBlock::BrickBlock(GameObject* parent)
	:Block(parent, "Stage/Block/BrickBlock.fbx", "BrickBlock")
{}

//更新の前に一度だけ呼ばれる関数
void BrickBlock::BlockChildStartUpdate()
{
	///////////////明るさ///////////////////

	Model::SetBrightness(hModel_, 1.0f);
}


//更新
void BrickBlock::BlockChildUpdate()
{
	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();
}