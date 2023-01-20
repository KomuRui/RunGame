#pragma once
#include "../../../Engine/Particle.h"
#include "../../../Engine/GameObject.h"

/// <summary>
/// Enemy�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace EnemyEffectManager
{
	/// <summary>
	/// �ǉ�
	/// </summary>
	/// <param name="enemy">�G�t�F�N�g�g���G�̃|�C���^</param>
	/// <returns>�G�t�F�N�g�ԍ�(�G�t�F�N�g�g���Ƃ��Ɏg��)</returns>
	int Add(GameObject* enemy);
	
	/// <summary>
	/// ���
	/// </summary>
	void Release(const int& handle);

	/// <summary>
	/// ���
	/// </summary>
	void AllRelease();

	/// <summary>
	/// �����������̃G�t�F�N�g
	/// </summary>
	/// <param name="handle">�G�t�F�N�g�ԍ�</param>
	/// <param name="Hitpos">�G�t�F�N�g�𔭐����������ʒu</param>
	/// <param name="pos">�G�̈ʒu</param>
	void HitEffect(const int& handle, const XMFLOAT3& Hitpos, const XMFLOAT3& pos);

	/// <summary>
	/// ���ʂƂ��̃G�t�F�N�g
	/// </summary>
	/// <param name="handle">�G�t�F�N�g�ԍ�</param>
	/// <param name="pos">�G�̈ʒu</param>
	/// <param name="dir">�G�t�F�N�g�̕���</param>
	void DieEffect(const int& handle, const XMFLOAT3& pos, const XMVECTOR& dir);
}