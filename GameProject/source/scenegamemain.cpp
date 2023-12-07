#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "mymath.h"
#include "mydraw.h"
#include "SceneGameMain.h"
#include "SceneGameOver.h"
#include "scenegameresult.h"
#include "mapdata.h"
#include "Map.h"
#include "map_create.h"
#include "scenebase.h"
UI* ui;
SceneGameMain::SceneGameMain() {
	
	int stage = gStageNum;
	//gStageNum = stage;
	ui = new UI;
	//背景
	if(stage < 3)
	{
		_cgBg = LoadGraph("res/BG/City.png");
	}
	else
	{
		_cgBg = LoadGraph("res/BG/Lab.png");
	}

	mapData = new chip::MapData();
	const auto path = _T("map/");//パス
	auto json = _T("map_1_ex.json");//マップファイル

	//jsonマップ読み取り
	if(stage == 1)
	{
		json = _T("map_1_ex.json");//マップファイル
	}
	else if (stage == 2)
	{
		json = _T("map_2.json");//マップファイル
	}
	else if (stage == 3)
	{
		json = _T("map_3.json");//マップファイル
	}
	else if (stage == 4)
	{
		json = _T("bossmap.json");//マップファイル
	}
	
	tiled::TiledMap* tiledMap = tiled::In(path, json);
	mapData->SetMap(tiledMap);

	if (!mapData->LoadChip(path))
	{
		// ロード失敗
		delete mapData;
	}

	// キャラデータの初期設定
	for (int i = 0; i < CHARA_MAX; i++)
	{
		_gChara[i].type = CHARA_TYPE_NONE;		// いったん、全キャラをnoneに
	}
	//キャラデータをtiledMapのobjectから設定
	for (auto& obj : tiledMap->objects) {
		//このif文の形でAddCharaすること。
		if (obj.className == "rennji") {
			AddChara(CHARA_TYPE_ENEMY_RENJI, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "senntakuki") {
			AddChara(CHARA_TYPE_ENEMY_WASH, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "terebi") {
			AddChara(CHARA_TYPE_ENEMY_TV, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "reizouko") {
			AddChara(CHARA_TYPE_ENEMY_FREEZER, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "sennpuuki") {
			AddChara(CHARA_TYPE_ENEMY_FUN, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "jihannki") {
			AddChara(CHARA_TYPE_VENDING, obj.x, obj.y, obj.arrow,obj.putItem);
		}
		if (obj.className == "tatiiri") {
			AddChara(CHARA_TYPE_SIGNBOARD1, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "kowasuna") {
			AddChara(CHARA_TYPE_SIGNBOARD2, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "yajirusi") {
			AddChara(CHARA_TYPE_SIGNBOARD_ARROW, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "tomare") {
			AddChara(CHARA_TYPE_SIGN1, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "kowase") {
			AddChara(CHARA_TYPE_SIGN2, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "tyuukinn") {
			AddChara(CHARA_TYPE_SIGN3, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "ki") {
			AddChara(CHARA_TYPE_TREE, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "tekotu") {
			AddChara(CHARA_TYPE_PILLAR1, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "tekotutu") {
			AddChara(CHARA_TYPE_PILLAR2, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "hasira") {
			AddChara(CHARA_TYPE_PILLAR3, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "poddo") {
			AddChara(CHARA_TYPE_POD1, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "hibipoddo") {
			AddChara(CHARA_TYPE_POD2, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "goal") {
			AddChara(CHARA_TYPE_DOOR, obj.x, obj.y, obj.arrow,0);
		}
		if (obj.className == "battery") {
			AddChara(CHARA_TYPE_BATTERY, obj.x, obj.y, obj.arrow, 0);
		}
		if (obj.className == "boss") {
			AddChara(CHARA_TYPE_ENEMY_BOSS, obj.x, obj.y, obj.arrow,0);
		}
	}

	if (stage == 4)
	{
		_cam._scale = 0.5f;

		AddChara(CHARA_TYPE_ARM_L, 0, 0, -1, 0);

		AddChara(CHARA_TYPE_PLAYER1, 28200, 880, 1, 0);

		AddChara(CHARA_TYPE_ARM_R, 0, 0, -1, 0);



	}
	else {
		AddChara(CHARA_TYPE_ARM_L, 0, 0, -1, 0);

		AddChara(CHARA_TYPE_PLAYER1, 360, 1620, 1, 0);

		AddChara(CHARA_TYPE_ARM_R, 0, 0, -1, 0);
	}


	mapData->SetChip();//プロパティを設定

	LoadCharaData();//キャラクタデータロード

	// カメラのリミット設定
	auto& layers = tiledMap->layers[0];
	_cam._rcLimit.x = 0;
	_cam._rcLimit.y = 0;
	_cam._rcLimit.w = layers.width * 60;
	_cam._rcLimit.h = layers.height * 60;


	//use_arm = 0;
	//星初期化
	for(int i = 0; i < STAR_MAX; i++) {
		star[i].direction = 0;
		star[i].pos.x = 0;
		star[i].pos.y = 0;
		star[i].pos.z = 0;
		star[i].speed = 10;
		if(i <= 10)
		{
			star[i].star_use = 1;
		}
		else
		{
			star[i].star_use = 0;
		}
	}
	
	pl_x = 0;//腕追従用
	pl_y = 0;//腕追従用
	pl_arrow = 0;//腕追従用

	//敵の座標代入用
	rennji_x = 0;
	rennji_y = 0;
	freeze_x = 0;
	freeze_y = 0;
	tv_x = 0;
	tv_y = 0;
	wash_x = 0;
	wash_y = 0;
	fun_x = 0;
	fun_y = 0;
	boss_x = 0;

	checkdistance = 0;

	Energy = 0;
	UseEnergy = 0;

	_cgParticle = LoadGraph("res/EF/stardot.gif");
	_vParticles.clear();
	
	//デバッグ用
	armtype = 0;

	// カラーマスクのリセット
	//ColorMask(0, 0, 0, 0);
	ColorFadeIn(60);		// フェードインに変更
	PlaySoundMem(_se[SE_SYSTEM_START], DX_PLAYTYPE_NORMAL, TRUE);

	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP, TRUE);

}

SceneGameMain::~SceneGameMain()
{
	delete mapData;
	ui -> ~UI();
	DeleteGraph(_cgBg);
	for (int i = 0; i < _PT_CHARA_ALLNUM_; i++) 
	{
		if (_cgChara[i] != -1)
		{
			DeleteGraph(_cgChara[i]);
		}
	}
	for (int i = 0; i < _SE_ALL_; i++)
	{
		if (_se[i] != -1)
		{
			DeleteSoundMem(_se[i]);
		}
	}
	DeleteSoundMem(_bgm);
}

void SceneGameMain::Input() {
	// 何もしない
}


// パーティクル
Particle::Particle(int cg, float x, float y, float vx, float vy, int cnt,int w,int h) {
	_cg = cg;
	_w = w;
	_h = h;

	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_cnt = cnt;
}

Particle::~Particle() {
}

// 生存するならture, 削除するならfalseを返す
bool Particle::Process() {
	// 位置の移動
	_x += _vx;
	_y += _vy;
	// カウンタを減らす
	_cnt--;
	// カウンタが0以下になったら削除
	if(_cnt <= 0) {
		return false;
	}
	return true;
}

void	Particle::SetColor(int r, int g, int b, int a) {
	_color_r = r;
	_color_g = g;
	_color_b = b;
	_color_a = a;
}

void Particle::Draw(MATRIX mView)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, _color_a);		// 加算描画指定
	SetDrawBright(_color_r, _color_g, _color_b);
	VECTOR world = VGet(_x, _y, 0);

	MyDrawTurnModiGraph(mView, world, 1.0f, 1.0f, _w, _h, _cg);	// (x,y)を中心位置として描画

	SetDrawBright(255, 255, 255);		// 色を戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定
}


void SceneGameMain::Process()
{
	//エネルギーを使うかどうか
	//0：使わない、1：使う
	//UseEnergy = 0;

	for (int j = 0; j < ARM_MAX; j++)
	{
		ChangeArmType(j);
	}
	if(pause == 0) 
	{

		int i;
		for(i = 0; i < CHARA_MAX; i++)
		{
			if(_gChara[i].type != CHARA_TYPE_NONE)
			{
				if(_gChara[i].HP <= 0)
				{
					//_gChara[i].useChara = 0;
					/*_gChara[i].hx = 0;
					_gChara[i].hy = 0;
					_gChara[i].hw = 0;
					_gChara[i].hh = 0;*/
				}
				if(_gChara[i].useChara == 1) {
					//
					// 共通処理（前）
					//

					int motChg = -1;		// モーションを変更する場合、ここに指定する

					// 重力処理
					if(_gChara[i].useGravity == 1) {
						_gChara[i].gravity += 1;			// キャラの、重力による加速値を大きくする
						_gChara[i].y += _gChara[i].gravity;	// 重力による加速値の分だけ移動する
						_gChara[i].stand = 0;			// 床に当たってないことを前提に、床フラグリセット
					}

					// 上下の当たり判定
					if (_gChara[i].group != CHARA_GROUP_OBJECT) {

						if (CheckCharaMove(i, 0, _gChara[i].gravity) != 0)
						{
							// 当たった。当たったのは床か？（重力値はプラスだったか？）
							if (_gChara[i].gravity > 0)
							{
								_gChara[i].stand = 1;	// 床に当たったのでフラグセット
							}
							_gChara[i].gravity = 0;		// 重力による加速値をリセット
						}
					}
					else if (_gChara[i].DamegeFase == 0) {

						if (CheckCharaMove(i, 0, _gChara[i].gravity) != 0)
						{
							// 当たった。当たったのは床か？（重力値はプラスだったか？）
							if (_gChara[i].gravity > 0)
							{
								_gChara[i].stand = 1;	// 床に当たったのでフラグセット
							}
							_gChara[i].gravity = 0;		// 重力による加速値をリセット
						}
					}

					//
					// タイプ別個別処理
					//
						switch(_gChara[i].group)
						{
							case CHARA_GROUP_PLAYER:
							{	// プレイヤ-
								motChg = CharaPlayerProcess(i);
								break;
							}
							case CHARA_GROUP_ENEMY:
							{
								motChg = CharaEnemyProcess(i);
								break;
							}
							case CHARA_GROUP_OBJECT:
							{
								motChg = CharaObjectProcess(i);
							}
						}

						switch(_gChara[i].type)
						{
						case CHARA_TYPE_ARM_L:
						{
							motChg = CharaArmProcessB(i, 0);
							break;
						}
						case CHARA_TYPE_ARM_R:
						{
							motChg = CharaArmProcessF(i, 1);
							 
							break;
						}
						}
		
					//
					// 共通処理（後）
					//

					for(int i = 0; i < CHARA_MAX; i++)
					{
					int frameId = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);

						HitChipFromFrame(frameId, i);
					}

					// 当たり判定
					int j;
					// 自分がダメージを受けるかの判定を行う
					for(j = 0; j < CHARA_MAX; j++)
					{
						// 自キャラじゃない、かつキャラタイプがある
						if(i != j && _gChara[j].type != CHARA_TYPE_NONE)
						{
							if(_gChara[i].type == CHARA_TYPE_PLAYER1 && _gChara[j].type == CHARA_TYPE_ARM_L)
							{
								continue;
							}
							if(_gChara[i].type == CHARA_TYPE_PLAYER1 && _gChara[j].type == CHARA_TYPE_ARM_R)
							{
								continue;
							}
							//とりまおき
							if(_gChara[i].group == CHARA_GROUP_OBJECT && _gChara[j].group == CHARA_GROUP_BULLET)
							{
								continue;
							}
							if (_gChara[i].group == CHARA_GROUP_OBJECT && _gChara[j].group == CHARA_GROUP_ENEMY)
							{
								continue;
							}
							if(_gChara[j].group == _gChara[i].group)
							{
								continue;
							}
							//ここまで
							if(_gChara[i].type == _gChara[j].type)
							{
								continue;
							}

							// [i]と[j]で当たり判定
							// [i]（自分）の持つダメージ判定と、[j]（相手）の持つ攻撃判定との当たり判定。
							int ii, jj;

							for(ii = 0; ii < CHARA_HITRECT_NUM; ii++)
							{
								int frameId_i = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);

								for(jj = 0; jj < CHARA_HITRECT_NUM; jj++)
								{
									if (_gChara[i].HP >= 0 && _gChara[j].HP >= 0)
									{
										int frameId_j = SearchFrame(tblMotion[_gChara[j].motId].item[_gChara[j].motcnt].frameId);
										if (tblFrame[frameId_i].hit[ii].type == CHARA_HITRECT_TYPE_DAMAGE
											&& tblFrame[frameId_j].hit[jj].type == CHARA_HITRECT_TYPE_ATTACK
											)
										{	// [i]のダメージ判定, [j]の攻撃判定が見つかった
											// 二つの当たり判定矩形を取り出す
											MYRECT rc_i = GetHitRectFromFrame(frameId_i, ii, _gChara[i].x, _gChara[i].y, tblMotion[_gChara[i].motId].mirror_lr);
											MYRECT rc_j = GetHitRectFromFrame(frameId_j, jj, _gChara[j].x, _gChara[j].y, tblMotion[_gChara[j].motId].mirror_lr);



											// RECTの当たり判定
											if (IsHitBox(rc_i.x, rc_i.y, rc_i.w, rc_i.h,
												rc_j.x, rc_j.y, rc_j.w, rc_j.h) == 1
												) {
												// 当たった。自分はダメージを食らう
												// ダメージの方向は、相手のX座標から判断
												if (_gChara[i].x > _gChara[j].x)
												{
													// 相手が左側に居るので、自分も左側を向く
													_gChara[i].arrow = -1;
													_gChara[i].HP -= _gChara[j].Pow;
												}
												else {
													// 相手が右側に居るので、自分も右側を向く
													_gChara[i].arrow = 1;
													_gChara[i].HP -= _gChara[j].Pow;
												}

												if (_gChara[i].arrow < 0)
												{
													if (_gChara[i].type == CHARA_TYPE_PLAYER1)
													{
														motChg = MOTION_L_DAMAGE;
													}
													if (_gChara[i].type == CHARA_TYPE_ENEMY_RENJI)
													{
														motChg = MOTION_RENJI_L_DAMAGE;
													}
												}
												else
												{
													if (_gChara[i].type == CHARA_TYPE_PLAYER1)
													{
														motChg = MOTION_R_DAMAGE;
													}
													if (_gChara[i].type == CHARA_TYPE_ENEMY_RENJI)
													{
														motChg = MOTION_RENJI_R_DAMAGE;
													}
												}
												if (_gChara[i].type == CHARA_TYPE_ENEMY_FUN) {

													_gChara[i].CheckAttack = 1;
												}
												// ダメージSE
												//　音
												if(_gChara[i].type == CHARA_TYPE_PLAYER1) 
												{
													PlaySoundMem(_se[VOICE_PLAYER_DAMAGE], DX_PLAYTYPE_BACK, TRUE);
												}
												else
												{
													PlaySoundMem(_se[SE_DAMAGE], DX_PLAYTYPE_BACK, TRUE);
												}
												if (_gChara[j].type == CHARA_TYPE_FREEZER_BULLET)
												{
													DeleteChara(j);
												}
											}
										}
									}


									if (_gChara[i].type == CHARA_TYPE_PLAYER1 && _gChara[j].core != 0)
									{
										int frameId_j = SearchFrame(tblMotion[_gChara[j].motId].item[_gChara[j].motcnt].frameId);
										if (tblFrame[frameId_i].hit[ii].type == CHARA_HITRECT_TYPE_PLAYER
											&& tblFrame[frameId_j].hit[jj].type == CHARA_HITRECT_TYPE_CORE)
											{
												// [i]のダメージ判定, [j]の攻撃判定が見つかった
												// 二つの当たり判定矩形を取り出す
												MYRECT rc_i = GetHitRectFromFrame(frameId_i, ii, _gChara[i].x, _gChara[i].y, tblMotion[_gChara[i].motId].mirror_lr);
												MYRECT rc_j = GetHitRectFromFrame(frameId_j, jj, _gChara[j].x, _gChara[j].y, tblMotion[_gChara[j].motId].mirror_lr);

												// RECTの当たり判定
												if (IsHitBox
												(rc_i.x, rc_i.y, rc_i.w, rc_i.h,
												rc_j.x, rc_j.y, rc_j.w, rc_j.h) == 1)
												{
													for(int k = 0; k < ARM_MAX; k++)
													{
														if (arm[k].ArmPULv <= _gChara[j].core) {
															arm[k].ArmPULv = _gChara[j].core;
														}
													}
													PlaySoundMem(_se[SE_POWERUP], DX_PLAYTYPE_BACK, TRUE);
													DeleteChara(j);
												}
										}
									}
								}
							}
						}
					}

					// モーションは変更されないか？
					if(motChg == -1 || motChg == _gChara[i].motId)
					{
						// モーション分移動
						// mx,myに移動値を得る
						int mx, my;
						mx = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].mx;
						my = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].my;

						// 移動してみる
						_gChara[i].x += mx;
						_gChara[i].y += my;

						// 移動可能か？当たり判定。移動不可なら中で位置調整
						CheckCharaMove(i, mx, my);

						// 今のモーションのままなので、カウンタを進める
						_gChara[i].animcnt++;

						// モーションの今のフレームは終了したか？
						if(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt <= _gChara[i].animcnt)
						{
							// 次のフレームへ
							_gChara[i].motcnt++;
							_gChara[i].animcnt = 0;

							// 次のフレームはコマンドか？
							// コマンドが複数連続で処理できるように、ループをさせておく
							int loop = 1;
							while(loop == 1)
							{
								// コマンド分岐
								switch(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId)
								{
								case CHARA_MOTION_CMD_LOOP:
								{	// モーションをループする(frameCntにモーションindex指定)
									int motionIndex = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
									_gChara[i].motcnt = motionIndex;
									break;
								}
								case CHARA_MOTION_CMD_MOTION:
								{	// 別のモーションへ(frameCntはモーションID)
									int motionId = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
									CharaChangeMotion(i, motionId);
									loop = 0;	// ループ終了
									break;
								}
								case CHARA_MOTION_CMD_PLAYSE:
								{	// 効果音再生(frameCntにSE_xxxx)
									int seId = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
									PlaySoundMem(_se[seId], DX_PLAYTYPE_BACK, TRUE);
									_gChara[i].motcnt++;
									break;
								}
								case CHARA_MOTION_CMD_HPCHECK:
								{	// HPをチェックし0以下なら死亡
									if(_gChara[i].HP <= 0)
									{
										//DeleteChara(i);
										int x, y;
										x = _gChara[i].x - (_cam._pos.x - _cam._lookat.x);
										y = _gChara[i].y - (_cam._pos.y - _cam._lookat.y);

										for(int i = 0; i < STAR_MAX; i++) 
										{
											if(star[i].star_use != 0)
											{
												star[i].checkStar = 1;
												Process_Star(i, x, y);
											}
										}
										if (_gChara[i].DamegeFase == 0) {
											_gChara[i].DamegeFase = 1;
										}
									}
									_gChara[i].motcnt++;
									break;
								}
								case CHARA_MOTION_CMD_DELET:
								{
									DeleteChara(i);
								}
								case CHARA_MOTION_CMD_EFFECT:
								{
									
								}
								/*
								case CHARA_MOTION_CMD_xxx:
								{
								// コマンドを追加する場合は、コマンドを処理したらmotcnt++する
									_gChara[i].motcnt++;
									break;
								}
								*/
								default:
								{	// コマンドじゃなかったのでループ終了
									loop = 0;
								}
								}
							}
						}
					}
					// モーションは変更されるか？
					if(motChg != -1 && motChg != _gChara[i].motId)
					{
						// 今と別のモーションに変更
						CharaChangeMotion(i, motChg);
					}
				}
			}
		}

		// カメラ位置をCHARA_TYPE_PLAYER1の位置にする
		for(i = 0; i < CHARA_MAX; i++)
		{
			if(_gChara[i].type == CHARA_TYPE_PLAYER1) {
				_cam._pos = VGet(_gChara[i].x, _gChara[i].y, 0);
			}
		}

		// カメラ処理を呼ぶ
		_cam.Process();

		//タイマーの処理
		int over = ui -> Process();
		if(over != 0)
		{
			SceneBase* scene = new SceneGameOver;
			ChangeScene(scene);
		}
	}
}


void SceneGameMain::Draw()
{
	int i, j, x, y;

	// カメラのView行列で、画面上の座標を計算（View座標）
	MATRIX	mView = _cam.GetViewMatrix();

	// 背景
	DrawGraphF(0.0f - BGMoveX(), -900.0f, _cgBg, TRUE);

	// マップ描画
	mapData->Draw(mView);

	//ポーズ
	if(pause == 1)
	{
		DrawGraph(0, 0, _cgPause, TRUE);
	}

	// キャラ描画
		// まずはlayerを参考に描画順を作る
	int drawCharaIndex[CHARA_MAX];
	for(i = 0; i < CHARA_MAX; i++)
	{
		drawCharaIndex[i] = i;
	}
	// layer順に並び変え
	for(i = 0; i < CHARA_MAX; i++)
	{
		for(j = i + 1; j < CHARA_MAX; j++) {
			if(_gChara[drawCharaIndex[i]].layer > _gChara[drawCharaIndex[j]].layer) {
				int tmp = drawCharaIndex[i];
				drawCharaIndex[i] = drawCharaIndex[j];
				drawCharaIndex[j] = tmp;
			}
		}
	}

	for(j = 0; j < CHARA_MAX; j++)
	{
		i = drawCharaIndex[j];
		//DrawFormatString(1, 1, GetColor(255, 255, 255), "x=%d,y=%d,dir=%d",pl_x,pl_y,pl_arrow);
		//DrawFormatString(1, 10, GetColor(255, 255, 255), "armtype=%d,PL_Stand=%d,PL_grv=%d", armtype, pl_stand, pl_gravity);
		if(_gChara[i].type != CHARA_TYPE_NONE)
		{
			if(_gChara[i].HP <= 0)
			{
				//_gChara[i].useChara = 0;
			}
			if(_gChara[i].useChara == 1)
			{

				// キャラのモーションフレームから情報を得る
				int frameId = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);
				int cgId = tblFrame[frameId].cgId;
				// 左右反転するか？
				if(tblMotion[_gChara[i].motId].mirror_lr == 0)
				{
					// しない
					// 描画位置は、基点分ずらした場所
					x = _gChara[i].x - tblFrame[frameId].cx;
					y = _gChara[i].y - tblFrame[frameId].cy;
					// ※このx,yはDrawGraph()用に画像の左上なので、MyDrawModiGraph()の中心位置には合わない

					VECTOR world = VGet(x, y, 0);
					// 画像の中心をworld座標とするので、サイズ/2だけずらす
					world.x += tblFrame[frameId].w / 2;
					world.y += tblFrame[frameId].h / 2;
					
					//キャラの描画
					MyDrawModiGraph(mView, world, 1.f, tblFrame[frameId].angle, tblFrame[frameId].w, tblFrame[frameId].h, _cgChara[cgId]);
					//MyDrawModiGraph(/*場所*/ world, /*角度*/ tblFrame[frameId].angle,/*ハンドル*/ _cgChara[cgId]);
					if(_gChara[i].type == CHARA_TYPE_ARM_R || _gChara[i].type == CHARA_TYPE_ARM_L)
					{
						for(int j = 0; j < ARM_MAX; j++)
						{
							if(arm[j].ArmType == ARM_TYPE_RENJI)
							{
								MyDrawModiGraph(mView, world, 1.f, tblFrame[frameId].angle, 200, 200, _cgGuard);
							}
						}
					}
					if(pause == 1)
					{
						if(_gChara[i].type == CHARA_TYPE_PLAYER1)
						{
							MyDrawModiGraph(mView, world, 1.f, tblFrame[frameId].angle, 200, 200, _cgSelect);
						}
					}
				}
				else
				{
					// する
					// 描画位置は、左右反転してから基点分ずらした場所
					x = _gChara[i].x - (tblFrame[frameId].w - tblFrame[frameId].cx);
					y = _gChara[i].y - tblFrame[frameId].cy;
					// ※このx,yはDrawGraph()用に画像の左上なので、MyDrawModiGraph()の中心位置には合わない

					VECTOR world = VGet(x, y, 0);
					// 画像の中心をworld座標とするので、サイズ/2だけずらす
					world.x += tblFrame[frameId].w / 2;
					world.y += tblFrame[frameId].h / 2;
					MyDrawTurnModiGraph(mView, world, 1.f, tblFrame[frameId].angle, tblFrame[frameId].w, tblFrame[frameId].h, _cgChara[cgId]);
					if(_gChara[i].type == CHARA_TYPE_ARM_R || _gChara[i].type == CHARA_TYPE_ARM_L)
					{
						for(int j = 0; j < ARM_MAX; j++)
						{
							if(arm[j].ArmType == ARM_TYPE_RENJI)
							{
								MyDrawModiGraph(mView, world, 1.f, tblFrame[frameId].angle, 200, 200, _cgGuard);
							}
						}
					}
					if(pause == 1)
					{
						if(_gChara[i].type == CHARA_TYPE_PLAYER1)
						{
							MyDrawModiGraph(mView, world, 1.f, 0.f, 200, 200, _cgSelect);
						}
					}
				}
				//コメント
				if (_gChara[i].type == CHARA_TYPE_ARM_L) {
					DrawFormatString(1, 20 * 1, GetColor(255, 255, 255), "LmotId = %d", _gChara[i].motId);
					DrawFormatString(1, 20 * 2, GetColor(255, 255, 255), "Larrow = %d", _gChara[i].arrow);
				}
				if (_gChara[i].type == CHARA_TYPE_ARM_R) {
					DrawFormatString(1, 20 * 10, GetColor(255, 255, 255), "RmotId = %d", _gChara[i].motId);
					DrawFormatString(1, 20 * 11, GetColor(255, 255, 255), "Rarrow = %d", _gChara[i].arrow);
				} 
				DrawFormatString(1, 20 * 15, GetColor(255, 255, 255), "Energy = %d", Energy);
				DrawFormatString(1, 20 * 16, GetColor(255, 255, 255), "UseEnergy = %d", UseEnergy);
				DrawFormatString(1, 20 * 17, GetColor(255, 255, 255), "pl_stand = %d", pl_stand);
			}

			if(_gChara[i].type == CHARA_TYPE_ARM_R || _gChara[i].type == CHARA_TYPE_ARM_L)
			{
				int frameId = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);
				// 描画位置は、基点分ずらした場所
				x = _gChara[i].x - tblFrame[frameId].cx;
				y = _gChara[i].y - tblFrame[frameId].cy;
				// ※このx,yはDrawGraph()用に画像の左上なので、MyDrawModiGraph()の中心位置には合わない

				if (frameId == 365 || frameId == 363)
				{
					x -= 75;
					y += 100;
				}
				if(frameId == 364 || frameId == 366)
				{
					x += 75;
					y += 100;
				}
				VECTOR world = VGet(x, y, 0);
				// 画像の中心をworld座標とするので、サイズ/2だけずらす
				world.x += tblFrame[frameId].w / 2;
				world.y += tblFrame[frameId].h / 2;

				
				//色を生成
				if (_gChara[i].type == CHARA_TYPE_ARM_R)
				{
					//色を生成
					if (arm[1].ArmPULv == 0) { r = 0;  g = 0;  b = 0; }
					if (arm[1].ArmPULv == 1) { r = 256;  g = 0;  b = 0; }
					if (arm[1].ArmPULv == 2) { r = 0;  g = 0;  b = 256; }
					if (arm[1].ArmPULv == 3) { r = 256;  g = 0;  b = 256; }
					if (arm[1].ArmPULv == 4) { r = 0;  g = 256;  b = 256; }
					if (arm[1].ArmPULv == 5) { r = 0;  g = 256; b = 0; }
					if (arm[1].ArmPULv == 6) { r = rand() % 256;  g = rand() % 256;  b = rand() % 256; }
				}
				if (_gChara[i].type == CHARA_TYPE_ARM_L)
				{
					if (arm[1].ArmPULv == 0) { r = 0;  g = 0;  b = 0; }
					if (arm[1].ArmPULv == 1) { r = 256;  g = 0;  b = 0; }
					if (arm[1].ArmPULv == 2) { r = 0;  g = 0;  b = 256; }
					if (arm[1].ArmPULv == 3) { r = 256;  g = 0;  b = 256; }
					if (arm[1].ArmPULv == 4) { r = 0;  g = 256;  b = 256; }
					if (arm[1].ArmPULv == 5) { r = 0;  g = 256; b = 0; }
					if (arm[1].ArmPULv == 6) { r = rand() % 256;  g = rand() % 256;  b = rand() % 256; }
				}

				for(int q = 0; q < 24; q++)
				{
					if (frameId == 365 || frameId == 363)
					{
						 r = rand() %100;  g = rand() % 255;  b = 256;
						VECTOR pos = VGet(0, 0, 0);
						VECTOR vDir1 = VGet(0, 0, 0);
						float rad = DegToRad(120+rand()%30-15);		// 角度をdegreeからradianに変換
						vDir1.x = cos(rad);
						vDir1.y = sin(rad);
						// 作ったベクトルを「単位ベクトル」（スカラが1のベクトル）にする
						VECTOR vUnit = VNorm(vDir1);
						// 単位ベクトルに移動速度をかけた、移動ベクトルを作る
						VECTOR vMove = VScale(vUnit, 10);
						// 移動ベクトルを位置に加算する
						pos = VAdd(pos, vMove);

						VECTOR v = VGet(pos.x, pos.y, 0);
						int w = rand() % 20 + 1; int h = rand() % 50 + 1;
						Particle* p = new Particle(_cgParticle, world.x, world.y, v.x, v.y, 15, w, w);
						p->SetColor(r, g, b, 300);
						_vParticles.push_back(p);
					}
					else if (frameId == 364 || frameId == 366)
					{
						r = rand() % 100;  g = rand() % 255;  b = 256;

						VECTOR pos = VGet(0, 0, 0);
						VECTOR vDir1 = VGet(0, 0, 0);
						float rad = DegToRad(50 + rand() % 30 - 15);		// 角度をdegreeからradianに変換
						vDir1.x = cos(rad);
						vDir1.y = sin(rad);
						// 作ったベクトルを「単位ベクトル」（スカラが1のベクトル）にする
						VECTOR vUnit = VNorm(vDir1);
						// 単位ベクトルに移動速度をかけた、移動ベクトルを作る
						VECTOR vMove = VScale(vUnit, 10);
						// 移動ベクトルを位置に加算する
						pos = VAdd(pos, vMove);

						VECTOR v = VGet(pos.x, pos.y, 0);
						int w = rand() % 20 + 1; int h = rand() % 50 + 1;

						Particle* p = new Particle(_cgParticle, world.x, world.y, v.x, v.y, 15, w, w);
						p->SetColor(r, g, b, 300);
						_vParticles.push_back(p);
					}
					else {
						VECTOR pos = VGet(0, 0, 0);
						VECTOR vDir1 = VGet(0, 0, 0);
						float rad = DegToRad(rand() % 360);		// 角度をdegreeからradianに変換
						vDir1.x = cos(rad);
						vDir1.y = sin(rad);
						// 作ったベクトルを「単位ベクトル」（スカラが1のベクトル）にする
						VECTOR vUnit = VNorm(vDir1);
						// 単位ベクトルに移動速度をかけた、移動ベクトルを作る
						VECTOR vMove = VScale(vUnit, 10);
						// 移動ベクトルを位置に加算する
						pos = VAdd(pos, vMove);

						VECTOR v = VGet(pos.x, pos.y, 0);

						int w = rand() % 20 + 1; int h = rand() % 50 + 1;
						Particle* p = new Particle(_cgParticle, world.x, world.y, v.x, v.y, 15, w, w);
						p->SetColor(r, g, b, 300);
						_vParticles.push_back(p);

					}
				}
				// パーティクルの処理
				for(auto ite = _vParticles.begin(); ite != _vParticles.end();) {
					// パーティクルを処理
					if((*ite)->Process() == true) {
						// まだ生存している
						ite++;
					}
					else {
						// パーティクルは終了した
						ite = _vParticles.erase(ite);
					}
				}

				// パーティクルの描画
				for(auto particle : _vParticles) 
				{
					particle->Draw(mView);
				}

			}
			if (_gChara[i].type == CHARA_TYPE_PLAYER1)
			{
				ui->Draw(_gChara[i].HP);
			}
		}
	}

	//エフェクト
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
	if(_debugViewCollision != 0)
	{
		// 開発用：当たり判定描画(地形/キャラ側)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		// 半透明描画指定
		{
			for(i = 0; i < CHARA_MAX; i++)
			{
				if(_gChara[i].type != CHARA_TYPE_NONE)
				{
					// キャラの当たり判定を取り出す
					MYRECT rc = GetHitRectFromChara(i);

					// 矩形描画
					MyDrawBox(mView, rc.x, rc.y, rc.x + rc.w, rc.y + rc.h, GetColor(0, 255, 0), TRUE);
				}
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定

		// 開発用：当たり判定描画(モーション側)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		// 半透明描画指定
		{
			// 当たり判定色テーブル
			int tblColor[] =
			{
				0,		// CHARA_HITRECT_TYPE_NONE
				GetColor(0,0,0),		// CHARA_HITRECT_TYPE_ATTACK	1
				GetColor(0,0,255),		// CHARA_HITRECT_TYPE_DAMAGE	2
				GetColor(255,0,0),		//
			};

			for(i = 0; i < CHARA_MAX; i++)
			{
				if(_gChara[i].type != CHARA_TYPE_NONE)
				{
					// キャラのモーションフレームから情報を得る
					int frameId = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);
					// 当たり判定の数分ループ
					int ii;
					for(ii = 0; ii < CHARA_HITRECT_NUM; ii++)
					{
						int type = tblFrame[frameId].hit[ii].type;
						if(type != CHARA_HITRECT_TYPE_NONE)
						{
							// 当たり判定矩形を取り出す
							MYRECT rc = GetHitRectFromFrame(frameId, ii, _gChara[i].x, _gChara[i].y, tblMotion[_gChara[i].motId].mirror_lr);

							// 矩形描画
							MyDrawBox(mView, rc.x, rc.y, rc.x + rc.w, rc.y + rc.h, tblColor[type], TRUE);
						}
					}
				}
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定


	}

	//星の描画
	for(int i = 0; i <= STAR_MAX; i++) {

		if(star[i].star_use != 0) {

			if(star[i].checkStar != 0)
			{
				DrawGraph(star[i].pos.x, star[i].pos.y, star[0].cgStar, TRUE);
			}
			/*DrawFormatString(1, 20 * 3, GetColor(255, 255, 255), "checkStar = %d", star[0].direction);
			DrawFormatString(1, 20 * 4, GetColor(255, 255, 255), "checkStar = %d", star[1].direction);
			DrawFormatString(1, 20 * 5, GetColor(255, 255, 255), "checkStar = %d", star[2].direction);
			DrawFormatString(1, 20 * 6, GetColor(255, 255, 255), "checkStar = %d", star[3].direction);
			DrawFormatString(1, 20 * 7, GetColor(255, 255, 255), "checkStar = %d", star[4].direction);
			DrawFormatString(1, 20 * 8, GetColor(255, 255, 255), "checkStar = %d", star[5].direction);*/
		}
	}

	/*if(pause == 1) {
		DrawGraph(0, 0, _cgPause, TRUE);
	}*/

}
