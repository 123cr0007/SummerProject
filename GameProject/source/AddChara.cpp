#include "scenegamemain.h"

// キャラの追加
int SceneGameMain::AddChara(int type, int x, int y, int arrow,int core)
{
	// 追加できる配列を検索
	for(int i = 0; i < CHARA_MAX; i++)
	{
			if(_gChara[i].type == CHARA_TYPE_NONE)
			{
				// キャラを[i]に追加。キャラタイプによって初期化情報が変わる
				_gChara[i].type = type;
				_gChara[i].x = x;
				_gChara[i].y = y;
				_gChara[i].arrow = arrow;
				_gChara[i].hx = 0;
				_gChara[i].hy = 0;
				_gChara[i].hw = 0;
				_gChara[i].hh = 0;
				_gChara[i].HP = 0;
				_gChara[i].Pow = 0;
				_gChara[i].core = 0;
				_gChara[i].useChara = 0;
				_gChara[i].useGravity = 1;
				_gChara[i].layer = 0;
				_gChara[i].DamegeFase = 0;
				_gChara[i].CheckAttack = 0;
				_gChara[i].AtkCnt = 120;
				_gChara[i].movecnt = 0;
				_gChara[i].core = 0;
				_gChara[i].direction = 0;
				_gChara[i].group = CHARA_GROUP_NONE;
				//デバッグ用

				switch(type)
				{
				case CHARA_TYPE_PLAYER1:
					_gChara[i].hx = -50;
					_gChara[i].hy = -130;
					_gChara[i].hw = 110;
					_gChara[i].hh = 250;
					_gChara[i].motId = MOTION_R_STAND;
					_gChara[i].HP = 10;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_PLAYER;
					_gChara[i].layer = 3;
					break;

				case CHARA_TYPE_ARM_L:
					_gChara[i].Pow = 10;
					_gChara[i].useChara = 1;
					_gChara[i].HP = 1;
					_gChara[i].group = CHARA_GROUP_ARMS;
					arm[0].ArmType = ARM_TYPE_NORMAL;
					arm[0].ArmPULv = 0;
					arm[0].ArmAtkType = ARM_ATTACK_NORMAL;
					armtype = arm[0].ArmType;
					_gChara[i].motId = MOTION_ARM_B_WAIT_R;
					_gChara[i].useGravity = 0;
					_gChara[i].layer = 2;
					break;

				case CHARA_TYPE_ARM_R:
					_gChara[i].Pow = 10;
					_gChara[i].useChara = 1;
					_gChara[i].HP = 1;
					_gChara[i].group = CHARA_GROUP_ARMS;
					arm[1].ArmType = ARM_TYPE_NORMAL;
					arm[1].ArmPULv = 0;
					arm[1].ArmAtkType = ARM_ATTACK_NORMAL;
					armtype = arm[1].ArmType;
					_gChara[i].motId = MOTION_ARM_F_WAIT_R;
					_gChara[i].useGravity = 0;
					_gChara[i].layer = 4;
					break;
				case CHARA_TYPE_ENEMY_RENJI:
					_gChara[i].hx = -40;
					_gChara[i].hy = -120;
					_gChara[i].hw = 90;
					_gChara[i].hh = 120;
					_gChara[i].HP = 10;
					_gChara[i].Pow = 1;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_RENJI_L_STAND;
					_gChara[i].useChara = 1;
					_gChara[i].layer =1;
					break;

				case CHARA_TYPE_ENEMY_FREEZER:
					_gChara[i].hx = -110;
					_gChara[i].hy = -300;
					_gChara[i].hw = 225;
					_gChara[i].hh = 300;
					_gChara[i].HP = 50;
					_gChara[i].Pow = 1;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_FREEZE_STAND_L;
					_gChara[i].useChara = 1;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_ENEMY_TV:
					_gChara[i].hx = -90;
					_gChara[i].hy = -270;
					_gChara[i].hw = 180;
					_gChara[i].hh = 180;
					_gChara[i].HP = 10;
					_gChara[i].Pow = 1;
					_gChara[i].y = pl_y - 500;
					_gChara[i].useGravity = 0;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_TV_STAND_R;
					_gChara[i].useChara = 1;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_ENEMY_WASH:
					_gChara[i].hx = -180;
					_gChara[i].hy = -120;
					_gChara[i].hw = 360;
					_gChara[i].hh = 120;
					_gChara[i].HP = 50;
					_gChara[i].Pow = 1;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_WASH_STAND_L;
					_gChara[i].useChara = 1;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_ENEMY_FUN:
					_gChara[i].hx = -60;
					_gChara[i].hy = -180;
					_gChara[i].hw = 120;
					_gChara[i].hh = 180;
					_gChara[i].HP = 50;
					_gChara[i].Pow = 1;
					_gChara[i].CheckAttack = 0;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_FUN_STAND_L;
					_gChara[i].useChara = 1;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_ENEMY_BOSS:
					_gChara[i].HP = 1000000000;
					_gChara[i].Pow = 50;
					_gChara[i].CheckAttack = 120;
					_gChara[i].useGravity = 0;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_BOSS_STAND_L;
					_gChara[i].useChara = 1;
					_gChara[i].layer = 1;
					break;
				case CHARA_TYPE_RENJI_BULLET:
					_gChara[i].useGravity = 0;
					_gChara[i].Pow = 1;
					_gChara[i].useChara = 1;
					_gChara[i].motId = MOTION_RENJI_BEAM_L;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_FREEZER_BULLET:
					_gChara[i].useGravity = 0;
					_gChara[i].Pow = 1;
					_gChara[i].useChara = 1;
					_gChara[i].HP = 20;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_FREEZE_BULLET;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_TV_BULLET:
					_gChara[i].useGravity = 0;
					_gChara[i].Pow = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_TV_BULLET;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_WASH_BULLET:
					_gChara[i].useGravity = 0;
					_gChara[i].Pow = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_WASH_BULLET;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_FUN_BULLET:
					_gChara[i].useGravity = 0;
					_gChara[i].Pow = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_WASH_BULLET;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_BOSS_BULLET:
					_gChara[i].useGravity = 0;
					_gChara[i].Pow = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_ENEMY;
					_gChara[i].motId = MOTION_BOSS_BULLET;
					_gChara[i].layer = 1;
					break;

				case CHARA_TYPE_VENDING:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].core = core;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_VENDING;
					break;

				case CHARA_TYPE_SIGNBOARD1:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_SIGNBORD1;
					break;

				case CHARA_TYPE_SIGNBOARD2:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_SIGNBORD2;
					break;

				case CHARA_TYPE_SIGNBOARD_ARROW:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_SIGNBORD_ARROW;
					break;

				case CHARA_TYPE_SIGN1:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_SIGN1;
					break;

				case CHARA_TYPE_SIGN2:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_SIGN2;
					break;

				case CHARA_TYPE_SIGN3:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_SIGN3;
					break;

				case CHARA_TYPE_TREE:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_TREE;
					break;
				case CHARA_TYPE_PILLAR1:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_PILLAR1;
					
					break;
				case CHARA_TYPE_PILLAR2:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity =0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_PILLAR2;

					break;
				case CHARA_TYPE_PILLAR3:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_PILLAR3;

					break;

				case CHARA_TYPE_POD1:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_POD1;

					break;
				case CHARA_TYPE_POD2:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_POD2;

					break;

				case CHARA_TYPE_DOOR:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_DOOR;

					break;

				case CHARA_TYPE_BATTERY:

					_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;
					_gChara[i].useGravity = 0;
					_gChara[i].HP = 1;
					_gChara[i].useChara = 1;
					_gChara[i].group = CHARA_GROUP_OBJECT;
					_gChara[i].motId = MOTION_OBJECT_BATTERY;

					break;
				}


				_gChara[i].motcnt = 0;		// モーションカウンタ。0～
				_gChara[i].animcnt = 0;	// アニメーションカウンタ。0～
				_gChara[i].gravity = 0;	// 重力による加速値
				_gChara[i].stand = 0;		// 床フラグ。着地していたら1

				_gChara[i].respawn = 0;	// リスポーンフラグ。リスポーンするなら1
				_gChara[i].respawn_x = _gChara[i].x;	// リスポーン座標
				_gChara[i].respawn_y = _gChara[i].y;	// リスポーン座標

				// 追加できた配列番号を返す
				return i;
			}
		
	}
	// 追加できなかった
	return -1;
}