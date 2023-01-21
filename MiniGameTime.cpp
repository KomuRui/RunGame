#include "MiniGameTime.h"
#include "Engine/Time.h"
#include "Manager/GameManager/GameManager.h"

namespace MiniGameTime
{
	//���ԕ\�����邽�߂̕ϐ�
	Text* pTimeText_;

	//������
	void Initialize()
	{
		//�����̏�����
		ARGUMENT_INITIALIZE(pTimeText_, new Text);
		pTimeText_->Initialize(-0.06f);

		//�^�C���X�^�[�g
		Time::UnLock();
	}

	//�`��
	void Draw()
	{
		//���C�h������ɕϊ�
		wchar_t wtext[FILENAME_MAX];
		std::string text;

		//10�b�ȏ�Ȃ�
		if (Time::GetTimef() / 10.0f >= 0)
			text = float_to_string(Time::GetTimef(), 3) + "/30.000";
		else
			text = "0" + float_to_string(Time::GetTimef(), 3) + "/30.000";

		size_t ret;
		setlocale(LC_ALL, ".932");
		mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

		//�R���{�`��
		pTimeText_->Draw(100, 150, wtext);
	}
}
