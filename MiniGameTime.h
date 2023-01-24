#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//�~�j�Q�[���̏��
enum class MiniGameStatus 
{
	NOT_START = 0,
	PLAY,
	END
};

/// <summary>
/// �~�j�Q�[���̃^�C����\������
/// </summary>
namespace MiniGameTime
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �������ԕ`��
	/// </summary>
	void LimitTimeDraw();

	/// <summary>
	/// �X�^�[�g�J�E���g�`��
	/// </summary>
	void StartCountDraw();

	/// <summary>
	/// ���ʕ\��
	/// </summary>
	void ResultDraw();

	/// <summary>
	/// �J�n���Ă��邩
	/// </summary>
	/// <returns>true�Ȃ�J�n���Ă���</returns>
	bool IsPlay();

	/// <summary>
	/// �J�n���Ă��邩���Z�b�g
	/// </summary>
	void SetMiniGameStatus(MiniGameStatus status);

	/// <summary>
	/// �~�j�Q�[���̏�Ԃ��Q�b�g
	/// </summary>
	/// <returns>�~�j�Q�[���̏��</returns>
	MiniGameStatus GetMiniGameStatus();

	/// <summary>
	/// ������ݒ�
	/// </summary>
	/// <param name="dis">�ݒ肵��������</param>
	void SetResultDis(const int& dis);
};

