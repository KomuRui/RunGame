#pragma once

/// <summary>
/// Player�̎����Ă�R�C���Ǘ�
/// </summary>
namespace CoinManager
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// �R�C�����������Ă��邩�`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �R�C���̒ǉ�
	/// </summary>
	/// <param name="num">�ǉ��������R�C���̐�</param>
	void AddCoin(int num);
}

