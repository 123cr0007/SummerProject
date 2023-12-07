#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"

class SceneGameOver : public SceneBase {
public:
	SceneGameOver();			// コンストラクタ
	virtual ~SceneGameOver();	// デストラクタ

	void	Input() override;	// 入力
	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:
#define CG_BT_TITLE 2
#define CG_BT_NEXT	2

	int		select;
	int		_cgBg;		// 背景画像
	int     miss_cg;
	int		_cgNb[CG_BT_NEXT];		// NEXTSTAGEボタン
	int		_cgTb[CG_BT_TITLE];		// TITLEボタン
	int  _add_alpha;
	int count;
};

