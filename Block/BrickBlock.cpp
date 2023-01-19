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