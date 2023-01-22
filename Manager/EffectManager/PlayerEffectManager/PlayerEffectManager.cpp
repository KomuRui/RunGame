#include "PlayerEffectManager.h"
#include "../../../Engine/Global.h"
#include "../../GameManager/GameManager.h"

/// <summary>
/// Player�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace PlayerEffectManager
{
	/////////////////////////////////�ϐ�/////////////////////////////////////

	//�G�t�F�N�g�\������̂ɕK�v�ȕϐ�
	Particle* pEffect_;

	/////////////////////////////////�֐�/////////////////////////////////////

	//������
	void Initialize(GameObject* player)
	{
		ARGUMENT_INITIALIZE(pEffect_, Instantiate<Particle>(player));
	}

	//���
	void AllRelease()
	{
		//nullptr�Ȃ�return
		if (pEffect_ == nullptr) return;

		//�폜
		pEffect_->KillMe();
	}

	//��]�G�t�F�N�g
	void RotationEffect(const int& modelnum)
	{
		XMFLOAT3 Right = Model::GetBonePosition(modelnum, "Right2");//�E
		XMFLOAT3 Left = Model::GetBonePosition(modelnum, "Left2");  //��

		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = Right;
		data.positionErr = XMFLOAT3(0.3, 0.2, 0.3);
		data.delay = 0;
		data.number = 5;
		data.lifeTime = 50;
		data.speed = 0.04f;
		data.speedErr = 0.8;
		data.size = XMFLOAT2(0.6, 0.6);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.00, 1.00);
		data.color = XMFLOAT4(0, 1, 1, 1);
		data.deltaColor = XMFLOAT4(0, -0.1, 0, -0.1);
		pEffect_->Start(data);


		data.position = Left;
		pEffect_->Start(data);
	}

	//�����G�t�F�N�g
	void FallEffect(const XMFLOAT3& position)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = position;
		data.position.y -= 4;
		data.delay = 0;
		data.number = 180;
		data.lifeTime = 50;
		data.dir = XMFLOAT3(0, 0, 1);
		data.dirErr = XMFLOAT3(0, 360, 0);
		data.speed = 0.2f;
		data.speedErr = 0.45;
		data.size = XMFLOAT2(1, 1);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 1, 0.2);
		data.deltaColor = XMFLOAT4(0, 0, 0, -0.004);
		pEffect_->Start(data);
	}

	/// <summary>
	/// ���S�|�W�V����
	/// </summary>
	void DieEffect(const XMFLOAT3& position, const XMVECTOR& dir)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = position;
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
		pEffect_->Start(data);
	}
}