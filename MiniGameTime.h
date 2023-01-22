#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

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
	/// �J�n���Ă��邩
	/// </summary>
	/// <returns>true�Ȃ�J�n���Ă���</returns>
	bool IsStart();
};

