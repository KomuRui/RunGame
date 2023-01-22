#include "Time.h"
#include "Global.h"
#include <vector>

//�萔�錾
namespace
{
	//60�i�@
	const char HEX = 60;
}

//�ϐ�
namespace
{
	char Hours_;
	char Minuts_;
	double Seconds_;
	bool Lock_ = true;		    //���݂̏�ԂŌŒ肷�邩
	std::vector<int> CountFps_;	//���݂̃t���[�����[�g���i�[���Ă�������
	int FPS_;		            //���������ɍő�t���[�����[�g���i�[���Ă���
	int LookAt_;	            //�z��̂ǂ������邩
}

namespace Time
{
	//������
	void Initialize(int FPS)
	{
		//�e�ϐ�������
		ARGUMENT_INITIALIZE(Hours_,ZERO);
		ARGUMENT_INITIALIZE(Minuts_, ZERO);
		ARGUMENT_INITIALIZE(Seconds_, ZERO);
		ARGUMENT_INITIALIZE(FPS_, FPS);
		ARGUMENT_INITIALIZE(LookAt_, ZERO);

		CountFps_.clear();		//�O�̂��߂̏�����
		CountFps_.reserve(FPS);	//�v�f�����m�ۂ��Ă���

		while (CountFps_.size() != CountFps_.capacity())
		{
			CountFps_.push_back(FPS);
		}
	}

	void Update()
	{
		for (int i = 0; i < CountFps_.size(); i++)
		{
			//�ő�t���[�����[�g�𒴂��邱�Ƃ͂Ȃ��̂�
			if (CountFps_.at(i) < FPS_)
				CountFps_.at(i)++;
		}

		LookAt_++;
		if (LookAt_ >= FPS_)
			LookAt_ -= FPS_;

		//Lock����Ă�����X�V���Ȃ�
		if (!Lock_)
		{
			float fps = CountFps_.at(LookAt_) * 0.98f;
			Seconds_ += 1.0 / fps;
		}

		CountFps_.at(LookAt_) = 0;
	}

	void Reset()
	{
		Hours_ = 0;
		Minuts_ = 0;
		Seconds_ = 0;
	}

	void Lock()
	{
		Lock_ = true;
	}

	void UnLock()
	{
		Lock_ = false;
	}

	bool GetLock()
	{
		return Lock_;
	}

	int GetTimei()
	{
		return (int)Seconds_;
	}
	float GetTimef()
	{
		return (float)Seconds_;
	}
	double GetTime()
	{
		return Seconds_;
	}
}