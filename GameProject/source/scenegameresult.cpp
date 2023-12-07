#include"scenegameresult.h"
#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "SceneGameMain.h"
#include "SceneGameTitle.h"


SceneGameResult::SceneGameResult() {
	_cgBg = LoadGraph("res/UI/next.png");

	select = 0;

	for(int c=0;c < RANK_CG_MAX;c++)
	{
		_cgRa[c] = 0;
	}

	for (int b = 0; b < RESULT_SE_MAX; b++)
	{
		_seRe[b] = 0;
	}

	count = 0;
	rank = 0;


	_cgRa[RANK1] = LoadGraph("res/UI/rank_1.png");
	_cgRa[RANK2] = LoadGraph("res/UI/rank_2.png");
	_cgRa[RANK3] = LoadGraph("res/UI/rank_3.png");


	_seRe[0] = LoadSoundMem("se/BGM/わんさかダッシュ.mp3");
	_seRe[1] = LoadSoundMem("se/system/don.mp3");
	_seRe[2] = LoadSoundMem("se/system/re_1.mp3");
	_seRe[3] = LoadSoundMem("se/system/re_2.mp3");
	_seRe[4] = LoadSoundMem("se/system/re_3.mp3");

	PlaySoundMem(_seRe[0], DX_PLAYTYPE_BACK, TRUE);

	if (score >= 30000)
	{
		rank = 2;
		PlaySoundMem(_seRe[4], DX_PLAYTYPE_BACK, TRUE);
	}
	else if (score >= 20000)
	{
		rank = 1;
		PlaySoundMem(_seRe[3], DX_PLAYTYPE_BACK, TRUE);
	}
	else if (score >= 0)
	{
		rank = 0;
		PlaySoundMem(_seRe[2], DX_PLAYTYPE_BACK, TRUE);
	}
}

SceneGameResult::~SceneGameResult() {
	DeleteGraph(_cgBg);
	for (int c = 0; c < RANK_CG_MAX; c++)
	{
		DeleteGraph(_cgRa[c]);
	}

	for (int b = 0; b < RESULT_SE_MAX; b++)
	{
		DeleteSoundMem(_seRe[b]);
	}
}

void SceneGameResult::Input() {
	// 何もしない
}

void SceneGameResult::Process() {
	/*if(gPad._trg & PAD_INPUT_1) {
		SceneBase* scene = new SceneGameMain();
		ChangeScene(scene);
	}*/
	if (gStageNum < 5)
	{
		if (gPad._trg & PAD_INPUT_4)
		{
			StageNum = gStageNum;
			StageNum++;
			gStageNum = StageNum;
			SceneBase* scene = new SceneGameMain();
			ChangeScene(scene);
		}
	}
	else
	{
		if (gPad._trg & PAD_INPUT_4)
		{
			SceneBase* scene = new SceneGameTitle();
			ChangeScene(scene);
			gStageNum = 1;
		}
	}
	//if(gPad._trg & PAD_INPUT_4) {
//	SceneBase* scene = new SceneGameTitle();
//	ChangeScene(scene);
//}


	if (count >= 0)//透明度をあげる
	{
		count += 4 ;
	}

	if (count == 256)//音をならす
	{
		PlaySoundMem(_seRe[1], DX_PLAYTYPE_BACK, TRUE);
	}
}

void SceneGameResult::Draw() {
	


	//評価画像描画////////////////////////////////
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count);

	DrawGraph(130, 100, _cgRa[rank], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	////////////////////////////////////////////

	SetFontSize(50);


	DrawFormatString(1000, 100, GetColor(rand()%256, rand() % 256, rand() % 256), "R E S U L T ");


	DrawFormatString(1000, 200, GetColor(255, 255, 255), "破壊したブロック数 =");
	DrawFormatString(1000, 200, GetColor(rand() % 256, rand() % 256, rand() % 256), "　　　　　　　　　　 %d", cntBrokeBlock);
	
	DrawFormatString(1000, 300, GetColor(255, 255, 255), "敵の撃破数 =");	
	DrawFormatString(1000, 300, GetColor(rand() % 256, rand() % 256, rand() % 256), "　　　　　　 %d", cntDeadEnem);

	DrawFormatString(1000, 400, GetColor(255, 255, 255), "TIME = ");
	DrawFormatString(1000, 400, GetColor(rand() % 256, rand() % 256, rand() % 256), "       %d", gtime);
	if (gStageNum < 5) {
		DrawFormatString(1400, 950, GetColor(255, 255, 255), "次のステージへ　B");
	}
	else
	{
		DrawFormatString(1400, 950, GetColor(255, 255, 255), "タイトルへ戻る　B");
	}
	SetFontSize(100);

	DrawFormatString(1000, 600, GetColor(255, 255, 255), "S C O R E ");
	DrawFormatString(1000, 800, GetColor(rand() % 256, rand() % 256, rand() % 256), "%d", score);

	SetFontSize(30);
}
