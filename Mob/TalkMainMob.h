#pragma once
#include "../Mob.h"
#include "../Engine/Model.h"
#include "../Image/TalkImage.h"

class TalkImage;

/// <summary>
/// ���C�����u�L����
/// </summary>
class TalkMainMob : public Mob
{
	//�摜�ԍ�
	int hPict_;

	//�摜�̃g�����X�t�H�[��
	Transform tPict_;

	//Player�̕��������s��
	XMMATRIX toPlayer_;

	//�\���������摜�̃N���X��ۑ����Ă����p
	TalkImage *pTalkImage_;

	//���ł�Player�̕����������ǂ���
	bool isLookPlayer_;

	//�b�����ǂ���
	bool isTalk_;

public:

	//�R���X�g���N�^
	TalkMainMob(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	/// <summary>
	/// Player�̕�������
	/// </summary>
	void LookPlayer();

	/// <summary>
	/// �w�苗�����ɓ����Ă��邩�ǂ���
	/// </summary>
	bool IsInSpecifiedDistance();
};
