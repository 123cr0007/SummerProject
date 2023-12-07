#include"scenegamemain.h"
#include"DxLib.h"
#include"gamemain.h"
#include"motiondata.h"
#include"framedata.h"
#include"scenegameover.h"
#include"scenegameresult.h"

int	SceneGameMain::DamegePL(int charaIndex) {
	int motChg;

	if(_gChara[charaIndex].arrow < 0) {
		motChg = MOTION_L_DAMAGE;
	}
	else {
		motChg = MOTION_R_DAMAGE;
	}
	return motChg;
}

int SceneGameMain::CharaPlayerProcess(int i)
{
	int motChg = -1;
	int run = 0;
	int attack = 0;
	// 使うキー操作
	int padNo = 0;
	switch (_gChara[i].type)
	{
	case CHARA_TYPE_PLAYER1:

		padNo = 0;
		break;
	}
	//エネルギー関連
	if (UseEnergy != 0) {
		
		if (Energy > 0) {
			Energy--;
		}
		
	}
	else {
		
		if (Energy < 100 && pl_stand == 1) {

			Energy++;
		}
	}

	//入力でジャンプ
	if(gPad._key & PAD_INPUT_3)
	{	
		//音
		if(CheckSoundMem(_se[SE_ARM_UP]) == 0)//再生中でないなら
		{
			PlaySoundMem(_se[SE_ARM_UP], DX_PLAYTYPE_BACK, TRUE);
		}

		if (Energy > 0) {

			UseEnergy = 1;

			if (_gChara[i].gravity > -10) {
				_gChara[i].gravity -= 5;
			}
		}

		_gChara[i].y += _gChara[i].gravity;

		CheckCharaMove(i, 0, _gChara[i].gravity);
	}
	else {
		_gChara[i].useGravity = 1;
		UseEnergy = 0;
	}

	int useLRMove = 0;	// キーの左右移動をするなら1
	int moveSpeed = 5;	// プレイヤーの移動速度

	//ここさわる


	// 現在のモーションによって操作を分ける
	switch (_gChara[i].motId)
	{
	/*case MOTION_ATTACK_L:
	case MOTION_ATTACK_R:*/
	case MOTION_R_STAND:
	case MOTION_L_STAND:
	case MOTION_R_WALK:
	case MOTION_L_WALK:
	case MOTION_R_RUN:
	case MOTION_L_RUN:
	{	// 立ち/歩き
		// 何も入力が無ければ立ち
		//攻撃入力
		if (gPad._trg & PAD_INPUT_7 || gPad._trg & PAD_INPUT_8)
		{
			if (_gChara[i].arrow < 0)
			{
				motChg = MOTION_L_STAND;

			}
			else
			{
				motChg = MOTION_R_STAND;

			}
		}
		
		if (_gChara[i].arrow < 0)
		{
			motChg = MOTION_L_STAND;
			
		}
		else
		{
			motChg = MOTION_R_STAND;
			
		}

		// 入力によって操作
		useLRMove = 1;
		
		// 左右でモーションだけ切り替える
		//攻撃モーション
		if (gPad._key & PAD_INPUT_1)
		{
			run = 1;
		}
		else
		{
			run = 0;
		}
		if (gPad._key & PAD_INPUT_LEFT)
		{	
			if(run != 0)
			{
				motChg = MOTION_L_RUN;
			}
			else
			{
				motChg = MOTION_L_WALK;
			}
			_gChara[i].arrow = -1;

		}
		if (gPad._key & PAD_INPUT_RIGHT)
		{
			if (attack != 0)
			{
				motChg = MOTION_ATTACK_R;
			}
			if(run != 0)
			{
				motChg = MOTION_R_RUN;
			}
			
			else
			{
				motChg = MOTION_R_WALK;
			}
			_gChara[i].arrow = 1;
		}
		if(_gChara[i].gravity < 0)
		{
			if(_gChara[i].arrow < 0)
			{
				motChg = MOTION_L_JUMP_UP;
			}
			else
			{
				motChg = MOTION_R_JUMP_UP;
			}
		}
		// 下降しはじめたか
		if(_gChara[i].gravity > 0)
		{
			if(_gChara[i].arrow < 0)
			{
				motChg = MOTION_L_JUMP_DOWN;
			}
			else
			{
				motChg = MOTION_R_JUMP_DOWN;
			}
		}

		if (gPad._trg & PAD_INPUT_8 || gPad._trg & PAD_INPUT_7)
		{
			if (_gChara[i].arrow < 0)
			{
				motChg = MOTION_ATTACK_L;
			}
			else
			{
				motChg = MOTION_ATTACK_R;
			}
		}
		
		
		break;
	}
	case MOTION_L_DAMAGE:
	case MOTION_R_DAMAGE:{	
		// ダメージ中
		// 特に何もしない
		useLRMove = 1;
		break;
	}
	case MOTION_L_JUMP_UP:
	case MOTION_R_JUMP_UP:{	
		// ジャンプ上昇中
		// 入力によって操作
		useLRMove = 1;
		// 下降しはじめたか？
		if (_gChara[i].gravity >= 0)
		{
			if (_gChara[i].arrow < 0)
			{
				motChg = MOTION_L_JUMP_DOWN;
			}
			else
			{
				motChg = MOTION_R_JUMP_DOWN;
			}
		}
	}
	case MOTION_L_JUMP_DOWN:
	case MOTION_R_JUMP_DOWN:{	
		// ジャンプ下降中
		// 入力によって操作
		useLRMove = 1;
		// 着地したか？
		if (_gChara[i].stand != 0)
		{
			if (_gChara[i].arrow < 0)
			{
				motChg = MOTION_L_STAND;
			}
			else
			{
				motChg = MOTION_R_STAND;
			}
		}
		break;
	}
	}
	/*for(int i = 0; i < CHARA_MAX; i++) 
	{
		int frameId_k = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);

		HitChipFromFrame(frameId_k, i);
	}*/

	if (_gChara[i].y >= 2700)
	{
		DeleteChara(i);
		SceneBase* scene = new SceneGameOver();
		ChangeScene(scene);

		StopSoundMem(_bossbgm);
		StopSoundMem(_bgm);
	}
	if(_gChara[i].HP <= 0)
	{

		StopSoundMem(_bossbgm);
		StopSoundMem(_bgm);

		DeleteChara(i);
		SceneBase* scene = new SceneGameOver();
		ChangeScene(scene);
	}


	// 入力によって操作
	if (useLRMove != 0)
	{
		int mx = 0;
		if(gPad._key & PAD_INPUT_1)
		{
			moveSpeed = 15;
		}
		if (gPad._key & PAD_INPUT_LEFT)
		{
			mx = -moveSpeed;
		}
		if (gPad._key & PAD_INPUT_RIGHT)
		{
			mx = moveSpeed;
		}
		_gChara[i].x += mx;
		if(_gChara[i].x <= 0)
		{
			_gChara[i].x = 0;
			//_gChara[i].gravity = 0;
		}
		if(_gChara[i].y <= 0)
		{
			_gChara[i].y = 0;
			_gChara[i].gravity = 0;
		}
		if(_gChara[i].x <= 0) 
		{
			_gChara[i].x = 0;
			//_gChara[i].gravity = 0;
		}
		if(_gChara[i].y <= 0)
		{
			_gChara[i].y = 0;
			_gChara[i].gravity = 0;
		}
		// 移動可能か？当たり判定。移動不可なら中で位置調整
		CheckCharaMove(i, mx, 0);
		pl_x = _gChara[i].x;
		pl_y = _gChara[i].y;
		pl_arrow = _gChara[i].arrow;
		pl_stand = _gChara[i].stand;
		pl_gravity = _gChara[i].gravity;
		_gChara[i].stand = pl_stand;
		
	}
	return motChg;
}