#pragma once
#include "../../../Engine/Particle.h"
#include "../../../Engine/GameObject.h"

/// <summary>
/// Player�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace PlayerEffectManager
{
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	void Initialize(GameObject* player);

	/// <summary>
	/// ���
	/// </summary>
	void AllRelease();

	/// <summary>
	/// ��]�G�t�F�N�g
	/// </summary>
	/// <param name="modelnum">player�̃��f���ԍ�</param>
	void RotationEffect(int modelnum);

	/// <summary>
	/// �����G�t�F�N�g
	/// </summary>
	/// <param name="position">�G�t�F�N�g�𔭐����������|�W�V����</param>
	void FallEffect(XMFLOAT3 position);
}

