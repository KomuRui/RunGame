#include "CoinEffectManager.h"
#include "../../../Engine/Global.h"
#include "../../GameManager/GameManager.h"

/// <summary>
/// Coin�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace CoinEffectManager
{
	/////////////////////////////////�ϐ�/////////////////////////////////////

	//�G�t�F�N�g�\������̂ɕK�v�ȃf�[�^
	std::vector<Particle*> pEffectData_;

	/////////////////////////////////�֐�/////////////////////////////////////

	//�ǉ�
	int Add(GameObject* coin)
	{
		//�V���ɒǉ�
		pEffectData_.push_back(Instantiate<Particle>(coin));
		return (int)pEffectData_.size() - 1;
	}

	/// <summary>
	/// ���
	/// </summary>
	void Release(const int& handle)
	{
		for (int i = 0; i < pEffectData_.size(); i++)
		{
			if ( i != handle)
			{
				pEffectData_[i]->KillMe();
				break;
			}
		}
	}

	//���ׂĉ��
	void AllRelease()
	{
		//�폜
		for (auto i = pEffectData_.begin(); i != pEffectData_.end(); i++)
		{
			(*i)->KillMe();
		}

		//��ɂ���
		pEffectData_.clear();
	}

	//�����������̃G�t�F�N�g
	void HitEffect(const int& handle)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = GameManager::GetpPlayer()->GetPosition();
		data.delay = 0;
		data.number = 150;
		data.lifeTime = 100;
		data.positionErr = XMFLOAT3(0.5, 0, 0.5);
		data.dir = VectorToFloat3(GameManager::GetpPlayer()->GetNormal());
		data.dirErr = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedErr = 1;
		data.accel = 0.93;
		data.size = XMFLOAT2(0.1, 0.1);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(0.99, 0.99);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, 0, 0, 0);
		data.gravity = 0.003f;
		pEffectData_[handle]->Start(data);

	}
}