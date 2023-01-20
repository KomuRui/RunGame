#include "EnemyEffectManager.h"
#include "../../../Engine/Global.h"
#include "../../GameManager/GameManager.h"

/// <summary>
/// Enemy�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace EnemyEffectManager
{
	/////////////////////////////////�ϐ�/////////////////////////////////////

	//�G�t�F�N�g�\������̂ɕK�v�ȃf�[�^
	std::vector<Particle*> pEffectData_;

	/////////////////////////////////�֐�/////////////////////////////////////

	//�ǉ�
	int Add(GameObject* enemy)
	{
		//�V���ɒǉ�
		pEffectData_.push_back(Instantiate<Particle>(enemy));
		return (int)pEffectData_.size() - 1;
	}


	/// <summary>
	/// ���
	/// </summary>
	void Release(const int& handle)
	{
		for (int i = 0; i < pEffectData_.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (i != handle && pEffectData_[i] == pEffectData_[handle])
			{
				pEffectData_[i]->KillMe();
				break;
			}
		}
	}

	//���
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
	void HitEffect(const int& handle, const XMFLOAT3& Hitpos, const XMFLOAT3& pos)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = Hitpos;
		data.delay = 0;
		data.number = 40;
		data.lifeTime = 40;
		XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&pos)));
		data.dirErr = XMFLOAT3(90, 90, 90);
		data.speed = 0.15f;
		data.speedErr = 0.8;
		data.size = XMFLOAT2(1.5, 1.5);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
		pEffectData_[handle]->Start(data);
	}

	//���ʂƂ��̃G�t�F�N�g
	void DieEffect(const int& handle, const XMFLOAT3& pos, const XMVECTOR& dir)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = pos;
		data.delay = 0;
		data.number = 350;
		data.lifeTime = 100;
		data.positionErr = XMFLOAT3(0.5, 0, 0.5);
		data.dir = VectorToFloat3(dir);
		data.dirErr = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedErr = 1;
		data.accel = 0.93;
		data.size = XMFLOAT2(0.2, 0.2);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(0.99, 0.99);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, 0, 0, 0);
		data.gravity = 0.003f;
		pEffectData_[handle]->Start(data);
	}
}