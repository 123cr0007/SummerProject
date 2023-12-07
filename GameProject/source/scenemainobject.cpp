#include"scenegamemain.h"
#include"DxLib.h"
#include"gamemain.h"
#include"motiondata.h"
#include"framedata.h"
#include"scenegameover.h"
#include"scenegameresult.h"


int SceneGameMain::CharaObjectProcess(int i)
{
	int motChg = -1;
	
	switch(_gChara[i].type)
	{
		case CHARA_TYPE_VENDING:
		{
			if(_gChara[i].HP > 0)
			{
				motChg = MOTION_OBJECT_VENDING;
			}
			else
			{
				if (_gChara[i].core == 1)
				{
					motChg = MOTION_RENJI_CORE;
				}
				else if (_gChara[i].core == 2)
				{
					motChg = MOTION_WASH_CORE;
				}
				else if (_gChara[i].core == 3)
				{
					motChg = MOTION_TV_CORE;
				}
				else if (_gChara[i].core == 4)
				{
					motChg = MOTION_FREEZE_CORE;
				}
				else if (_gChara[i].core == 5) 
				{
					motChg = MOTION_FUN_CORE;
				}
			}
			break;
		}
		case CHARA_TYPE_DOOR:
		{
			if (_gChara[i].DamegeFase == 1) {

				if (_gChara[i].type == CHARA_TYPE_DOOR) {

					StopSoundMem(_bossbgm);
					StopSoundMem(_bgm);

					DeleteChara(i);
					SceneBase* scene = new SceneGameResult();
					ChangeScene(scene);
				}

				_gChara[i].useGravity = 1;
			}
			break;
		}
		case CHARA_TYPE_BATTERY:
		{
			if (_gChara[i].DamegeFase == 1) {
				for (int i = 0; i < CHARA_MAX; i++)
				{
					if (_gChara[i].type == CHARA_TYPE_ARM_R
						|| _gChara[i].type == CHARA_TYPE_ARM_L) {

						arm[0].ArmPULv = 6;
					}
				}

				StopSoundMem(_bgm);
				DeleteSoundMem(_bgm);

				if (bgmMum == 0) {

					PlaySoundMem(_bossbgm, DX_PLAYTYPE_LOOP, TRUE);
					ChangeVolumeSoundMem(255, _bossbgm);

					bgmMum = 1;
				}

				AddChara(CHARA_TYPE_ENEMY_BOSS, 31000, 0, -1, 0);

				DeleteChara(i);

				_gChara[i].DamegeFase = 2;
			}
			break;
		}
	}

	if (_gChara[i].DamegeFase == 1) {

		if (_gChara[i].type != CHARA_TYPE_VENDING) {

			_gChara[i].useGravity = 1;
		}
	}
	
	return motChg;
}