#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "mydraw.h"
#include "mapdata.h"
#include "Map.h"
#include "map_create.h"
#include "mymath.h"
#include "scenegamemain.h"
#include "scenegameresult.h"

chip::MapData::MapData()
{
	_tiledMap = nullptr;

	// マップチップの読み込み
	//LoadDivGraph("res/platformer_simpleA_sheet.png", 64, 8, 8, tilesets.tilewidth, tilesets.tileheight, _cgChip);
	//LoadDivGraph("res/map1.png", 25, 5, 5, tilesets.tilewidth, tilesets.tileheight, _cgChip);
	//_cgStar[0] = LoadGraph("res/cgstar_blue.png");
	LoadDivGraph("res/EF/star.png", 5, 5, 1, 40, 40, _cgStar);
	LoadDivGraph("res/EF/block_break_1.png", 10, 10, 1, 120, 120, &_cgef[EF_BLOCK_DARK]);
	LoadDivGraph("res/EF/block_break_2.png", 10, 10, 1, 120, 120, &_cgef[EF_BLOCK_ROCK]);
	LoadDivGraph("res/EF/spark_1.png", 10, 10, 1, 120, 120, &_cgef[EF_SPARK_PURPLE]);
	LoadDivGraph("res/EF/spark_2.png", 10, 10, 1, 120, 120, &_cgef[EF_SPARK_GREEN]);
	LoadDivGraph("res/EF/spark_3.png", 10, 10, 1, 120, 120, &_cgef[EF_SPARK_WHITE]);
	LoadDivGraph("res/EF/spark_5.png", 10, 10, 1, 120, 120, &_cgef[EF_SPARK_RED]);
	LoadDivGraph("res/EF/spark_6.png", 10, 10, 1, 120, 120, &_cgef[EF_SPARK_YELLOW]);

	_cgParticle = LoadGraph("res/EF/stardot.gif");

	star_se = LoadSoundMem("se/star/spown_star.mp3");
	rock_se = LoadSoundMem("se/break_chip_/break_rock.mp3");
	iron_se = LoadSoundMem("se/break_chip_/break_metal.mp3");
	glass_se = LoadSoundMem("se/break_chip_/break_glass.mp3");
	soil_se = LoadSoundMem("se/break_chip_/tuti.mp3");
	concrete_se = LoadSoundMem("se/break_chip_/zawazawa.mp3");
	kusa_se = LoadSoundMem("se/break_chip_/kusa.mp3");
	chip_se = LoadSoundMem("se/候補/doka-nn.mp3");
	chip_1_se = LoadSoundMem("se/hit_/hit_enemy_1.mp3");
	ChangeVolumeSoundMem(150, rock_se);
	ChangeVolumeSoundMem(150, iron_se);
	ChangeVolumeSoundMem(150, soil_se);
	ChangeVolumeSoundMem(150, glass_se);
	ChangeVolumeSoundMem(150, concrete_se);
	ChangeVolumeSoundMem(150, kusa_se);
	ChangeVolumeSoundMem(150, chip_se);
	ChangeVolumeSoundMem(150, chip_1_se);
	// キャラデータの初期設定
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		ef[i].type = EF_TYPE_NONE;		// いったん、全キャラをnoneに
	}
	
	for(int i = 0; i < STAR_SPAWN_MAX; i++)
	{
		for(int j = 0; j < STAR_MAX; j++)
		{
			star[i][j].direction = 0;
			star[i][j].pos.x = 0;
			star[i][j].pos.y = 0;
			star[i][j].pos.z = 0;
			star[i][j].speed = 10;
			star[i][j].star_use = 0;
		}
	}
	c_cnt = 0;
}

chip::MapData::~MapData()
{
	auto& tilesets = _tiledMap->tilesets[0];

	int j = tilesets.tilecount;

	delete _tiledMap;//mapを削除
	_tiledMap = nullptr;//初期化

	for (int i = 0; i < j; i++)
	{
		DeleteGraph(_cgChip[i]);
	}

	InitSoundMem;
}
// パーティクル
chip::Particle2::Particle2(int cg, float x, float y, float vx, float vy, int cnt, int w, int h) {
	_cg = cg;
	_w = w;
	_h = h;

	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_cnt = cnt;
}

chip::Particle2::~Particle2() {
}

// 生存するならture, 削除するならfalseを返す
bool chip::Particle2::Process() {
	// 位置の移動
	_x += _vx;
	_y += _vy;
	// カウンタを減らす
	_cnt--;
	// カウンタが0以下になったら削除
	if (_cnt <= 0) {
		return false;
	}
	return true;
}

void	chip::Particle2::SetColor(int r, int g, int b, int a) {
	_color_r = r;
	_color_g = g;
	_color_b = b;
	_color_a = a;
}

void chip::Particle2::Draw(MATRIX mView)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, _color_a);		// 加算描画指定
	SetDrawBright(_color_r, _color_g, _color_b);
	VECTOR world = VGet(_x, _y, 0);

	MyDrawTurnModiGraph(mView, world, 1.0f, 1.0f, _w, _h, _cg);	// (x,y)を中心位置として描画

	SetDrawBright(255, 255, 255);		// 色を戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定
}


bool chip::MapData::LoadChip(const std::string path) {
	if(_tiledMap == nullptr || _tiledMap->tilesets.size() == 0) {
		return false;
	}

	auto& tileset = _tiledMap->tilesets[0];

	// vector の数を指定する
	_cgChip.resize(tileset.tilecount);

	// マップチップの読み込み
	auto ret = LoadDivGraph((path + tileset.image).c_str(), // string から文字列に変換
		tileset.tilecount,
		tileset.columns,
		tileset.tilecount / tileset.columns,
		tileset.tilewidth,
		tileset.tileheight,
		_cgChip.data()); // vector からポインタに変換

	return (-1 != ret);
}

// マップ描画
void chip::MapData::Draw(MATRIX mView)
{
	if(_tiledMap == nullptr || _tiledMap->layers.size() == 0 || _tiledMap->tilesets.size() == 0) 
	{		
		return;
	}

	int x, y, layer, i;

	auto& layers = _tiledMap->layers[0];
	auto& tilesets = _tiledMap->tilesets[0];

	for(y = 0; y < layers.height; y++)
	{
		for(x = 0; x < layers.width; x++)
		{
			int chip_no = layers.data[y * layers.width + x];
			// .tmxのcsv形式は、透明を0とし、画像のチップは[1]から始まる。
			// そのため、全体的に数値を-1する。透明は-1となるので、if判定を追加
			if(chip_no > 0)
			{
				chip_no --;
			}
			//DrawGraph(pos_x, pos_y, _cgChip[chip_no], TRUE);
			VECTOR world = VGet(x * tilesets.tilewidth, y * tilesets.tileheight, 0);
			// 画像の中心をworld座標とするので、サイズ/2だけずらす
			world.x += 60 / 2;
			world.y += 60 / 2;
			MyDrawModiGraph(mView, world, 1.f, 0.f, 60, 60, _cgChip[chip_no]);
			//開発用
			//DrawFormatString(0 + 20 * x, 0 + 20 * y, GetColor(255, 255, 255), "%d", chip_no);
			//DrawFormatString(x * layers.width, y * MAPSIZE_H, GetColor(255, 255, 255), "%d", BlData.BlockHP);
			//	DrawFormatString(world.x, world.y, GetColor(255, 255, 255), "%d", data[y * layers.width + x].type);
		}
	}
	//エフェクト処理
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (ef[i].useEf != 0)
		{
			for (int use = 0; use < ef[i].useGraphNum;)
			{
				EffectAnm(i);
				DrawEffect(mView, i);
				if (EffectAnm(i) == ef[i].useGraphNum)
				{
					ef[i].useEf = 0;
				}
				use++;
			}
		}
	}
	DrawStar(mView);
	DeleteStar();
}


int chip::MapData::SetChip()
{
	if(_tiledMap == nullptr || _tiledMap->layers.size() == 0 || _tiledMap->tilesets.size() == 0) {
		return-1;
	}
	auto& layers = _tiledMap->layers[0];
	auto& tilesets = _tiledMap->tilesets[0];

	//チップのプロパティを設定
	for(int y = 0; y < layers.height; y++)
	{
		for(int x = 0; x < layers.width; x++)
		{
			auto& layers = _tiledMap->layers[0];
			Chip chip = { 0,0,0 };
			MapData::data.push_back(chip);
			MapData::data[y * layers.width + x].id = layers.data[y * layers.width + x];
			if(MapData::data[y * layers.width + x].id>0)
			{
				MapData::data[y * layers.width + x].id--;
			}

			if(MapData::data[y * layers.width + x].id == 1)//ノーマル
			{
				MapData::data[y * layers.width + x].hp = 10;//HP設定
				MapData::data[y * layers.width + x].type = 0;//タイプ設定
				
			}
			else if(MapData::data[y * layers.width + x].id == 2)//レンジ
			{
				MapData::data[y * layers.width + x].hp = 10;//HP設定
				
				MapData::data[y * layers.width + x].type = 1;//タイプ設定
			}
			else if(MapData::data[y * layers.width + x].id == 3)//冷蔵庫
			{
				MapData::data[y * layers.width + x].hp = 10;//HP設定
				
				MapData::data[y * layers.width + x].type = 2;//タイプ設定
			}
			else if(MapData::data[y * layers.width + x].id == 4)//ガラス
			{
				MapData::data[y * layers.width + x].hp = 10;//HP設定
				//MapData::data[y * layers.width + x].type = ARM_TYPE_NORMAL;//タイプ設定
				MapData::data[y * layers.width + x].type = 3;//タイプ設定
			}
			else if(MapData::data[y * layers.width + x].id == 5)//コンクリート
			{
				MapData::data[y * layers.width + x].hp = 10;//HP設定
				//MapData::data[y * layers.width + x].type = ARM_TYPE_NORMAL;//タイプ設定
				MapData::data[y * layers.width + x].type = 4;//タイプ設定
			}
			if(MapData::data[y * layers.width + x].id == 6)//草
			{
				MapData::data[y * layers.width + x].hp = 10;//HP設定
				//MapData::data[y * layers.width + x].type = ARM_TYPE_NORMAL;//タイプ設定
				MapData::data[y * layers.width + x].type = 5;//タイプ設定
			}
			//ステージブロック
			else if(MapData::data[y * layers.width + x].id == 10
				|| MapData::data[y * layers.width + x].id == 11
				|| MapData::data[y * layers.width + x].id == 12
				|| MapData::data[y * layers.width + x].id == 13 
				|| MapData::data[y * layers.width + x].id == 14
				|| MapData::data[y * layers.width + x].id == 15
				|| MapData::data[y * layers.width + x].id == 16
				|| MapData::data[y * layers.width + x].id == 17
				|| MapData::data[y * layers.width + x].id == 18
				|| MapData::data[y * layers.width + x].id == 20
				|| MapData::data[y * layers.width + x].id == 21
				|| MapData::data[y * layers.width + x].id == 22
				|| MapData::data[y * layers.width + x].id == 23  )
			{
				MapData::data[y * layers.width + x].hp = 100;//HP設定
				MapData::data[y * layers.width + x].type = 6;//タイプ設定
			}
		}
	}
	return 0;
}




// 指定のチップIDが当たり判定ありか？
int		chip::MapData::CheckHitChip(int chip_no)
{
	// 当たるIDかどうかをチェック
	int idtable[] =
	{
		1,2,3,4,5,6,
		10,11,12,13,14,15,16,17,18,
		20,21,22,23,
		-1		// 最後
	};
	int i = 0;
	while (idtable[i] != -1)
	{
		if (chip_no == idtable[i])
		{
			// 当たった
			return chip_no;
		}
		i++;
	}
	// 当たっていない
	return 0;
}



// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int chip::MapData::CheckHitMapChip(int x, int y)
{
	auto& layers = _tiledMap->layers[0];
	auto& tilesets = _tiledMap->tilesets[0];
	// マップチップ位置はマップデータからはみ出ているか？
	if (0 <= x && x < layers.width && 0 <= y && y < MAPSIZE_H)
	{	// はみでていない

		// マップチップIDが0以外は当たり判定を行う
		// 現在、レイヤーは考慮されていない
		int chip_no = layers.data[y * layers.width + x];
		if(chip_no>0)
		{
			chip_no--;
		}
		return CheckHitChip(chip_no);
	}

	// 当たっていない
	return 0;
}



// 指定のboxがmove_x,move_yに移動していた場合、マップチップに当たるか？
// boxはpixel単位
// move_x, move_yはpixel単位
chip::MapData::HITSLIDE chip::MapData::IsHitBox(int box_x, int box_y, int box_w, int box_h, int move_x, int move_y) 
{
	auto& layers = _tiledMap->layers[0];
	auto& tilesets = _tiledMap->tilesets[0];

	HITSLIDE hitSlide;
	hitSlide.hit = 0;
	hitSlide.slide_x = 0;
	hitSlide.slide_y = 0;

	int x, y;
	// 矩形を作成する
	int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
	l = box_x;
	t = box_y;
	r = box_x + box_w;
	b = box_y + box_h;

	// boxの左上座標～右下座標にあたるマップチップと、当たり判定を行う
	for (y = t / tilesets.tileheight; y <= b / tilesets.tileheight; y++)
	{
		for (x = l / tilesets.tilewidth; x <= r / tilesets.tilewidth; x++)
		{
			// (x,y)は、マップチップの座標（チップ単位）
			// この位置のチップは当たるか？
			int chip_no = CheckHitMapChip(x, y);
			//ChangeMapChip(chip_no);
			if (chip_no != 0)
			{	// このチップと当たった。
				
				// X,Yの移動方向を見て、その反対方向に補正する
				if (move_x < 0)
				{	// 左に動いていたので、右に補正
					hitSlide.slide_x = x * tilesets.tilewidth + tilesets.tilewidth - (box_x);
				}
				if (move_x > 0)
				{	// 右に動いていたので、左に補正
					hitSlide.slide_x = x * tilesets.tilewidth - 1 - (box_x + box_w);
				}
				if (move_y > 0)
				{	// 下に動いていたので、上に補正
					hitSlide.slide_y = y * tilesets.tileheight - 1 - (box_y + box_h);
				}
				if (move_y < 0)
				{	// 上に動いていたので、下に補正
					hitSlide.slide_y = y * tilesets.tileheight + tilesets.tileheight - (box_y);
				}
				// 当たったので戻る
				hitSlide.hit = 1;
				return hitSlide;
			}
		}
	}

	// 当たらなかった
	return hitSlide;
}

void chip::MapData::Process_Star(int i, int x, int y)
{
	int r = 0;
	for(int j = 0; j <= STAR_MAX; j++)
	{
		if(star[i][NULL].star_use != 0)
		{
			double s;
			s = (360 / STAR_MAX) + r;
			//星をキャラの真ん中へ
			star[i][j].pos.x = x + rand()%60-30;
			star[i][j].pos.y = y + rand()%60-30;
			star[i][j].direction += s * j;
		}
	}
}

//ブロック壊すのここ
int chip::MapData::HitChipDamage(int box_x, int box_y, int box_w, int box_h, int armPULv)
{
	auto& layers = _tiledMap->layers[0];
	auto& tilesets = _tiledMap->tilesets[0];

	int x, y;
	int ChipPos;
	int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
	l = box_x;
	t = box_y;
	r = box_x + box_w;
	b = box_y + box_h;


	for(y = t / tilesets.tileheight; y <= b / tilesets.tileheight; y++)
	{
		for(x = l / tilesets.tilewidth; x <= r / tilesets.tilewidth; x++)
		{

			if(x >= 0 && x < layers.width && y >= 0 && y < layers.height)
			{
				ChipPos = y * layers.width + x;
				DeleteChip(x, y, MapData::data[ChipPos].type, armPULv);
			}
		}
	}

	return 0;
}

//ブロック壊した後の処理
int chip::MapData::DeleteChip(int x, int y, int& data_type, int armPULv)
{
	auto& layers = _tiledMap->layers[0];
	auto& tilesets = _tiledMap->tilesets[0];
	int id = layers.data[y * layers.width + x];
	if(id>0)
	{
		id--;
	}
	if(id != 0)
	{
		if (data_type <= armPULv)
		{
			layers.data[y * layers.width + x] = 0;
			//音
			//岩
			if (id == 1)
			{
				PlaySoundMem(rock_se, DX_PLAYTYPE_BACK, TRUE);
				checkblock++;
			}
			//鉄
			if (id == 2)
			{
				PlaySoundMem(iron_se, DX_PLAYTYPE_BACK, TRUE);
				checkblock+=5;
			}
			//土
			if (id == 3)
			{
				PlaySoundMem(soil_se, DX_PLAYTYPE_BACK, TRUE);
				checkblock += 2;
			}
			//ガラス
			if (id == 4)
			{
				PlaySoundMem(glass_se, DX_PLAYTYPE_BACK, TRUE);
				checkblock += 5;
			}
			//コンクリ
			if (id == 5)
			{
				PlaySoundMem(concrete_se, DX_PLAYTYPE_BACK, TRUE);
				checkblock += 10;
			}
			//くさ
			if (id == 6)
			{
				PlaySoundMem(kusa_se, DX_PLAYTYPE_BACK, TRUE);
				checkblock += 2;
			}
			if (	
				   id == 10 || id == 11|| id == 12
				|| id == 13 || id == 14|| id == 15 
				|| id == 16 || id == 17|| id == 18
				|| id == 20 || id == 21|| id == 22 
				|| id == 23 )
			{
				PlaySoundMem(chip_se, DX_PLAYTYPE_BACK, TRUE);
				checkblock++;
			}
			cntBrokeBlock = checkblock;
			for(int i = 0; i < STAR_SPAWN_MAX; i++)
			{
				for(int j = 0; j < STAR_MAX; j++)
				{
					if(star[i][NULL].star_use != 1)
					{
						star[i][NULL].star_use = 1;
						star[i][j].x = x;
						star[i][j].y = y;
						int s_x = x * tilesets.tilewidth;
						int s_y = y * tilesets.tileheight;
						Process_Star(i, s_x, s_y);
						return i;
					}
				}
			}
		}
	}
	return 1;
}

void chip::MapData::DeleteStar()
{
	
	for(int i = 0; i < STAR_SPAWN_MAX; i++)
	{
		if(star[i][NULL].star_use != 0)
		{
			time[i]++;
			if(time[i] >= 40)
			{
				star[i][NULL].star_use = 0;
				time[i] = 0;
			}
		}
	}
}

void chip::MapData::DrawStar(MATRIX mView)
{
	for(int i = 0; i < STAR_SPAWN_MAX; i++)
	{
		for(int j = 0; j < STAR_MAX; j++)
		{
			if(star[i][NULL].star_use != 0)
				{
				//音
				if(CheckSoundMem(star_se) == 0)//再生中でないなら
				{
					PlaySoundMem(star_se, DX_PLAYTYPE_BACK, TRUE);
				}
				ChangeVolumeSoundMem(255, star_se);
					// まず現在の角度でベクトルを作る
				VECTOR vDir1 = VGet(0, 0, 0);
				float rad = DegToRad(star[i][j].direction);		// 角度をdegreeからradianに変換
				vDir1.x = cos(rad);
				vDir1.y = sin(rad);
				// 作ったベクトルを「単位ベクトル」（スカラが1のベクトル）にする
				VECTOR vUnit = VNorm(vDir1);
				// 単位ベクトルに移動速度をかけた、移動ベクトルを作る
				VECTOR vMove = VScale(vUnit, star[i][j].speed);
				// 移動ベクトルを位置に加算する
				star[i][j].pos = VAdd(star[i][j].pos, vMove);
				int color = rand() % 5;
				VECTOR world = VGet(star[i][j].pos.x, star[i][j].pos.y, 0);
				// 画像の中心をworld座標とするので、サイズ/2だけずらす
				world.x += 60 / 2;
				world.y += 60 / 2;

				MyDrawModiGraph(mView, world, 1.f, star[i][j].direction, 60, 60, _cgStar[color]);

				if(c_cnt>7){ c_cnt = 0; }
				else { c_cnt++; }

				if (c_cnt == 0) { r = 255; g = 0; b = 0; };
				if (c_cnt == 1) { r = 255; g = 165; b = 0; };
				if (c_cnt == 2) { r = 255; g = 255; b = 0; };
				if (c_cnt == 3) { r = 0; g = 128; b = 0; };
				if (c_cnt == 4) { r = 0; g = 255; b = 255; };
				if (c_cnt == 5) { r = 0; g = 0; b = 255; };
				if (c_cnt == 6) { r = 128; g = 0; b = 128; };

				for (int q = 0; q < 1; q++)
				{
					VECTOR pos = VGet(0, 0, 0);
					VECTOR vDir1 = VGet(0, 0, 0);
					float rad = DegToRad(star[i][j].direction + 180);		// 角度をdegreeからradianに変換
					vDir1.x = cos(rad);
					vDir1.y = sin(rad);
					// 作ったベクトルを「単位ベクトル」（スカラが1のベクトル）にする
					VECTOR vUnit = VNorm(vDir1);
					// 単位ベクトルに移動速度をかけた、移動ベクトルを作る
					VECTOR vMove = VScale(vUnit, 0);
					// 移動ベクトルを位置に加算する
					pos = VAdd(pos, vMove);

					VECTOR v = VGet(pos.x+rand()%10-5, pos.y+rand() % 10-5, 0);
					int w = rand() % 20 + 1; //int h = rand() % 50 + 1;
					chip::Particle2* p = new chip::Particle2(_cgParticle, world.x, world.y, v.x, v.y, 8, w, w);
					p->SetColor(r, g, b, rand()%300);
					_vParticles.push_back(p);
				}
			}
		}

	}
	// パーティクルの処理
	for (auto ite = _vParticles.begin(); ite != _vParticles.end();) {
		// パーティクルを処理
		if ((*ite)->Process() == true) {
			// まだ生存している
			ite++;
			}
		else {
			// パーティクルは終了した
			ite = _vParticles.erase(ite);
		}
		}
	// パーティクルの描画
	for (auto particle : _vParticles) {
		particle->Draw(mView);
	}
}


//エフェクト処理
int chip::MapData::AddEffect(int x, int y, int type)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (ef[i].type == EF_TYPE_NONE)
		{
			ef[i].x = x * CHIPSIZE_W;
			ef[i].y = y * CHIPSIZE_H;
			ef[i].useEf = 0;
			ef[i].type = type;
			switch (type)
			{
			case EF_TYPE_PURPLE:
				ef[i].useEf = 1;
				ef[i].time = 100;
				ef[i].useGraphNum = 10;
				ef[i].startGraphNum = 0;
				ef[i].cg = EF_SPARK_PURPLE;
				break;

			case EF_TYPE_GREEN:
				ef[i].useEf = 1;
				ef[i].time = 100;
				ef[i].useGraphNum = 10;
				ef[i].startGraphNum = 0;
				ef[i].cg = EF_SPARK_GREEN;
				break;

			case EF_TYPE_WHITE:
				ef[i].useEf = 1;
				ef[i].time = 100;
				ef[i].useGraphNum = 10;
				ef[i].startGraphNum = 0;
				ef[i].cg = EF_SPARK_WHITE;
				break;

			case EF_TYPE_RED:
				ef[i].useEf = 1;
				ef[i].time = 100;
				ef[i].useGraphNum = 10;
				ef[i].startGraphNum = 0;
				ef[i].cg = EF_SPARK_RED;
				break;

			case EF_TYPE_YELLOW:
				ef[i].useEf = 1;
				ef[i].time = 100;
				ef[i].useGraphNum = 10;
				ef[i].startGraphNum = 0;
				ef[i].cg = EF_SPARK_YELLOW;
				break;
			}
			return i;
			return type;
		}
	}
	return -1;
}

void chip::MapData::DeleteEffect(int i)
{
	ef[i].type = EF_TYPE_NONE;
}

int chip::MapData::EffectAnm(int i)
{
	int StartGraphNum = ef[i].startGraphNum;
	int UseGraphNum = ef[i].useGraphNum;
	int UseEffectTime = ef[i].time;

	int anmcnt = UseEffectTime;

	if (framecount > anmcnt)
	{
		if (StartGraphNum < UseGraphNum)
		{
			ef[i].startGraphNum++;
		}
		if (StartGraphNum >= UseGraphNum)
		{
			DeleteEffect(i);
		}
		framecount = 0;
	}
	framecount++;
	return 1;
}

//エッフェクト
void chip::MapData::DrawEffect(MATRIX mView, int i)
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

		//火花紫
		if (eftype == EF_TYPE_PURPLE)
		{
			ef[i].cg = EF_SPARK_PURPLE + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 1.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//火花緑
		else if (eftype == EF_TYPE_GREEN)
		{
			ef[i].cg = EF_SPARK_GREEN + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 1.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//火花白
		else if (eftype == EF_TYPE_WHITE)
		{
			ef[i].cg = EF_SPARK_WHITE + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 1.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//火花赤
		else if (eftype == EF_TYPE_RED)
		{
			ef[i].cg = EF_SPARK_RED + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 1.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//火花黄
		else if (eftype == EF_TYPE_YELLOW)
		{
			ef[i].cg = EF_SPARK_YELLOW + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 1.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		EffectAnm(i);
	}
}