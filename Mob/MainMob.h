#pragma once
#include "../Mob.h"
#include "../Engine/Model.h"

/// <summary>
/// ���C�����u�L����
/// </summary>
class MainMob : public Mob
{
	//Player�̕��������s��
	XMMATRIX toPlayer_;

	//���ł�Player�̕����������ǂ���
	bool isLookPlayer_;

	//�b�����ǂ���
	bool isTalk_;

public:

	//�R���X�g���N�^
	MainMob(GameObject* parent, std::string modelPath, std::string name);

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
	/// �b�����ǂ������Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�b��,false�Ȃ�b���Ȃ�</param>
	void SetTalk(const bool& flag) { isTalk_ = flag; }
};
