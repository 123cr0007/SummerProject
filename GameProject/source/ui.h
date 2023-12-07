#pragma once


	//UI用定数
constexpr auto UI_MAX = 7;			//最大値

constexpr auto UI_BASE = 0;          //UI
constexpr auto UI_POS_X_BASE = 0;	//UI置き場のx座標
constexpr auto UI_POS_Y_BASE = 900;	//UI置き場のy座標

constexpr auto UI_HP = 1;			//HPバー
constexpr auto UI_POS_X_HP = 10;		//HPバーのx座標
constexpr auto UI_POS_Y_HP = 910;	//HPバーのy座標
constexpr auto UI_HP_MAX = 545;		//HPバー最大値

constexpr auto UI_EN = 2;			//エネルギーバー
constexpr auto UI_POS_X_EN = 1310;	//エネルギーバーのx座標
constexpr auto UI_POS_Y_EN = 910;	//エネルギーバーのy座標

constexpr auto UI_START = 3;			//スタート
constexpr auto UI_POS_X_START = 0;	//スタートのx座標
constexpr auto UI_POS_Y_START = 0;	//スタートのy座標

constexpr auto UI_CLEAR = 4;			//クリア
constexpr auto UI_POS_X_CLEAR = 0;	//クリアのx座標
constexpr auto UI_POS_Y_CLEAR= 0;	//クリアのy座標

constexpr auto UI_OVER = 5;			//ゲームオーバー
constexpr auto UI_POS_X_OVER = 0;	//ゲームオーバーのx座標
constexpr auto UI_POS_Y_OVER = 0;	//ゲームオーバーのy座標

constexpr auto UI_ISBREAK = 6;			//どのブロックが破壊可能か
constexpr auto UI_POS_X_BREAK = 660;	//上のx座標
constexpr auto UI_POS_Y_BREAK = 930;	//道場のy座標


class UI
{
public:

		UI();			//コンストラクター
		virtual ~UI();	//デストラクター

		int Process();

		void Draw(int pl_hp);

protected:
	//変数
	int _ui[UI_MAX];

	float hp;

	float ui_hp;
	
	int time ;
	int second;

	int _uiCover;
};
extern int overtime;

extern int cntBrokeBlock;
extern int cntDeadEnem;
extern int score;
extern int gtime;