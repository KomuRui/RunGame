#pragma once
#include "../../../Engine/Particle.h"
#include "../../../Engine/GameObject.h"

/// <summary>
/// Coin�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace CoinEffectManager
{
	/// <summary>
	/// �ǉ�
	/// </summary>
	/// <param name="enemy">�G�t�F�N�g�g���G�̃|�C���^</param>
	/// <returns>�G�t�F�N�g�ԍ�(�G�t�F�N�g�g���Ƃ��Ɏg��)</returns>
	int Add(GameObject* coin);

	/// <summary>
	/// ���
	/// </summary>
	void AllRelease();

	/// <summary>
	/// �����������̃G�t�F�N�g
	/// </summary>
	/// <param name="handle">�G�t�F�N�g�ԍ�</param>
	void HitEffect(const int& handle);

}