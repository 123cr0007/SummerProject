#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "mymath.h"
#include "mydraw.h"
#include "SceneGameMain.h"
#include "SceneGameOver.h"
#include "scenegameresult.h"
#include "mapdata.h"
#include "tiledata.h"
#include "Map.h"
#include "map_create.h"

SceneGameResult scresult;

void SceneGameMain::DeleteChara(int charaIndex)
{
	_gChara[charaIndex].type = CHARA_TYPE_NONE;
}

// キャラの地形/キャラ当たり判定を取り出す
MYRECT SceneGameMain::GetHitRectFromChara(int charaIndex)
{
	MYRECT rc = { 0, 0, 0, 0 };

	if (_gChara[charaIndex].type != CHARA_TYPE_NONE)
	{
		rc.w = _gChara[charaIndex].hw;
		rc.h = _gChara[charaIndex].hh;
		rc.x = _gChara[charaIndex].x + _gChara[charaIndex].hx;
		rc.y = _gChara[charaIndex].y + _gChara[charaIndex].hy;
	}
	/*if(_gChara[charaIndex].group==CHARA_GROUP_ARMS)
	{

	}*/

	return rc;
}

// フレームIDと、hitrectIndexから、左右反転に応じた当たり判定RECTを得る
// (cx,cy)は基点座標
MYRECT SceneGameMain::GetHitRectFromFrame(int frameId, int hitrectIndex, int cx, int cy, int mirror_lr)
{
	MYRECT rc = { 0, 0, 0, 0 };

	int type = tblFrame[frameId].hit[hitrectIndex].type;
	if (type != CHARA_HITRECT_TYPE_NONE)
	{
		// 矩形の大きさ
		int x, y, w, h;
		w = tblFrame[frameId].hit[hitrectIndex].hw;
		h = tblFrame[frameId].hit[hitrectIndex].hh;

		// 左右反転するか？
		if (mirror_lr == 0)
		{
			// しない
			// 描画位置は、基点分ずらした場所
			x = cx - tblFrame[frameId].cx;
			y = cy - tblFrame[frameId].cy;
			// (x,y)は描画する左上位置。矩形分ずらす
			x = x + tblFrame[frameId].hit[hitrectIndex].hx;
			y = y + tblFrame[frameId].hit[hitrectIndex].hy;
		}
		else
		{
			// する
			// 描画位置は、左右反転してから基点分ずらした場所
			x = cx - (tblFrame[frameId].w - tblFrame[frameId].cx);
			y = cy - tblFrame[frameId].cy;
			// (x,y)は描画する左上位置。矩形分ずらす
			x = x + (tblFrame[frameId].w - tblFrame[frameId].hit[hitrectIndex].hx) - w;
			y = y + tblFrame[frameId].hit[hitrectIndex].hy;
		}

		rc.x = x;
		rc.y = y;
		rc.w = w;
		rc.h = h;
	}

	return rc;
}

// キャラが移動可能か、当たり判定
// mx, my はキャラの移動方向
// 当たり判定でヒットしたら1を、していなければ0を返す
int SceneGameMain::CheckCharaMove(int charaIndex, int mx, int my)
{
	int hit = 0;
	int i = charaIndex;		// [i] を自キャラとする

	// マップチップとの当たり判定
	chip::MapData::HITSLIDE hitSlide;
	MYRECT rc = GetHitRectFromChara(i);
	hitSlide = mapData->IsHitBox(rc.x, rc.y, rc.w, rc.h, mx, my);


	if (hitSlide.hit != 0)
	{
		if (_gChara[i].group != CHARA_GROUP_ARMS)
		{
			// 当たったので、位置を動かす
			_gChara[i].x += hitSlide.slide_x;
			_gChara[i].y += hitSlide.slide_y;
			hit = 1;
		}
	}

	//// 別キャラとの当たり判定を行う
	//int j;					// [j] を別キャラとする

	//// 自分が別のキャラと重なっているか？（重なっていたら押し出される）
	for (int j = 0; j < CHARA_MAX; j++)
	{
		// 自キャラじゃない、かつキャラタイプがある
		if (i != j && _gChara[j].type != CHARA_TYPE_NONE)
		{
			//とりまおき
			//判定をグループにした。
			if (i != CHARA_TYPE_PLAYER1 && _gChara[j].group != CHARA_GROUP_ARMS
				 && _gChara[j].group != CHARA_GROUP_OBJECT && _gChara[j].group != CHARA_GROUP_ENEMY)
			{
				// [i]と[j]で当たり判定
				MYRECT rc_i = GetHitRectFromChara(i);
				MYRECT rc_j = GetHitRectFromChara(j);

				// RECTの当たり判定
				if (IsHitBox(
					rc_i.x, rc_i.y, rc_i.w, rc_i.h,
					rc_j.x, rc_j.y, rc_j.w, rc_j.h) == 1
					)
				{
					return _gChara[j].type;
				}
			}
		}
	}
	return hit;
}
//int count = 0;
int SceneGameMain::HitChipFromFrame(int frameId, int charaIndex)//フレーム情報使うやつ
{

	int i = charaIndex;
	for (int ii = 0; ii < CHARA_HITRECT_NUM; ii++)
	{
		//frameId_i = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);

		if (tblFrame[frameId].hit[ii].type == CHARA_HITRECT_TYPE_BREAK)
		{		// [i]のダメージ判定
				// 二つの当たり判定矩形を取り出す
			MYRECT rc_i = GetHitRectFromFrame(frameId, ii, _gChara[i].x, _gChara[i].y, tblMotion[_gChara[i].motId].mirror_lr);

			if (_gChara[i].type != CHARA_TYPE_ENEMY_BOSS) {

				mapData->HitChipDamage(rc_i.x, rc_i.y, rc_i.w, rc_i.h, arm[1].ArmPULv);
			}
			else {
				mapData->HitChipDamage(rc_i.x, rc_i.y, rc_i.w, rc_i.h, 100);
			}
		}
	}
	return 1;
}


// tblFrame[] の配列番号を、frameIdで調べる
int SceneGameMain::SearchFrame(int frameId)
{
	int n = 0;
	while (tblFrame[n].frameId != -1)
	{
		if (tblFrame[n].frameId == frameId)
		{
			// 見つかった。[n]が配列番号
			return n;
		}
		n++;
	}
	// 見つからなかった（本来来てはいけない）
	return -1;
}

// キャラのモーション変更指示
void SceneGameMain::CharaChangeMotion(int charaIndex, int motion)
{
	if (_gChara[charaIndex].motId != motion)
	{
		_gChara[charaIndex].motId = motion;
		_gChara[charaIndex].motcnt = 0;
		_gChara[charaIndex].animcnt = 0;
	}
}

float SceneGameMain::BGMoveX()
{
	if (gStageNum < 4) {

		float map_w = MAPSIZE_W * CHIPSIZE_W * 2;
		float pl_clear = pl_x / map_w;
		float bg_rest_x = pl_clear * 3840;
		return bg_rest_x;
	}
	else {

		float map_w = 510 * CHIPSIZE_W * 2;
		float pl_clear = pl_x / map_w;
		float bg_rest_x = pl_clear * 3840;
		return bg_rest_x;
	}
}

