#include "scenegamemain.h"
void SceneGameMain::LoadCharaData()
{
	// キャラ画像配列の初期化
	for (int i = 0; i < _PT_CHARA_ALLNUM_; i++)
	{
		_cgChara[i] = -1;
	}
	// 画像の読み出し
	//プレイヤー
	
	LoadDivGraph("res/PL/stand_left.png", 21, 21, 1, 360, 360, &_cgChara[PT_PLAYER_STAND_L]);
	LoadDivGraph("res/PL/stand_right.png", 21, 21, 1, 360, 360, &_cgChara[PT_PLAYER_STAND_R]);

	LoadDivGraph("res/PL/ran_left.png", 25, 25, 1, 360, 360, &_cgChara[PT_PLAYER_RUN_L]);
	LoadDivGraph("res/PL/ran_right.png", 25, 25, 1, 360, 360, &_cgChara[PT_PLAYER_RUN_R]);

	LoadDivGraph("res/PL/walk_left.png", 21, 21, 1, 360, 360, &_cgChara[PT_PLAYER_WALK_L]);
	LoadDivGraph("res/PL/walk_right.png", 21, 21, 1, 360, 360, &_cgChara[PT_PLAYER_WALK_R]);

	LoadDivGraph("res/PL/knock_left.png", 25, 25, 1, 360, 360, &_cgChara[PT_PLAYER_DAMAGE_L]);
	LoadDivGraph("res/PL/knock_right.png", 25, 25, 1, 360, 360, &_cgChara[PT_PLAYER_DAMAGE_R]);

	LoadDivGraph("res/PL/rise_right.png", 1, 1, 1, 360, 360, &_cgChara[PT_PLAYER_JUMP_UP]);
	LoadDivGraph("res/PL/rise_left.png", 1, 1, 1, 360, 360, &_cgChara[PT_PLAYER_JUMP_UP+1]);

	LoadDivGraph("res/PL/fall.png", 1, 1, 1, 360, 360, &_cgChara[PT_PLAYER_JUMP_DOWN]);

	LoadDivGraph("res/PL/attack_left.png", 21, 21, 1, 360, 360, &_cgChara[PT_PLAYER_ATTACK_L]);
	LoadDivGraph("res/PL/attack_right.png", 21, 21, 1, 360, 360, &_cgChara[PT_PLAYER_ATTACK_R]);
	//腕
	LoadDivGraph("res/arm/roboarm_lr_f.png", 2, 2, 1, 294, 153, &_cgChara[PT_ARM_WAIT_1]);
	LoadDivGraph("res/arm/roboarm_lr_b.png", 2, 2, 1, 300, 153, &_cgChara[PT_ARM_WAIT_2]);
	LoadDivGraph("res/arm/roboarm_lr_f.png", 2, 2, 1, 294, 153, &_cgChara[PT_ARM_ATTACK_1]);
	LoadDivGraph("res/arm/roboarm_lr_b.png", 2, 2, 1, 300, 153, &_cgChara[PT_ARM_ATTACK_2]);
	LoadDivGraph("res/arm/roboarm_lr_f.png", 2, 2, 1, 294, 153, &_cgChara[PT_ARM_FALL_1]);
	LoadDivGraph("res/arm/roboarm_lr_b.png", 2, 2, 1, 300, 153, &_cgChara[PT_ARM_FALL_2]);
	_cgGuard = LoadGraph("res/guard.png");

	//敵
	LoadDivGraph("res/EN/01.png", 1, 1, 1, 160, 120, &_cgChara[PT_RENJI_STAND]);
	//LoadDivGraph("res/EN/renji_death.png", 1, 1, 1, 179, 100, &_cgChara[PT_RENJI_DAMAGE]);
	LoadDivGraph("res/EN/renji_atk.png", 1, 1, 1, 120, 120, &_cgChara[PT_RENJI_ATTACK]);
	LoadDivGraph("res/DR/core_ren.gif", 1, 1, 1, 32, 32, &_cgChara[PT_RENJI_CORE]);
	LoadDivGraph("res/EN/renji_beam.png", 6, 6, 1, 1350, 349, &_cgChara[PT_RENJI_BEAM]);

	LoadDivGraph("res/EN/04.png", 1, 1, 1, 400, 300, &_cgChara[PT_FREEZE_STAND]);
	LoadDivGraph("res/EN/freeze_atk.png", 1, 1, 1, 400, 300, &_cgChara[PT_FREEZE_ATTACK]);
	LoadDivGraph("res/EN/06.png", 1, 1, 1, 80, 60, &_cgChara[PT_FREEZE_BULLET]);
	LoadDivGraph("res/DR/core_rei.gif", 1, 1, 1, 32, 32, &_cgChara[PT_FREEZE_CORE]);

	LoadDivGraph("res/EN/freeze_open.png", 13, 13, 1, 400, 300, &_cgChara[PT_FREEZE_OPEN]);
	LoadDivGraph("res/EN/freeze_close.png", 13, 13, 1, 400, 300, &_cgChara[PT_FREEZE_CLOSE]);


	//テレビ
	//LoadDivGraph("res/著作/midori.png", 1, 1, 1, 160, 184, &_cgChara[PT_TV_STAND]);
	LoadDivGraph("res/EN/03.png", 1, 1, 1, 240, 180, &_cgChara[PT_TV_STAND]);
	LoadDivGraph("res/EN/wind_blade.PNG", 1, 1, 1, 60, 120, &_cgChara[PT_TV_BULLET]);
	LoadDivGraph("res/DR/core_tv.gif", 1, 1, 1, 32, 32, &_cgChara[PT_TV_CORE]);

	//洗濯機
	LoadDivGraph("res/EN/02.png", 1, 1, 1, 360, 270, &_cgChara[PT_WASH_STAND]);
	LoadDivGraph("res/EN/water_a.png", 5, 5, 1, 360, 300, &_cgChara[PT_WASH_BULLET]);
	LoadDivGraph("res/DR/core_sent.gif", 1, 1, 1, 32, 32, &_cgChara[PT_WASH_CORE]);
	LoadDivGraph("res/EN/wash_atk.png", 1, 1, 1, 360, 270, &_cgChara[PT_WASH_ATTACK]);

	//扇風機
	LoadDivGraph("res/EN/05.png", 1, 1, 1, 240, 180, &_cgChara[PT_FUN_STAND]);
	LoadDivGraph("res/DR/core_senp.gif", 1, 1, 1, 32, 32, &_cgChara[PT_FUN_CORE]);

	//ボス
	LoadDivGraph("res/EN/boss.png", 1, 1, 1, 710, 523, &_cgChara[PT_BOSS_STAND]);
	LoadDivGraph("res/EN/boss_beam.png",10,10, 1, 120,  50, &_cgChara[PT_BOSS_BULLET]);

	//オブジェクト
	LoadDivGraph("res/OB/mp_14.png", 1, 1, 1, 180, 279, &_cgChara[PT_CHARA_VENDING]);
	LoadDivGraph("res/OB/mp_01.png", 1, 1, 1, 120, 166, &_cgChara[PT_CHARA_SIGNBORD1]);
	LoadDivGraph("res/OB/mp_02.png", 1, 1, 1, 120, 142, &_cgChara[PT_CHARA_SIGNBORD2]);
	LoadDivGraph("res/OB/mp_15.png", 1, 1, 1, 240, 509, &_cgChara[PT_CHARA_POD1]);
	LoadDivGraph("res/OB/mp_16.png", 1, 1, 1, 240, 509, &_cgChara[PT_CHARA_POD2]);
	LoadDivGraph("res/OB/mp_06.png", 1, 1, 1, 120, 114, &_cgChara[PT_CHARA_SIGNBORD_ARROW]);
	LoadDivGraph("res/OB/mp_03.png", 1, 1, 1, 120, 361, &_cgChara[PT_CHARA_SIGN1]);
	LoadDivGraph("res/OB/mp_04.png", 1, 1, 1, 120, 401, &_cgChara[PT_CHARA_SIGN2]);
	LoadDivGraph("res/OB/mp_05.png", 1, 1, 1, 120, 401, &_cgChara[PT_CHARA_SIGN3]);
	LoadDivGraph("res/OB/mp_11.png", 1, 1, 1, 120, 540, &_cgChara[PT_CHARA_PILLAR1]);
	LoadDivGraph("res/OB/mp_12.png", 1, 1, 1, 120, 540, &_cgChara[PT_CHARA_PILLAR2]);
	LoadDivGraph("res/OB/mp_13.png", 1, 1, 1, 120, 540, &_cgChara[PT_CHARA_PILLAR3]);
	LoadDivGraph("res/OB/mp_17.png", 1, 1, 1, 300, 891, &_cgChara[PT_CHARA_TREE]);
	LoadDivGraph("res/OB/mp_20.png", 1, 1, 1, 60, 58, &_cgChara[PT_CHARA_BU]);
	LoadDivGraph("res/OB/door_goal.png", 1, 1, 1, 120, 180, &_cgChara[PT_CHARA_DOOR]);
	LoadDivGraph("res/OB/mp_20.png", 1, 1, 1, 40, 58, &_cgChara[PT_CHARA_BU]);

	//星//修正する
	star[0].cgStar = LoadGraph("res/cgstar_red.png");

	//ポーズ画面
	_cgPause = LoadGraph("res/pause.png");
	_cgSelect = LoadGraph("res/CraftTable.png");

	//エフェクト
	//爆発
	LoadDivGraph("res/EF/explosion_blue.png", 10, 10, 1, 120, 120, &_cgef[EF_EXPLOSION_BLUE]);
	LoadDivGraph("res/EF/explosion_cyan.png", 10, 10, 1, 120, 120, &_cgef[EF_EXPLOSION_CYAN]);
	LoadDivGraph("res/EF/explosion_green.png", 10, 10, 1, 120, 120, &_cgef[EF_EXPLOSION_GREEN]);
	LoadDivGraph("res/EF/explosion_purple.png", 10, 10, 1, 120, 120, &_cgef[EF_EXPLOSION_PURPLE]);
	LoadDivGraph("res/EF/explosion_red.png", 10, 10, 1, 120, 120, &_cgef[EF_EXPLOSION_RED]);
	LoadDivGraph("res/EF/explosion_yellow.png", 10, 10, 1, 120, 120, &_cgef[EF_EXPLOSION_YELLOW]);

	

	// 効果音の読み込み
	for (int i = 0; i < _SE_ALL_; i++)
	{
		_se[i] = -1;
	}
	_bgm= LoadSoundMem("se/BGM/KAMIKAZE_ATTACK.mp3");
	_bossbgm = LoadSoundMem("se/BGM/爆走列車VINVIN号.mp3");


	_se[VOICE_PLAYER_ATTACK_NORMAL] = LoadSoundMem("se/action_player/attack_1.mp3");
	_se[VOICE_PLAYER_ATTACK_FALL] = LoadSoundMem("se/action_player/attack_2.mp3");
	_se[VOICE_PLAYER_DAMAGE] = LoadSoundMem("se/action_player/hit.mp3");
	_se[SE_ATTACK] = LoadSoundMem("se/attack.mp3");
	_se[SE_DAMAGE] = LoadSoundMem("se/damage.wav");
	_se[SE_POWERUP] = LoadSoundMem("se/action_arm/power_up_arm.mp3");
	_se[SE_ARM_FIRE] = LoadSoundMem("se/action_arm/push_arm.mp3");
	_se[SE_ARM_UP] = LoadSoundMem("se/action_arm/jump_up_arm.mp3");
	_se[SE_ARM_ATTACK_L] = LoadSoundMem("se/action_arm/swing_l_arm.mp3");
	_se[SE_ARM_ATTACK_R] = LoadSoundMem("se/action_arm/swing_r_arm.mp3");
	_se[SE_ARM_ATTACK_CHIP_1] = LoadSoundMem("se/hit_/hit_chip_1.mp3");
	_se[SE_ARM_ATTACK_CHIP_2] = LoadSoundMem("se/hit_/hit_chip_2.mp3");
	_se[SE_ARM_ATTACK_CHIP_3] = LoadSoundMem("se/hit_/hit_chip_3.mp3");
	_se[SE_ARM_ATTACK_ENEMY_1] = LoadSoundMem("se/hit_/hit_enemy_1.mp3");
	_se[SE_ARM_ATTACK_ENEMY_2] = LoadSoundMem("se/hit_/hit_enemy_2.mp3");
	_se[SE_ARM_ATTACK_ENEMY_3] = LoadSoundMem("se/hit_/hit_enemy_3.mp3");
	_se[SE_ENEMY_BEAM] = LoadSoundMem("se/action_enemy/beam.mp3");
	_se[SE_ENEMY_BULLET] = LoadSoundMem("se/action_enemy/bullet.mp3");
	_se[SE_ENEMY_BOMB_1] = LoadSoundMem("se/break_enemy/break_enemy_1.mp3");
	_se[SE_ENEMY_BOMB_2] = LoadSoundMem("se/break_enemy/break_enemy_2.mp3");
	_se[SE_CHIP_GROUND_BREAK_1] = LoadSoundMem("se/break_chip_/break_chip_1.mp3");
	_se[SE_CHIP_GROUND_BREAK_2] = LoadSoundMem("se/break_chip_/break_chip_2.mp3");
	_se[SE_SYSTEM_START] = LoadSoundMem("se/rule_se/game_start.mp3");
	_se[SE_SYSTEM_TIME] = LoadSoundMem("se/rule_se/time.mp3");
	_se[SE_STAR_FLASH] = LoadSoundMem("se/star/spown_star.mp3");
	_se[SE_PL_ATK_SE] = LoadSoundMem("se/system/push.mp3");
	_se[SE_PL_WALK] = LoadSoundMem("se/候補/player_walk.mp3");
}