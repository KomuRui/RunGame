#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

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
	/// 開始しているか
	/// </summary>
	/// <returns>trueなら開始している</returns>
	bool IsStart();
};

