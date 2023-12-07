#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "SceneGameOver.h"
#include "SceneGameTitle.h"
#include "scenegamemain.h"


SceneGameOver::SceneGameOver() {
	_cgBg = LoadGraph("res/UI/gameover.png");
	miss_cg = LoadGraph("gole.bmp");
	LoadDivGraph("res/button_next_div.png", 2, 2, 1, 600, 300, _cgNb);
	LoadDivGraph("res/button_title_div.png", 2, 2, 1, 600, 300, _cgTb);
	select = 0;
	count = 0;
	_add_alpha = 1;
}

SceneGameOver::~SceneGameOver() {
	DeleteGraph(_cgBg);
}

void SceneGameOver::Input() {
	// âΩÇ‡ÇµÇ»Ç¢
}

void SceneGameOver::Process() {
	
	/*if(gPad._trg & PAD_INPUT_RIGHT)
	{
		select = 1;
	}
	if(gPad._trg & PAD_INPUT_LEFT)
	{
		select = 0;
	}*/
	//ìßâﬂêßå‰////////////
	if (count == 255) {
		_add_alpha = -1;
	}
	else if (count == 0) {
		_add_alpha = +1;
	}
	count += _add_alpha;

	if (gPad._trg & PAD_INPUT_4) {
		SceneBase* scene = new SceneGameMain();
		ChangeScene(scene);
	}
	/////////////////////
}

void SceneGameOver::Draw() {

	DrawGraph(0, 0, miss_cg, TRUE);

	//gameoverÇï`âÊ///////////////////////
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count);

	DrawGraph(560, 290, _cgBg, TRUE);
	SetFontSize(100);
	DrawFormatString(700, 950, GetColor(255, 255, 255), "ÉäÉgÉâÉCÅ@B");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	////////////////////////////////////////////

	/*if(select == 0) 
	{
		DrawGraph(300, 500, _cgNb[1], TRUE);
		DrawGraph(1200, 500, _cgTb[0], TRUE);
	}
	if(select == 1)
	{
		DrawGraph(300, 500, _cgNb[0], TRUE);
		DrawGraph(1200, 500, _cgTb[1], TRUE);
		if(gPad._trg & PAD_INPUT_4) {
			SceneBase* scene = new SceneGameTitle();
			ChangeScene(scene);
		}
	}*/
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "select!=%d",select);
}
