#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

//�O���錾
class CsvReader;

/// <summary>
/// ���u�Ƙb���Ƃ��̉摜��\����������N���X
/// </summary>
class TalkImage : public GameObject
{
	///////////////////////������///////////////////////////

	int drawTextNum_; //���`�悵�Ă镶����̔ԍ�
	bool isLastDraw_; //�Ō�܂ŕ`�悵�����ǂ���

	CsvReader* pCsv_; //�������O���擾���邽�߂̕ϐ�

	/////////////////////////�摜///////////////////////////

	int hBasePict_;      //�x�[�X�摜�ԍ�
	int hCharaPict_;     //�L�����摜�ԍ�
	int hNextPict_;      //Next�摜�ԍ�

	Transform tBase_;    //�x�[�XTransform
	Transform tChara_;   //�L����Transform
	Transform tNext_;    //NextTransform

	////////////////////////�e�L�X�g/////////////////////////

	Text* pText_;        //�����\������p

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TalkImage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/// <summary>
	/// �Ō�܂ŕ`�悵�����ǂ���
	/// </summary>
	/// <returns>true�Ȃ炵��,false�Ȃ炵�ĂȂ�</returns>
	bool IsLastDraw() { return isLastDraw_; }
};

