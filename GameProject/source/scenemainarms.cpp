#include"scenegamemain.h"
#include"DxLib.h"
#include"gamemain.h"


	//前側の腕
int SceneGameMain::CharaArmProcessF(int i, int j)
{
	// 使うキー操作
	int padNo = 0;
	switch(_gChara[i].group)
	{
	case CHARA_GROUP_ARMS:
		padNo = 0;
		break;
	}

	int motChg = -1;
	//
	//どのモーションを使うか番号で整理
	// 1、右攻撃・2、左攻撃・3、空中攻撃・4、浮遊
	//
	int motNo = 0;
	int atk = 0;
	_gChara[i].x = pl_x;
	_gChara[i].y = pl_y;
	_gChara[i].arrow = pl_arrow;

	//浮遊モーション
	if (gPad._key & PAD_INPUT_3)
	{
		if (pl_stand == 0) {
			motNo = 4;
		}
	}
	//右向きパンチ
	if (_gChara[i].arrow == 1) {
		if (gPad._trg & PAD_INPUT_8) {

			motNo = 1;
		}
	}
	//左向きパンチ
	if (_gChara[i].arrow == -1) {
		if (gPad._trg & PAD_INPUT_7) {

			motNo = 2;
		}
	}
	//空中攻撃
	if (pl_stand == 0) {
		if (gPad._trg & PAD_INPUT_8 && gPad._key & PAD_INPUT_7) {

			motNo = 3;
		}
	}

	//基本は待機状態
	if (_gChara[i].motId == MOTION_ARM_F_WAIT_R 
		|| _gChara[i].motId == MOTION_ARM_F_WAIT_L) {

		if (_gChara[i].arrow == 1) {

			motChg = MOTION_ARM_F_WAIT_R;
		}
		else {

			motChg = MOTION_ARM_F_WAIT_L;
		}
	}
	
	switch (_gChara[i].motId)
	{
		//待機状態&浮遊状態の時のみ攻撃可
		case MOTION_ARM_F_WAIT_R:
		case MOTION_ARM_F_WAIT_L:
		case MOTION_ARM_F_RIDE_R:
		case MOTION_ARM_F_RIDE_L: {
			switch (motNo)
			{
			case 4:
				if (_gChara[i].arrow == 1) {

					motChg = MOTION_ARM_F_RIDE_R;
				}
				else {

					motChg = MOTION_ARM_F_RIDE_L;
				}
				break;
			case 1:

				//右通常攻撃
				motChg = MOTION_ARM_F_ATTACK_R;
				break;
			case 2:

				//左通常攻撃
				motChg = MOTION_ARM_F_ATTACK_L;
				break;
			case 3:

				//空中攻撃
				if (_gChara[i].arrow > 0)
				{
					motChg = MOTION_ARM_F_FALL_R;
				}
				// 左向き
				if (_gChara[i].arrow < 0)
				{
					motChg = MOTION_ARM_F_FALL_L;
				}
				break;
			case 0:
				if (_gChara[i].arrow == 1) {

					motChg = MOTION_ARM_F_WAIT_R;
				}
				else {

					motChg = MOTION_ARM_F_WAIT_L;
				}
				break;
			}
		}
	}
	return motChg;
}


//後ろ側の腕
int SceneGameMain::CharaArmProcessB(int i, int j)
{
	// 使うキー操作
	int padNo = 0;
	switch(_gChara[i].group)
	{
	case CHARA_GROUP_ARMS:
		padNo = 0;
		break;
	}

	int motChg = -1;
	//
	//どのモーションを使うか番号で整理
	// 1、右攻撃・2、左攻撃・3、空中攻撃・4、浮遊
	//
	int motNo = 0;
	int atk = 0;
	_gChara[i].x = pl_x;
	_gChara[i].y = pl_y;
	_gChara[i].arrow = pl_arrow;

	if (_gChara[i].motId == MOTION_ARM_B_WAIT_R
		|| _gChara[i].motId == MOTION_ARM_B_WAIT_L) {
		if (_gChara[i].arrow == 1) {

			motChg = MOTION_ARM_B_WAIT_R;
		}
		else {

			motChg = MOTION_ARM_B_WAIT_L;
		}
	}

	//浮遊モーション
	if (gPad._key & PAD_INPUT_3)
	{
		if (pl_stand == 0) {
			motNo = 4;
		}
	}
	//右向きパンチ
	if (_gChara[i].arrow == 1) {
		if (gPad._trg & PAD_INPUT_7) {

			motNo = 1;
		}
	}
	//左向きパンチ
	if (_gChara[i].arrow == -1) {
		if (gPad._trg & PAD_INPUT_8) {

			motNo = 2;
		}
	}
	//空中攻撃
	if (pl_stand == 0) {
		if (gPad._trg & PAD_INPUT_8 && gPad._key & PAD_INPUT_7) {

			motNo = 3;
		}
	}

	switch (_gChara[i].motId)
	{

		case MOTION_ARM_B_WAIT_R:
		case MOTION_ARM_B_WAIT_L:
		case MOTION_ARM_B_RIDE_R:
		case MOTION_ARM_B_RIDE_L: {
			switch (motNo)
			{
			case 4:
				if (_gChara[i].arrow == 1) {

					motChg = MOTION_ARM_B_RIDE_R;
				}
				else {

					motChg = MOTION_ARM_B_RIDE_L;
				}
				break;
			case 1:
				//右通常攻撃
				motChg = MOTION_ARM_B_ATTACK_R;
				break;
			case 2:
				//左通常攻撃
				motChg = MOTION_ARM_B_ATTACK_L;
				break;
			case 3:
				//空中攻撃
				if (_gChara[i].arrow > 0)
				{
					motChg = MOTION_ARM_B_FALL_R;
				}
				// 左向き
				if (_gChara[i].arrow < 0)
				{
					motChg = MOTION_ARM_B_FALL_L;
				}
				break;
			case 0:
				if (_gChara[i].arrow == 1) {

					motChg = MOTION_ARM_B_WAIT_R;
				}
				else {

					motChg = MOTION_ARM_B_WAIT_L;
				}
				break;
			}
		}
	}
	return motChg;
}
