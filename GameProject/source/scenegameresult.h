#pragma once
#include"scenebase.h"

constexpr int RANK_CG_MAX = 3;
constexpr int RANK1 = 0;
constexpr int RANK2 = 1;
constexpr int RANK3 = 2;

constexpr int RESULT_SE_MAX = 5;

class SceneGameResult : public SceneBase {
public:
	SceneGameResult();			// コンストラクタ
	virtual ~SceneGameResult();	// デストラクタ

	void	Input() override;	// 入力
	void	Process() override;	// 計算
	void	Draw() override;	// 描画

	int BreakChipNum;
	int DeadEnemyNum;
	int StageNum = 0;
	int chip_score;
	int time;
	int _seRe[RESULT_SE_MAX];//BGM・SE用配列
protected:

#define CG_BT_TITLE 2
#define CG_BT_NEXT	2
	int		select;
	int		_cgBg;		// 背景画像
	int		_cgNb[CG_BT_NEXT];		// NEXTSTAGEボタン
	int		_cgTb[CG_BT_TITLE];		// TITLEボタン

	int _cgRa[RANK_CG_MAX];//画像用配列


	int count;
	int rank;
};
extern int gStageNum;
extern int cntBrokeBlock;
extern int cntDeadEnem;
extern int score;
extern int gtime;
extern int ArmLv;