#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない


// 当たり判定構造体
struct CHARA_HITRECT {
	int		type;				// 当たり判定の種類
	int		hx, hy, hw, hh;		// 基点からの判定矩形
};

// 当たり判定種類
#define	CHARA_HITRECT_TYPE_NONE		0
#define	CHARA_HITRECT_TYPE_ATTACK	1
#define	CHARA_HITRECT_TYPE_DAMAGE	2
#define CHARA_HITRECT_TYPE_BREAK	3
#define CHARA_HITRECT_TYPE_PLAYER	4
#define CHARA_HITRECT_TYPE_CORE		5

#define	CHARA_HITRECT_NUM	10	

// キャラクタフレーム構造体
// 1枚のフレームに関する設定
struct CHARA_FRAME {
	int		frameId;	// フレームID。固有の番号を振る
	int		cgId;		// 使用画像番号 cgChara[]
	int		cx, cy;		// 画像の基点。足下を指定
	int		w, h;		// 画像サイズ
	float   angle;		// 画像の角度
	CHARA_HITRECT	hit[CHARA_HITRECT_NUM];		// 当たり判定矩形
};



extern struct CHARA_FRAME tblFrame[];
