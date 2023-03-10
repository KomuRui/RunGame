#include "MiniGameTime.h"
#include "Engine/Time.h"
#include "Engine/ImGuiSet.h"
#include "Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const int START_MAX_COUNT = 4;      			//スタートカウントの最大値
	static const float TEXT_INTERVAL = -0.06f;		    //文字の間隔
	static const float NORMAL_START_COUNT_SCALE = 5.0f; //スタートカウント文字の拡大率
}

namespace MiniGameTime
{
	
	Text* pTimeText_;           //時間表示するための変数
	Text* pStartCountText_;     //スタートするまでのカウントを表示するための文字表示変数
	
	int startCount_;            //スタートするまでのカウント
	float startCountTextScale_; //スタートカウント文字の拡大率

	MiniGameStatus miniGameStatus_;   //ミニゲームの状態
	int resultDis_;                   //最終的な結果(距離)


	//初期化
	void MiniGameTime::Initialize()
	{
		//文字の初期化
		ARGUMENT_INITIALIZE(pTimeText_, new Text);
		pTimeText_->Initialize(TEXT_INTERVAL);
		ARGUMENT_INITIALIZE(pStartCountText_,new Text)
		pStartCountText_->Initialize("Text/NumberFont.png", 128, 256, 10);

		//スタートカウントの初期化
		ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT);
		ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);

		//開始していないに初期化
		ARGUMENT_INITIALIZE(miniGameStatus_, MiniGameStatus::NOT_START);

		//距離初期化
		ARGUMENT_INITIALIZE(resultDis_, ZERO);
	}

	//描画
	void MiniGameTime::Draw()
	{
		switch (miniGameStatus_)
		{
		//まだ開始していない
		case MiniGameStatus::NOT_START:
			StartCountDraw();
			break;
		//ゲーム中
		case MiniGameStatus::PLAY:
			LimitTimeDraw();
			break;
		//終わり
		case MiniGameStatus::END:
			ResultDraw();
			break;

		default:
			break;
		}
			
	}

	//制限時間描画
	void MiniGameTime::LimitTimeDraw()
	{
		//ワイド文字列格納用
		wchar_t wtext[FILENAME_MAX];
		std::string text;

		if (Time::GetTimef() < 30.0f)
		{
			//10秒以上なら
			if (Time::GetTimef() / 10.0f >= 0)
				text = float_to_string(Time::GetTimef(), 3) + "/30.000";
			else
				text = "0" + float_to_string(Time::GetTimef(), 3) + "/30.000";
		}
		else
		{
			text = "30.000/30.000";
			miniGameStatus_ = MiniGameStatus::END;

			//フェードのステータスがFADE_OUT状態じゃなかったら
			if (GameManager::GetStatus() != FADE_OUT)
				GameManager::SetStatus(FADE_OUT, "Image/Fade/BaseFade.png");

			//タイムをロックする
			Time::Lock();

			resultDis_ = GameManager::GetpPlayer()->GetPosition().z;
		}

		//ワイド文字列に変換
		size_t ret;
		setlocale(LC_ALL, ".932");
		mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

		//時間描画
		pTimeText_->Draw(100, 150, wtext,1.0f,TEXT_INTERVAL);
	}

	//スタートカウント描画
	void MiniGameTime::StartCountDraw()
	{
		//もしロックされているのならロック解除
		if (Time::GetLock()) Time::UnLock();

		//一つ前保存
		int beforStartCount = startCount_;

		//startCount_を求める
		ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT - Time::GetTimei());

		//前回と違うのなら拡大率元に戻す
		if (beforStartCount != startCount_) ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);

		//startCount_が0なら
		if (startCount_ == ZERO)
		{
			//Start描画
			pTimeText_->Draw(460, 440, L"START", 3.0f, -0.15f);
		}
		//マイナスなら開始
		else if (startCount_ < ZERO)
		{
			//開始
			ARGUMENT_INITIALIZE(miniGameStatus_, MiniGameStatus::PLAY);

			//タイムリセット
			Time::Reset();
		}
		//startCount_が3以下なら数字描画
		else if (startCount_ <= 3)
		{
			//拡大率を小さくしていく
			startCountTextScale_ -= 0.05f;

			//描画
			pStartCountText_->NumberDraw(960, 440, startCount_, startCountTextScale_);
		}
	}

	//結果表示
	void MiniGameTime::ResultDraw()
	{
		//ワイド文字列格納用
		wchar_t wtext[FILENAME_MAX];
		std::string text = to_string(resultDis_) + "m";

		//ワイド文字列に変換
		size_t ret;
		setlocale(LC_ALL, ".932");
		mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

		//Start描画
		pTimeText_->Draw(760, 540, wtext, 2.5f, -0.15f);
	}

	//開始しているかをセット
	void SetMiniGameStatus(MiniGameStatus status) { miniGameStatus_ = status; }

	//ミニゲームの状態をゲット
	MiniGameStatus  MiniGameTime::GetMiniGameStatus() { return miniGameStatus_; }

	//開始しているか
	bool MiniGameTime::IsPlay() { return (miniGameStatus_ == MiniGameStatus::PLAY); }

	//距離を設定
	void SetResultDis(const int& dis) { resultDis_ = dis; }
}
