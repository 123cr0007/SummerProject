#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"

class SceneGameLogo : public SceneBase {
public:
	SceneGameLogo();			// コンストラクタ
	virtual ~SceneGameLogo();	// デストラクタ

	void	Input() override;	// 入力
	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:
	int		_cgBg;		// 背景画像
	int		_step;		// フェードインアウト用ステップ
	int		_bgm;
};
