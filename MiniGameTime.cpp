#include "MiniGameTime.h"
#include "Engine/Time.h"
#include "Manager/GameManager/GameManager.h"

namespace MiniGameTime
{
	//時間表示するための変数
	Text* pTimeText_;

	//初期化
	void Initialize()
	{
		//文字の初期化
		ARGUMENT_INITIALIZE(pTimeText_, new Text);
		pTimeText_->Initialize(-0.06f);

		//タイムスタート
		Time::UnLock();
	}

	//描画
	void Draw()
	{
		//ワイド文字列に変換
		wchar_t wtext[FILENAME_MAX];
		std::string text;

		//10秒以上なら
		if (Time::GetTimef() / 10.0f >= 0)
			text = float_to_string(Time::GetTimef(), 3) + "/30.000";
		else
			text = "0" + float_to_string(Time::GetTimef(), 3) + "/30.000";

		size_t ret;
		setlocale(LC_ALL, ".932");
		mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

		//コンボ描画
		pTimeText_->Draw(100, 150, wtext);
	}
}
