#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "SceneGameTitle.h"
#include "SceneGameMain.h"
#include "scenegameresult.h"


SceneGameTitle::SceneGameTitle() 
{
	for (int b = 0; b < SOUND_MAX; b++) 
	{
		_bgm[b]= 0;
	}
	for (int c = 0; c < CG_MAX; c++)
	{
		_cg[c] = 0;
	}

	_cg[0] = LoadGraph("res/UI/title.png");
	_cg[1] = LoadGraph("res/UI/start.png");

	_bgm[0] = LoadSoundMem("se/BGM/Clarity_of_My_Sight_2.mp3");
	_bgm[1] = LoadSoundMem("se/system/push.mp3");
	PlaySoundMem(_bgm[0], DX_PLAYTYPE_BACK, TRUE);

	gStageNum = 0;

	count = 255;
	_add_alpha = 1;

	_step = 0;
}

SceneGameTitle::~SceneGameTitle() 
{
	for (int c = 0; c < CG_MAX; c++)
	{
		DeleteGraph(_cg[c]);
	}
	
	for (int b = 0; b < SOUND_MAX; b++)
	{
		StopSoundMem(_bgm[b], 0);
	}
	
}

void SceneGameTitle::Input() {
	// �������Ȃ�
}

void SceneGameTitle::Process() {

	switch (_step) {
	case 0:
		// �t�F�[�h�C���J�n
		ColorFadeIn(60);
		_step++;
		break;
	case 1:
		if (IsColorFade() == 0) {
			// �t�F�[�h�C���I��
			_step++;
		}
		break;
	case 2:
		// �ʏ폈��
	if (gPad._trg & PAD_INPUT_4) {
			// �t�F�[�h�A�E�g�J�n
			ColorFadeOut(0, 0, 0, 60);

		PlaySoundMem(_bgm[1], DX_PLAYTYPE_BACK, TRUE);//���ʉ�

			_step++;
		}
		break;
	case 3:
		if (IsColorFade() == 0) {
			// �t�F�[�h�A�E�g�I��
		SceneBase* scene = new SceneGameMain();
		ChangeScene(scene);
	}
break;
}
	//���ߐ���////////////
	if (count == 255) {
		_add_alpha = -5;
	}
	else if (count == 0) {
		_add_alpha = +5;
	}
	count += _add_alpha;
	/////////////////////
}

void SceneGameTitle::Draw(){

	DrawGraph(0, 0, _cg[TITLE], FALSE);//�^�C�g���摜��`��

	//B�{�^���ł͂��߂��`��///////////////////////
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count);

	DrawGraph(50, 500, _cg[UI_B_PUSH], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	////////////////////////////////////////////

	//DrawFormatString(100, 100, GetColor(0, 255, 255), "SceneGameTitle!!");
}
