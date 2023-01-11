#include "Stage.h"
#include "Block/Block.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent, std::string name)
	:GameObject(parent,name), warpPos_(0,0,0)
{
}

//�萔
namespace
{
	static float BLOCK_SIZE = 1.0f;				    //�u���b�N�̃T�C�Y
	static const float PLAYER_MODEL_SIZE_X = 1.0f;  //Player��X�̃��f���T�C�Y
	static const float PLAYER_MODEL_SIZE_Y = 2.0f;  //Player��Y�̃��f���T�C�Y
}

//�����Ƀu���b�N�����邩�ǂ���,������������d�Ȃ��Ă��镪���炷
bool Stage::IsBlock(XMFLOAT3* pos, int status)
{
	//�A�zfor��
	for (const auto& block : tBlock_)
	{
		//�|�W�V�����ƃT�C�Y��ϐ��ɓ���Ă���
		XMFLOAT3 p = block->GetPosition();
		XMFLOAT3 s = block->GetScale();

		//�����������Ă�����
		if (p.x + (BLOCK_SIZE * s.x) > pos->x &&
			p.x - (BLOCK_SIZE * s.x) < pos->x &&
			p.y - (BLOCK_SIZE * s.y) < pos->y &&
			p.y + (BLOCK_SIZE * s.y) > pos->y &&
			p.z - (BLOCK_SIZE * s.z) < pos->z &&
			p.z + (BLOCK_SIZE * s.z) > pos->z)
		{

			//�����ɂ���ď����𕪂���
			switch (status)
			{
			//�E
			case Right:
				pos->x = (p.x + (PLAYER_MODEL_SIZE_X / 2) + (BLOCK_SIZE * s.x));
				break;

			//��
			case Left:
				pos->x = (p.x - (PLAYER_MODEL_SIZE_X / 2) - (BLOCK_SIZE * s.x));
				break;

			//��
			case Under:
				pos->y = (p.y + (PLAYER_MODEL_SIZE_Y / 2) + (BLOCK_SIZE * s.y));
				break;

			//��
			case Top:
				pos->y = (p.y - (PLAYER_MODEL_SIZE_Y / 2) - (BLOCK_SIZE * s.y));
				block->SetIsHit(true);
				break;
			}

			return true;
		}
	}

	return false;
}