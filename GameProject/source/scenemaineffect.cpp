#include "SceneGameMain.h"
#include "mydraw.h"
#include "camera.h"

int SceneGameMain::AddEffect(int i, int fx, int fy, int type)//fx,fyは表示座標いじる為のもの。typeで表示エフェクトを指定。
{
	for(int j = 0; j < EFFECT_MAX; j++)
	{
		if(ef[j].type == EFFECT_TYPE_NONE)
		{
			int frameId = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);
			ef[j].x = _gChara[i].x - tblFrame[frameId].cx;
			ef[j].y =  _gChara[i].y - tblFrame[frameId].cy;
			ef[j].arrow = _gChara[i].arrow;
			ef[j].useEf = 1;
			ef[j].type = type;
			switch (type)
			{
			case EFFECT_TYPE_BOMB_BLUE:
				ef[j].time = 100;
				ef[j].useGraphNum = 10;
				ef[j].startGraphNum = 0;
				ef[j].cg = EF_EXPLOSION_BLUE;
				break;
			
			case EFFECT_TYPE_BOMB_CYAN:
				ef[j].time = 100;
				ef[j].useGraphNum = 10;
				ef[j].startGraphNum = 0;
				ef[j].cg = EF_EXPLOSION_CYAN;
				break;
			
			case EFFECT_TYPE_BOMB_GREEN:
				ef[j].time = 100;
				ef[j].useGraphNum = 10;
				ef[j].startGraphNum = 0;
				ef[j].cg = EF_EXPLOSION_GREEN;
				break;
			
			case EFFECT_TYPE_BOMB_PURPLE:
				ef[j].time = 100;
				ef[j].useGraphNum = 10;
				ef[j].startGraphNum = 0;
				ef[j].cg = EF_EXPLOSION_PURPLE;
				break;

			case EFFECT_TYPE_BOMB_RED:
				ef[j].time = 100;
				ef[j].useGraphNum = 10;
				ef[j].startGraphNum = 0;
				ef[j].cg = EF_EXPLOSION_RED;
				break;

			case EFFECT_TYPE_BOMB_YELLOW:
				ef[j].time = 100;
				ef[j].useGraphNum = 10;
				ef[j].startGraphNum = 0;
				ef[j].cg = EF_EXPLOSION_YELLOW;
				break;
			}
			return j;
			return type;
		}
	}
	return -1;
}

int  SceneGameMain::EffectAnm(int i)//スタートは0番から。使用する枚数を指定。一連のエフェクト表示にかける時間。typeにはLoadDivGraphが入ってるところ。
{
	int StartGraphNum = ef[i].startGraphNum;
	int UseGraphNum = ef[i].useGraphNum;
	int UseEffectTime = ef[i].time;
	int anmcnt = UseEffectTime;
	
	if(framecount > anmcnt)
	{
		if(StartGraphNum < UseGraphNum)
		{
			ef[i].startGraphNum++;
		}
		if(StartGraphNum >= UseGraphNum)
		{
			DeleteEffect(i);
		}
		framecount = 0;
	}
	framecount++;
	return 1;
}

void SceneGameMain::DeleteEffect(int i) 
{
	ef[i].type = EFFECT_TYPE_NONE;
}

void SceneGameMain::DrawEffect(MATRIX mView,int i)
{
	
	if (ef[i].useEf != 0)
	{
		// キャラのモーションフレームから情報を得る
		int eftype = ef[i].type;

		// 描画位置は、基点分ずらした場所
		int x = ef[i].x;
		int y = ef[i].y;

		// ※このx,yはDrawGraph()用に画像の左上なので、MyDrawModiGraph()の中心位置には合わない
		VECTOR world = VGet(x, y, 0);

		// 画像の中心をworld座標とするので、サイズ/2だけずらす
		world.x += 60;
		world.y += 60;
		//爆発青
		if (eftype == EFFECT_TYPE_BOMB_BLUE)
		{
			ef[i].cg = EF_EXPLOSION_BLUE + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//爆発水
		if (eftype == EFFECT_TYPE_BOMB_CYAN)
		{
			ef[i].cg = EF_EXPLOSION_CYAN + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//爆発緑
		if (eftype == EFFECT_TYPE_BOMB_GREEN)
		{
			ef[i].cg = EF_EXPLOSION_GREEN + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//爆発紫
		if (eftype == EFFECT_TYPE_BOMB_PURPLE)
		{
			ef[i].cg = EF_EXPLOSION_PURPLE + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//爆発赤
		if (eftype == EFFECT_TYPE_BOMB_RED)
		{
			ef[i].cg = EF_EXPLOSION_RED + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//爆発黄
		if (eftype == EFFECT_TYPE_BOMB_YELLOW)
		{
			ef[i].cg = EF_EXPLOSION_YELLOW + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		EffectAnm(i);
	}
}