#include "TransparentBlock.h"
#include "../Engine/Model.h"

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void TransparentBlock::BlockChildStartUpdate()
{
	//�����ɐݒ�
	Model::SetAlpha(hModel_, ZERO);
}
