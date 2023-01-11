#pragma once
#include "GameObject.h"
#include "../Player.h"
#include "../Block/Block.h"

//�ő��Imgui�ŏo����I�u�W�F�N�g�T�C�Y
const int MAX_OBJECT_SIZE = 50;


/// <summary>
/// Debug�p��UI��\������
/// </summary>
namespace ImGuiSet
{

	//������
	void Initialize();

	//�`��
	void Draw();

	//�J��
	void Release();

	////////////////////////////////////�X�e�[�W�쐬�pImGui///////////////////////////////////////

	/// <summary>
	/// �X�e�[�W�쐬����ImGui��UI���o���Ă����
	/// </summary>
	void StageCreater();

	/// <summary>
	/// 3D�I�u�W�F�N�g�쐬
	/// </summary>
	void Create3D();

	/// <summary>
	/// �Ŕ쐬
	/// </summary>
	void CreateSigeboard();

	/// <summary>
	/// �J�����̑J�ڍ쐬(�R���C�_�[�ɓ���������J�����̃|�W�V�����ς���@�\)
	/// </summary>
	void CreateCameraTransition();

	/// <summary>
	/// �摜�쐬
	/// </summary>
	void CreateImage();

	//////////////////////////////�X�e�[�W�̃I�u�W�F�N�g�̃g�����X�t�H�[���\��////////////////////////////

	/// <summary>
	/// �X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\������ImGui��\��
	/// </summary>
	void StageObjImGuiDisplay();

	/// <summary>
	/// �X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\��
	/// </summary>
	void StageObjTransformDisplay(GameObject* pObj);

	//////////////////////////////////////���O�\��///////////////////////////////////////

	/// <summary>
	/// �f�o�b�O���O���Ǘ�����(ImGui�͂����ŕ\������)
	/// </summary>
	void DebugLogManager();

	/// <summary>
	/// �C�ӂ̒l��\�����Ă����
	/// </summary>
	/// <param name="text">�\���������ϐ��̖��O</param>
	/// <param name="num">�\���������l</param>
	void DebugLog(std::string text ,int num);
	void DebugLog(std::string text, float num);
	void DebugLog(std::string text, bool num);
	void DebugLog(std::string text, XMFLOAT3 num);
	void DebugLog(std::string text, std::string str);
};