#include "MiniGameTime.h"
#include "Engine/Time.h"
#include "Engine/ImGuiSet.h"
#include "Manager/GameManager/GameManager.h"

//�萔
namespace
{
	static const int START_MAX_COUNT = 4;      			//�X�^�[�g�J�E���g�̍ő�l
	static const float TEXT_INTERVAL = -0.06f;		    //�����̊Ԋu
	static const float NORMAL_START_COUNT_SCALE = 5.0f; //�X�^�[�g�J�E���g�����̊g�嗦
}

namespace MiniGameTime
{
	
	Text* pTimeText_;           //���ԕ\�����邽�߂̕ϐ�
	Text* pStartCountText_;     //�X�^�[�g����܂ł̃J�E���g��\�����邽�߂̕����\���ϐ�
	
	int startCount_;            //�X�^�[�g����܂ł̃J�E���g
	float startCountTextScale_; //�X�^�[�g�J�E���g�����̊g�嗦

	bool isStart_;   //�J�n���Ă��邩�ǂ���

	//������
	void MiniGameTime::Initialize()
	{
		//�����̏�����
		ARGUMENT_INITIALIZE(pTimeText_, new Text);
		pTimeText_->Initialize(TEXT_INTERVAL);
		ARGUMENT_INITIALIZE(pStartCountText_,new Text)
		pStartCountText_->Initialize("Text/NumberFont.png", 128, 256, 10);

		//�X�^�[�g�J�E���g�̏�����
		ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT);
		ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);

		//�J�n���Ă��Ȃ��ɏ�����
		ARGUMENT_INITIALIZE(isStart_, false);
	}

	//�`��
	void MiniGameTime::Draw()
	{
		//�J�n���Ă���Ȃ�
		if (isStart_)
			LimitTimeDraw();
		else
			StartCountDraw();
	}

	//�������ԕ`��
	void MiniGameTime::LimitTimeDraw()
	{
		//���C�h������i�[�p
		wchar_t wtext[FILENAME_MAX];
		std::string text;

		//10�b�ȏ�Ȃ�
		if (Time::GetTimef() / 10.0f >= 0)
			text = float_to_string(Time::GetTimef(), 3) + "/30.000";
		else
			text = "0" + float_to_string(Time::GetTimef(), 3) + "/30.000";

		//���C�h������ɕϊ�
		size_t ret;
		setlocale(LC_ALL, ".932");
		mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

		//���ԕ`��
		pTimeText_->Draw(100, 150, wtext,1.0f,TEXT_INTERVAL);
	}

	//�X�^�[�g�J�E���g�`��
	void MiniGameTime::StartCountDraw()
	{
		//�������b�N����Ă���̂Ȃ烍�b�N����
		if (Time::GetLock()) Time::UnLock();

		//��O�ۑ�
		int beforStartCount = startCount_;

		//startCount_�����߂�
		ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT - Time::GetTimei());

		//�O��ƈႤ�̂Ȃ�g�嗦���ɖ߂�
		if (beforStartCount != startCount_) ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);

		//startCount_��0�Ȃ�
		if (startCount_ == ZERO)
		{
			//Start�`��
			pTimeText_->Draw(460, 440, L"START", 3.0f, -0.15f);
		}
		//�}�C�i�X�Ȃ�J�n
		else if (startCount_ < ZERO)
		{
			//�J�n
			ARGUMENT_INITIALIZE(isStart_, true);

			//�^�C�����Z�b�g
			Time::Reset();
		}
		//startCount_��3�ȉ��Ȃ琔���`��
		else if (startCount_ <= 3)
		{
			//�g�嗦�����������Ă���
			startCountTextScale_ -= 0.05f;

			//�`��
			pStartCountText_->NumberDraw(960, 440, startCount_, startCountTextScale_);
		}
	}

	//�J�n���Ă��邩
	bool MiniGameTime::IsStart() { return isStart_; }
}
