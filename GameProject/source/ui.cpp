#include "DxLib.h"
#include "ui.h"
#include "scenegamemain.h"
#include "scenegameover.h"
#include "scenegameresult.h"
UI::UI()
{
	//UI
	_ui[UI_HP] = LoadGraph("res/UI/hp.png");
	_ui[UI_EN] = LoadGraph("res/UI/Energie.png");
	_ui[UI_START] = LoadGraph("res/UI/start.png");
	_ui[UI_CLEAR] = LoadGraph("res/UI/clear.png");
	_ui[UI_OVER] = LoadGraph("res/UI/gameover.png");
	_ui[UI_BASE] = LoadGraph("res/UI/space.png");
	_ui[UI_ISBREAK] = LoadGraph("res/UI/isbreak.png");
	_uiCover = LoadGraph("res/UI/block_cover.png");

	hp = 0;
	ui_hp = 0;
	time = 0;
	second = 300;
}
UI::~UI()
{
	//画像を削除
	for(int i = 0; i < UI_MAX; i++) {

		DeleteGraph(_ui[i]);
	}
}

int UI::Process()
{
	if(second >=250)
	{
		score = (cntBrokeBlock+cntDeadEnem) * 10;
	}
	else if (second >= 200)
	{
		score = (cntBrokeBlock + cntDeadEnem) * 9;
	}
	else if (second >= 150)
	{
		score = (cntBrokeBlock + cntDeadEnem) * 8;
	}
	else if (second >= 100)
	{
		score = (cntBrokeBlock + cntDeadEnem) * 7;
	}
	else if (second >= 50)
	{
		score = (cntBrokeBlock + cntDeadEnem) * 6;
	}
	else if (second >= 0)
	{
		score = (cntBrokeBlock + cntDeadEnem) * 5;
	}
	time++;
	if(time>=60)
	{
		second-=1;
		time = 0;
	}
	if(second<=0)
	{
		return 1;
	}

	gtime = second;//リザルトにもっていく

	return 0;//終了
}

void UI::Draw(int pl_hp)
{
	hp = pl_hp / (float)10;
	ui_hp = hp * (float)UI_HP_MAX;
	DrawGraph(UI_POS_X_BASE, UI_POS_Y_BASE, _ui[UI_BASE], TRUE);//表示は一番下に

	/*hp = pl_hp * 5.8f;

	if (pl_hp > 0) {
		ui_hp = UI_HP_MAX / pl_hp;
		DrawBoxAA(UI_POS_X_HP + 20, UI_POS_Y_HP + 19, UI_POS_X_HP + hp, UI_POS_Y_HP + 140, GetColor(255, 0, 0), TRUE);
	}*/
	
	DrawFormatString(UI_POS_X_HP + 100, UI_POS_Y_HP + 100, GetColor(255, 255, 255), "HP = %d", pl_hp);

	DrawBoxAA(UI_POS_X_HP+36, UI_POS_Y_HP+17, UI_POS_X_HP + UI_HP_MAX+36, UI_POS_Y_HP+142 , GetColor(100, 0, 0), TRUE);
	if (pl_hp > 0) 
	{
		DrawBoxAA(UI_POS_X_HP + 36, UI_POS_Y_HP + 17, UI_POS_X_HP + 36 + ui_hp, UI_POS_Y_HP + 142, GetColor(255, 0, 100), TRUE);
	}
	//スコア・タイム表示////////////////////////////////////////////////////////////////////////
	SetFontSize (50);
	DrawFormatString(UI_POS_X_EN + 36, UI_POS_Y_EN + 100, GetColor(0, 0, 0), "TIME");
	DrawFormatString(UI_POS_X_EN + 150, UI_POS_Y_EN + 100, GetColor(0,0, 0), "%d", second);
	DrawFormatString(UI_POS_X_EN + 90, UI_POS_Y_EN + 50, GetColor(0, 0, 0), "SCORE");
	DrawFormatString(UI_POS_X_EN + 220, UI_POS_Y_EN + 50, GetColor(0, 0, 0), "%d", score);
	SetFontSize(10);
	/////////////////////////////////////////////////////////////////////////////////////////

	DrawGraph(UI_POS_X_HP, UI_POS_Y_HP, _ui[UI_HP], TRUE);
	DrawGraph(UI_POS_X_EN, UI_POS_Y_EN, _ui[UI_EN], TRUE);
	DrawGraph(UI_POS_X_BREAK, UI_POS_Y_BREAK, _ui[UI_ISBREAK], TRUE);



	if (ArmLv <= 4) {
		DrawGraph(UI_POS_X_BREAK + 120 * 4, UI_POS_Y_BREAK, _uiCover, TRUE);
		if (ArmLv <= 3) {
			DrawGraph(UI_POS_X_BREAK + 120 * 3, UI_POS_Y_BREAK, _uiCover, TRUE);
			if (ArmLv <= 2) {
				DrawGraph(UI_POS_X_BREAK + 120 * 2, UI_POS_Y_BREAK, _uiCover, TRUE);
				if (ArmLv <= 1) {
					DrawGraph(UI_POS_X_BREAK + 120, UI_POS_Y_BREAK, _uiCover, TRUE);
					if (ArmLv <= 0) {
						DrawGraph(UI_POS_X_BREAK, UI_POS_Y_BREAK, _uiCover, TRUE);
					}
				}
			}
		}
	}
	
}