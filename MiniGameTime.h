#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//ミニゲームの状態
enum class MiniGameStatus 
{
	NOT_START = 0,
	PLAY,
	END
};

/// <summary>
/// ミニゲームのタイムを表示する
/// </summary>
namespace MiniGameTime
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 制限時間描画
	/// </summary>
	void LimitTimeDraw();

	/// <summary>
	/// スタートカウント描画
	/// </summary>
	void StartCountDraw();

	/// <summary>
	/// 結果表示
	/// </summary>
	void ResultDraw();

	/// <summary>
	/// 開始しているか
	/// </summary>
	/// <returns>trueなら開始している</returns>
	bool IsPlay();

	/// <summary>
	/// 開始しているかをセット
	/// </summary>
	void SetMiniGameStatus(MiniGameStatus status);

	/// <summary>
	/// ミニゲームの状態をゲット
	/// </summary>
	/// <returns>ミニゲームの状態</returns>
	MiniGameStatus GetMiniGameStatus();

	/// <summary>
	/// 距離を設定
	/// </summary>
	/// <param name="dis">設定したい距離</param>
	void SetResultDis(const int& dis);
};

