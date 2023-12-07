#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"
#include <vector>
#include <string>

constexpr int SOUND_MAX = 5;//音素材の最大数
constexpr int CG_MAX = 2; //2D素材の最大数

constexpr int TITLE = 0;//タイトル画像
constexpr int UI_B_PUSH = 1;//Bボタンではじめる画像

class SceneGameTitle : public SceneBase {
public:
	SceneGameTitle();			// コンストラクタ
	virtual ~SceneGameTitle();	// デストラクタ

	void	Input() override;	// 入力
	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:

	int _bgm[SOUND_MAX];//効果音
	int _cg[CG_MAX]; //画像

	//カウント用
	int count;
	int _add_alpha;


	int		_step;		// フェードインアウト用ステップ

};

