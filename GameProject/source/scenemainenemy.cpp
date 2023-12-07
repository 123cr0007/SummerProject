#include"scenegamemain.h"
#include"DxLib.h"
#include"gamemain.h"
#include"scenegameresult.h"

SceneGameResult scResult;
void SceneGameMain::Process_Star(int i, int x, int y)
{
	//音
	PlaySoundMem(_se[SE_STAR_FLASH], DX_PLAYTYPE_BACK, TRUE);
	if (star[i].star_use != 0)
	{
		//星をキャラの真ん中へ
		star[i].pos.x = x;
		star[i].pos.y = y;
		star[i].direction += 36 * i;
	}
}

//れんじ移動
int SceneGameMain::MoveRenji(int i) {

	int motChg = -1;

	if (_gChara[i].HP > 0) {

		// 向いている方向に少しずつ進む
		int mx = 0;
		int speed = 0;

		int x = 0;
		int y = 0;

		//攻撃モーションの時は移動止める
		if (_gChara[i].motId == MOTION_RENJI_ATTACK_L
			|| _gChara[i].motId == MOTION_RENJI_ATTACK_R) {
			speed = 0;
		}
		if (_gChara[i].motId == MOTION_RENJI_L_DAMAGE
			|| _gChara[i].motId == MOTION_RENJI_R_DAMAGE) {
			speed = 0;
		}
		else {
			speed = 1;
		}

		if (_gChara[i].stand == 1) {
			mx = _gChara[i].arrow * speed;
		}

		_gChara[i].x += mx;

		// 移動可能か？当たり判定。移動不可なら中で位置調整
		if (CheckCharaMove(i, mx, 0) == 1) {
			// 当たったので方向反転

			_gChara[i].arrow *= -1;

			if (_gChara[i].arrow < 0)
			{

				motChg = MOTION_RENJI_L_STAND;
			}
			else
			{
				motChg = MOTION_RENJI_R_STAND;
			}
		}
	}
	else if (_gChara[i].DamegeFase == 1)
	{
		_gChara[i].core = 1;
		//音
		PlaySoundMem(_se[SE_ENEMY_BOMB_1], DX_PLAYTYPE_BACK, TRUE);
		//エフェクト
		AddEffect(i, 0, 0, EFFECT_TYPE_BOMB_RED);

		//Process_Star(i,_gChara[i].x, _gChara[i].y);

		if (star[i].star_use != 1)
		{
			//star[i][j].checkStar = 1;

			star[i].star_use = 1;
			
			Process_Star(i, _gChara[i].x, _gChara[i].y);
		}

		cntDeadEnem++;
		_gChara[i].DamegeFase = 2;
		motChg = MOTION_RENJI_CORE;
	}



	if (_gChara[i].DamegeFase == 2) {

		motChg = MOTION_RENJI_CORE;
	}
	
	return motChg;
}

//冷蔵庫移動
//とりまおき
int SceneGameMain::MoveFreeze(int i) {
	int motChg = -1;

	if (_gChara[i].HP > 0)
	{

		// 向いている方向に少しずつ進む
		int mx = 0;
		int speed = 0;

		int x = 0;
		int y = 0;

		//攻撃モーションの時は移動止める
		if (_gChara[i].motId == MOTION_WASH_ATTACK_L
			|| _gChara[i].motId == MOTION_WASH_ATTACK_R) {
			speed = 0;
		}

		_gChara[i].movecnt--;

		if (_gChara[i].movecnt >= 0) {

			speed = 1;
		}
		else if (_gChara[i].movecnt <= 0 && _gChara[i].movecnt >= -60) {
			speed = 0;
		}
		else if (_gChara[i].movecnt <= -60) {
			_gChara[i].movecnt = 120;
		}

		if (_gChara[i].stand == 1) {

			mx = _gChara[i].arrow * speed;
		}

		_gChara[i].x += mx;


		// 移動可能か？当たり判定。移動不可なら中で位置調整
		if (CheckCharaMove(i, mx, 0) == 1) {
			// 当たったので方向反転

			_gChara[i].arrow *= -1;

			if (_gChara[i].arrow < 0)
			{

				motChg = MOTION_FREEZE_STAND_L;
			}
			else
			{
				motChg = MOTION_FREEZE_STAND_R;
			}
		}
	}
	else if (_gChara[i].DamegeFase == 1) {

		_gChara[i].core = 4;
		//音
		PlaySoundMem(_se[SE_ENEMY_BOMB_1], DX_PLAYTYPE_BACK, TRUE);
		//エフェクト
		AddEffect(i, 0, 0, EFFECT_TYPE_BOMB_CYAN);
		cntDeadEnem++;
		_gChara[i].DamegeFase = 2;
		motChg = MOTION_FREEZE_CORE;
	}

	return motChg;
}

//テレビ移動
int SceneGameMain::MoveTV(int i) {
	int motChg = -1;

	int mx = 0;
	int speed = 5;

	if (_gChara[i].HP > 0) {
		//攻撃モーションの時は移動止める
		if (_gChara[i].motId == MOTION_WASH_ATTACK_L
			|| _gChara[i].motId == MOTION_WASH_ATTACK_R) {
			speed = 0;
		}
		else {
			speed = 5;
		}
		if (_gChara[i].y >= pl_y - 500) {
			_gChara[i].y -= 3;
		}
		else {
			_gChara[i].y += 3;
		}

		_gChara[i].movecnt--;

		//どっちに進むか
		if (_gChara[i].movecnt <= 0) {

			if (_gChara[i].x >= pl_x) {

				_gChara[i].arrow = -1;
			}
			else {
				_gChara[i].arrow = 1;
			}
			_gChara[i].movecnt = 60;
		}

		if (_gChara[i].x <= pl_x + 5) {

			if (_gChara[i].x >= pl_x - 5) {

				_gChara[i].CheckAttack += 1;
			}
		}

		//モーション切り替え
		if (_gChara[i].arrow < 0)
		{

			motChg = MOTION_TV_STAND_L;
		}
		else
		{
			motChg = MOTION_TV_STAND_R;
		}

		//移動
		mx = _gChara[i].arrow * speed;
		_gChara[i].x += mx;
	}
	else if (_gChara[i].DamegeFase == 1) {

		_gChara[i].core = 3;
		//音
		PlaySoundMem(_se[SE_ENEMY_BOMB_1], DX_PLAYTYPE_BACK, TRUE);
		//エフェクト
		AddEffect(i, 0, 0, EFFECT_TYPE_BOMB_PURPLE);
		cntDeadEnem++;

		_gChara[i].DamegeFase = 2;
		motChg = MOTION_TV_CORE;
	}

	return motChg;
}

//洗濯機移動
int SceneGameMain::MoveWash(int i) {
	int motChg = -1;

	int mx = 0;
	int speed = 3;

	if (_gChara[i].HP > 0 && _gChara[i].DamegeFase == 0) {

		if (_gChara[i].stand == 1) {

			_gChara[i].gravity = -15;
		}

		mx = _gChara[i].arrow * speed;
		_gChara[i].x += mx;

		// 移動可能か？当たり判定。移動不可なら中で位置調整
		if (CheckCharaMove(i, mx, 0) == 1) {
			// 当たったので方向反転

			_gChara[i].arrow *= -1;

			if (_gChara[i].arrow < 0)
			{

				motChg = MOTION_WASH_STAND_L;
			}
			else
			{
				motChg = MOTION_WASH_STAND_R;
			}
		}
	}

	if (_gChara[i].DamegeFase == 1) {

		_gChara[i].core = 2;
		//音
		PlaySoundMem(_se[SE_ENEMY_BOMB_1], DX_PLAYTYPE_BACK, TRUE);
		//エフェクト
		AddEffect(i, 0, 0, EFFECT_TYPE_BOMB_BLUE);

		cntDeadEnem++;

		_gChara[i].DamegeFase = 2;
		motChg = MOTION_WASH_CORE;
	}

	return motChg;
}

//ボス移動
int SceneGameMain::MoveBoss(int i) {
	int motChg = -1;

	int mx = 0;
	int speed = 10; 

	boss_x = _gChara[i].x; 


	checkdistance = boss_x - pl_x;

	if (checkdistance >= 1000) {

		speed = 30;
	}
	else if (checkdistance >= 900) {

		speed = 12;
	}
	else if (checkdistance <= 800) {

		speed = 10;
	}

	mx = _gChara[i].arrow * speed;
	_gChara[i].x += mx;

	motChg = MOTION_WASH_STAND_L;

	return motChg;
}

//ダメージくらった時のモーション切り替え
int SceneGameMain::DamegeEnemy(int i) {
	int motChg;

	switch (_gChara[i].type)
	{
	case CHARA_TYPE_ENEMY_RENJI:

		if (_gChara[i].arrow < 0) {

			motChg = MOTION_RENJI_L_DAMAGE;
		}
		else {
			motChg = MOTION_RENJI_R_DAMAGE;
		}
		break;

	case CHARA_TYPE_ENEMY_FREEZER:

		if (_gChara[i].arrow < 0) {

			motChg = MOTION_FREEZE_DAMAGE_L;
		}
		else {
			motChg = MOTION_FREEZE_DAMAGE_R;
		}
		break;
	case CHARA_TYPE_ENEMY_TV:

		if (_gChara[i].arrow < 0) {

			motChg = MOTION_TV_DAMAGE_L;
		}
		else {
			motChg = MOTION_TV_DAMAGE_R;
		}
		break;
	case CHARA_TYPE_ENEMY_WASH:

		if (_gChara[i].arrow < 0) {

			motChg = MOTION_WASH_DAMAGE_L;
		}
		else {
			motChg = MOTION_WASH_DAMAGE_R;
		}
		break;
	case CHARA_TYPE_ENEMY_FUN:

		if (_gChara[i].arrow < 0) {

			motChg = MOTION_FUN_DAMAGE_L;
		}
		else {
			motChg = MOTION_FUN_DAMAGE_R;
		}
		break;
	case CHARA_TYPE_ENEMY_BOSS:

		motChg = MOTION_BOSS_STAND_L;
		{
			break;
		}
	}

	//音
	PlaySoundMem(_se[SE_ARM_ATTACK_ENEMY_1], DX_PLAYTYPE_BACK, TRUE);
	return motChg;
}

//弾が画面外行ったときに消すよう
void SceneGameMain::DeleteProcess(int i) {
	if (_gChara[i].x < 0) {
		DeleteChara(i);
	}
	if (_gChara[i].x > 15000) {

		DeleteChara(i);
	}

	if (_gChara[i].y < 0) {

		DeleteChara(i);
	}

	if (_gChara[i].y > 2300) {

		DeleteChara(i);
	}
}


//レンジビーム発射
int	SceneGameMain::AttackRenji_StandBy(int i)
{

	int motChg = -1;

	int x = 0;
	int y = 0;

	if (_gChara[i].arrow < 0) {
		//ビームの位置
		x = _gChara[i].x - 250;
		y = _gChara[i].hy / 2;
		y = _gChara[i].y + y;

		//攻撃範囲内入ってるか
		_gChara[i].CheckAttack = rennji_x - pl_x;
	}
	else {
		//ビームの位置
		x = _gChara[i].x + 250;
		y = _gChara[i].hy / 2;
		y = _gChara[i].y + y;

		//攻撃範囲内入ってるか
		_gChara[i].CheckAttack = pl_x - rennji_x;
	}

	if (_gChara[i].AtkCnt >= 0) {
		_gChara[i].AtkCnt--;
	}

	//蓮司の前にいるかつ距離500以内か
	if (_gChara[i].HP > 0) {
		if (_gChara[i].CheckAttack > 0) {
			if (_gChara[i].CheckAttack <= 500) {
				if (_gChara[i].AtkCnt <= 0) {
					if (_gChara[i].stand == 1) {

						AddChara(CHARA_TYPE_RENJI_BULLET, x, y, _gChara[i].arrow,0);
						//音
						PlaySoundMem(_se[SE_ENEMY_BEAM], DX_PLAYTYPE_BACK, TRUE);

						//モーション変更
						if (_gChara[i].arrow > 0) {
							motChg = MOTION_RENJI_ATTACK_R;
						}
						else {
							motChg = MOTION_RENJI_ATTACK_L;
						}

						_gChara[i].AtkCnt = 120;
					}
				}
			}
		}
	}

	return motChg;
}

//冷蔵庫弾発射
int	SceneGameMain::AttackFreeze_StandBy(int i)
{


	int motChg = -1;

	int x = 0;
	int y = 0;

	if (_gChara[i].arrow == -1) {
		//ビームの位置
		x = _gChara[i].x - 250;

		y = _gChara[i].hy / 2;
		y = _gChara[i].y + y;

		//攻撃範囲内入ってるか
		_gChara[i].CheckAttack = freeze_x - pl_x;
	}
	else {
		//ビームの位置
		x = _gChara[i].x + 250;
		
		y = _gChara[i].hy / 2;
		y = _gChara[i].y + y;

		//攻撃範囲内入ってるか
		_gChara[i].CheckAttack = pl_x - freeze_x;
	}

	if (_gChara[i].AtkCnt > 0) {
		_gChara[i].AtkCnt--;
	}


	//蓮司の前にいるかつ距離500以内か
	if (_gChara[i].HP > 0) {

		if (_gChara[i].AtkCnt == 0) {

			if (_gChara[i].CheckAttack <= 800) {

				if (_gChara[i].CheckAttack > 0) {

					if (_gChara[i].stand == 1) {

						//モーション変更
						if (_gChara[i].arrow < 0) {
							motChg = MOTION_FREEZE_OPEN_L;
						}
						else {
							motChg = MOTION_FREEZE_OPEN_R;
						}

						_gChara[i].AtkCnt = -1;
					}
				}
			}
		}
	}

	if (_gChara[i].AtkCnt <= 0) {

		if (_gChara[i].motId == MOTION_FREEZE_ATTACK_R
			|| _gChara[i].motId == MOTION_FREEZE_ATTACK_L)
		{
			//音
			PlaySoundMem(_se[SE_ARM_FIRE], DX_PLAYTYPE_BACK, TRUE);

			AddChara(CHARA_TYPE_FREEZER_BULLET, x, y, _gChara[i].arrow, 0);

			_gChara[i].AtkCnt = 180;
		}
	}

	if (motChg != -1) {
		return motChg;
	}
	else {
		return MoveFreeze(i);
	}

}

//テレビ弾発射
int	SceneGameMain::AttackTV_StandBy(int i)
{
	int motChg = -1;

	int x = 0;
	int y = 0;

	if (_gChara[i].arrow == 1) {
		//ビームの位置
		x = _gChara[i].x - 0;
		y = _gChara[i].y + 0;
	}
	else {
		//ビームの位置
		x = _gChara[i].x + 0;
		y = _gChara[i].y + 0;
	}

	//真上通ったのがｎ回以上なら
	if (_gChara[i].HP > 0) {
		if (_gChara[i].CheckAttack >= 10) {

			AddChara(CHARA_TYPE_TV_BULLET, x, y, -1,0);

			//音
			PlaySoundMem(_se[SE_ENEMY_BEAM], DX_PLAYTYPE_BACK, TRUE);

			//モーション変更
			if (_gChara[i].arrow < 0) {
				motChg = MOTION_TV_ATTACK_L;
			}
			else {
				motChg = MOTION_TV_ATTACK_R;
			}
			_gChara[i].CheckAttack = 0;
		}
	}

	if (motChg != -1) {
		return motChg;
	}
	else {
		return MoveTV(i);
	}
}

//洗濯機弾発射
int	SceneGameMain::AttackWash_StandBy(int i) {
	int motChg = -1;

	int x = 0;
	int y = 0;

	if (_gChara[i].arrow == -1) {
		//ビームの位置
		x = _gChara[i].x;
		y = _gChara[i].hy / 2;
		y = _gChara[i].y + y;

		//攻撃範囲内入ってるか
		_gChara[i].CheckAttack = wash_x - pl_x;
	}
	else {
		//ビームの位置
		x = _gChara[i].x;
		y = _gChara[i].hy / 2;
		y = _gChara[i].y + y;

		//攻撃範囲内入ってるか
		_gChara[i].CheckAttack = pl_x - wash_x;
	}

	if (_gChara[i].AtkCnt >= 0) {
		_gChara[i].AtkCnt--;
	}


	//蓮司の前にいるかつ距離500以内か
	if (_gChara[i].HP > 0) {
		if (_gChara[i].CheckAttack > 0) {
			if (_gChara[i].CheckAttack <= 300) {
				if (_gChara[i].AtkCnt <= 0) {
					if (_gChara[i].stand == 1) {

						//AddChara(CHARA_TYPE_WASH_BULLET, x, y, _gChara[i].arrow,0);

						//モーション変更
						/*if (_gChara[i].arrow < 0) {
							motChg = MOTION_WASH_ATTACK_L;
						}
						else {
							motChg = MOTION_WASH_ATTACK_R;
						}*/
						_gChara[i].AtkCnt = 120;
					}
				}
			}
		}
	}

	if (motChg != -1) {

		return motChg;
	}
	else {
		return MoveWash(i);
	}
}

//扇風機弾発射
int	SceneGameMain::AttackFun_StandBy(int i) {

	int oldHP = _gChara[i].HP;

	int motChg = -1;

	int x = 0;
	int y = 0;

	if (_gChara[i].arrow == 1) {

		//ビームの位置
		x = _gChara[i].x + 150;

		y = _gChara[i].hy / 2;
		y = _gChara[i].y + y;
	}
	else {

		//ビームの位置
		x = _gChara[i].x - 150;

		y = _gChara[i].hy / 2;
		y = _gChara[i].y + y;
	}

	if (_gChara[i].HP > 0) {

		if (_gChara[i].CheckAttack == 1) {

			AddChara(CHARA_TYPE_WASH_BULLET, x, y, _gChara[i].arrow,0);

			_gChara[i].CheckAttack = 0;
		}
	}

	
	return motChg;
}

//ボス弾プロセス
int	SceneGameMain::AttackBoss_StandBy(int i) {

	int motChg = -1;

	
	//ここに番号入れる
	int AtkNum = 0;

	int x = 0, y = 0;

	if (_gChara[i].arrow == 1) {

		//ビームの位置
		x = _gChara[i].x + 400;

		y = _gChara[i].y + 500;
	}
	else {

		//ビームの位置
		x = _gChara[i].x - 400;

		y = _gChara[i].y + 220;
	}


	if (_gChara[i].HP > 0) {
		if (_gChara[i].CheckAttack <= 0) {

			if (checkAtkNum <= 3) {
				checkAtkNum++;
			}
			else {
				checkAtkNum = 0;
			}

			checkAtkNum = 4;

			switch (checkAtkNum)
			{
			case 0:

				AddChara(CHARA_TYPE_RENJI_BULLET, x, y, _gChara[i].arrow,0);

				//_gChara[i].CheckAttack = 300;

				break;
			case 1:

				AddChara(CHARA_TYPE_FREEZER_BULLET, x, y, _gChara[i].arrow,0);

				//_gChara[i].CheckAttack = 300;

				break;
			case 2:

				AddChara(CHARA_TYPE_TV_BULLET, x, y, _gChara[i].arrow,0);

				break;
			case 3:

				AddChara(CHARA_TYPE_WASH_BULLET, x, y, _gChara[i].arrow,0);

				break;
			case 4:

				AddChara(CHARA_TYPE_BOSS_BULLET, x - 620, y - 100, _gChara[i].arrow,0);

				break;
			}

			_gChara[i].CheckAttack = 120;

		}
		else {
			_gChara[i].CheckAttack--;
		}

		if (motChg != -1) {

			return motChg;
		}
		else {
			return MoveBoss(i);
		}
	}

}


//敵の処理まとめ
int SceneGameMain::CharaEnemyProcess(int i)
{
	int motChg = -1;
	switch (_gChara[i].type)
	{
	case CHARA_TYPE_ENEMY_RENJI:
	{
		rennji_x = _gChara[i].x;
		rennji_y = _gChara[i].y;

		motChg = AttackRenji_StandBy(i);

	case MOTION_RENJI_L_STAND:
	case MOTION_RENJI_R_STAND:
	{

		motChg = MoveRenji(i);
	}


	break;
	}
	case CHARA_TYPE_ENEMY_FREEZER:
	{
		freeze_x = _gChara[i].x;
		freeze_y = _gChara[i].y;

		motChg = AttackFreeze_StandBy(i);

	break;
	}
	//テレビ処理終わり
	case CHARA_TYPE_ENEMY_TV:
	{
		tv_x = _gChara[i].x;
		tv_y = _gChara[i].y;

		motChg = AttackTV_StandBy(i);
	case MOTION_TV_STAND_L:
	{
	//	motChg = MoveTV(i);

		break;
	}
	}
	//洗濯機処理owari
	case CHARA_TYPE_ENEMY_WASH:
	{
		wash_x = _gChara[i].x;
		wash_y = _gChara[i].y;

		motChg = AttackWash_StandBy(i);

		break;

	}
	//扇風機
	case CHARA_TYPE_ENEMY_FUN:
	{
		fun_x = _gChara[i].x;
		fun_y = _gChara[i].y;

		AttackFun_StandBy(i);

		if (_gChara[i].DamegeFase == 1) {

			_gChara[i].core = 5;

			motChg = MOTION_FUN_CORE;
			//音
			PlaySoundMem(_se[SE_ENEMY_BOMB_1], DX_PLAYTYPE_BACK, TRUE);
			//エフェクト
			AddEffect(i, 0, 0, EFFECT_TYPE_BOMB_GREEN);

			cntDeadEnem++;

			_gChara[i].DamegeFase = 2;

		}

		break;

	}
	case CHARA_TYPE_ENEMY_BOSS:
	{

		AttackBoss_StandBy(i);

		break;
	}
	//蓮司ビーム
	case CHARA_TYPE_RENJI_BULLET:
	{

		motChg = BalletProcess_Renji(i);

		break;
	}
	//冷蔵庫弾
	case CHARA_TYPE_FREEZER_BULLET:
	{
		if (_gChara[i].HP <= 0) {
			DeleteChara(i);
		}

		DeleteProcess(i);

		BalletProcess_Freeze(i);
		break;
	}
	//テレビ弾
	case CHARA_TYPE_TV_BULLET:
	{

		DeleteProcess(i);

		BalletProcess_TV(i);
		break;
	}
	}
	return motChg;
}