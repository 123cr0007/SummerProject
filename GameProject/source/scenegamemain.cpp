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
	//�w�i
	if(stage < 3)
	{
		_cgBg = LoadGraph("res/BG/City.png");
	}
	else
	{
		_cgBg = LoadGraph("res/BG/Lab.png");
	}

	mapData = new chip::MapData();
	const auto path = _T("map/");//�p�X
	auto json = _T("map_1_ex.json");//�}�b�v�t�@�C��

	//json�}�b�v�ǂݎ��
	if(stage == 1)
	{
		json = _T("map_1_ex.json");//�}�b�v�t�@�C��
	}
	else if (stage == 2)
	{
		json = _T("map_2.json");//�}�b�v�t�@�C��
	}
	else if (stage == 3)
	{
		json = _T("map_3.json");//�}�b�v�t�@�C��
	}
	else if (stage == 4)
	{
		json = _T("bossmap.json");//�}�b�v�t�@�C��
	}
	
	tiled::TiledMap* tiledMap = tiled::In(path, json);
	mapData->SetMap(tiledMap);

	if (!mapData->LoadChip(path))
	{
		// ���[�h���s
		delete mapData;
	}

	// �L�����f�[�^�̏����ݒ�
	for (int i = 0; i < CHARA_MAX; i++)
	{
		_gChara[i].type = CHARA_TYPE_NONE;		// ��������A�S�L������none��
	}
	//�L�����f�[�^��tiledMap��object����ݒ�
	for (auto& obj : tiledMap->objects) {
		//����if���̌`��AddChara���邱�ƁB
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


	mapData->SetChip();//�v���p�e�B��ݒ�

	LoadCharaData();//�L�����N�^�f�[�^���[�h

	// �J�����̃��~�b�g�ݒ�
	auto& layers = tiledMap->layers[0];
	_cam._rcLimit.x = 0;
	_cam._rcLimit.y = 0;
	_cam._rcLimit.w = layers.width * 60;
	_cam._rcLimit.h = layers.height * 60;


	//use_arm = 0;
	//��������
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
	
	pl_x = 0;//�r�Ǐ]�p
	pl_y = 0;//�r�Ǐ]�p
	pl_arrow = 0;//�r�Ǐ]�p

	//�G�̍��W����p
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
	
	//�f�o�b�O�p
	armtype = 0;

	// �J���[�}�X�N�̃��Z�b�g
	//ColorMask(0, 0, 0, 0);
	ColorFadeIn(60);		// �t�F�[�h�C���ɕύX
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
	// �������Ȃ�
}


// �p�[�e�B�N��
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

// ��������Ȃ�ture, �폜����Ȃ�false��Ԃ�
bool Particle::Process() {
	// �ʒu�̈ړ�
	_x += _vx;
	_y += _vy;
	// �J�E���^�����炷
	_cnt--;
	// �J�E���^��0�ȉ��ɂȂ�����폜
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
	SetDrawBlendMode(DX_BLENDMODE_ADD, _color_a);		// ���Z�`��w��
	SetDrawBright(_color_r, _color_g, _color_b);
	VECTOR world = VGet(_x, _y, 0);

	MyDrawTurnModiGraph(mView, world, 1.0f, 1.0f, _w, _h, _cg);	// (x,y)�𒆐S�ʒu�Ƃ��ĕ`��

	SetDrawBright(255, 255, 255);		// �F��߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��
}


void SceneGameMain::Process()
{
	//�G�l���M�[���g�����ǂ���
	//0�F�g��Ȃ��A1�F�g��
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
					// ���ʏ����i�O�j
					//

					int motChg = -1;		// ���[�V������ύX����ꍇ�A�����Ɏw�肷��

					// �d�͏���
					if(_gChara[i].useGravity == 1) {
						_gChara[i].gravity += 1;			// �L�����́A�d�͂ɂ������l��傫������
						_gChara[i].y += _gChara[i].gravity;	// �d�͂ɂ������l�̕������ړ�����
						_gChara[i].stand = 0;			// ���ɓ������ĂȂ����Ƃ�O��ɁA���t���O���Z�b�g
					}

					// �㉺�̓����蔻��
					if (_gChara[i].group != CHARA_GROUP_OBJECT) {

						if (CheckCharaMove(i, 0, _gChara[i].gravity) != 0)
						{
							// ���������B���������̂͏����H�i�d�͒l�̓v���X���������H�j
							if (_gChara[i].gravity > 0)
							{
								_gChara[i].stand = 1;	// ���ɓ��������̂Ńt���O�Z�b�g
							}
							_gChara[i].gravity = 0;		// �d�͂ɂ������l�����Z�b�g
						}
					}
					else if (_gChara[i].DamegeFase == 0) {

						if (CheckCharaMove(i, 0, _gChara[i].gravity) != 0)
						{
							// ���������B���������̂͏����H�i�d�͒l�̓v���X���������H�j
							if (_gChara[i].gravity > 0)
							{
								_gChara[i].stand = 1;	// ���ɓ��������̂Ńt���O�Z�b�g
							}
							_gChara[i].gravity = 0;		// �d�͂ɂ������l�����Z�b�g
						}
					}

					//
					// �^�C�v�ʌʏ���
					//
						switch(_gChara[i].group)
						{
							case CHARA_GROUP_PLAYER:
							{	// �v���C��-
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
					// ���ʏ����i��j
					//

					for(int i = 0; i < CHARA_MAX; i++)
					{
					int frameId = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);

						HitChipFromFrame(frameId, i);
					}

					// �����蔻��
					int j;
					// �������_���[�W���󂯂邩�̔�����s��
					for(j = 0; j < CHARA_MAX; j++)
					{
						// ���L��������Ȃ��A���L�����^�C�v������
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
							//�Ƃ�܂���
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
							//�����܂�
							if(_gChara[i].type == _gChara[j].type)
							{
								continue;
							}

							// [i]��[j]�œ����蔻��
							// [i]�i�����j�̎��_���[�W����ƁA[j]�i����j�̎��U������Ƃ̓����蔻��B
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
										{	// [i]�̃_���[�W����, [j]�̍U�����肪��������
											// ��̓����蔻���`�����o��
											MYRECT rc_i = GetHitRectFromFrame(frameId_i, ii, _gChara[i].x, _gChara[i].y, tblMotion[_gChara[i].motId].mirror_lr);
											MYRECT rc_j = GetHitRectFromFrame(frameId_j, jj, _gChara[j].x, _gChara[j].y, tblMotion[_gChara[j].motId].mirror_lr);



											// RECT�̓����蔻��
											if (IsHitBox(rc_i.x, rc_i.y, rc_i.w, rc_i.h,
												rc_j.x, rc_j.y, rc_j.w, rc_j.h) == 1
												) {
												// ���������B�����̓_���[�W��H�炤
												// �_���[�W�̕����́A�����X���W���画�f
												if (_gChara[i].x > _gChara[j].x)
												{
													// ���肪�����ɋ���̂ŁA����������������
													_gChara[i].arrow = -1;
													_gChara[i].HP -= _gChara[j].Pow;
												}
												else {
													// ���肪�E���ɋ���̂ŁA�������E��������
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
												// �_���[�WSE
												//�@��
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
												// [i]�̃_���[�W����, [j]�̍U�����肪��������
												// ��̓����蔻���`�����o��
												MYRECT rc_i = GetHitRectFromFrame(frameId_i, ii, _gChara[i].x, _gChara[i].y, tblMotion[_gChara[i].motId].mirror_lr);
												MYRECT rc_j = GetHitRectFromFrame(frameId_j, jj, _gChara[j].x, _gChara[j].y, tblMotion[_gChara[j].motId].mirror_lr);

												// RECT�̓����蔻��
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

					// ���[�V�����͕ύX����Ȃ����H
					if(motChg == -1 || motChg == _gChara[i].motId)
					{
						// ���[�V�������ړ�
						// mx,my�Ɉړ��l�𓾂�
						int mx, my;
						mx = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].mx;
						my = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].my;

						// �ړ����Ă݂�
						_gChara[i].x += mx;
						_gChara[i].y += my;

						// �ړ��\���H�����蔻��B�ړ��s�Ȃ璆�ňʒu����
						CheckCharaMove(i, mx, my);

						// ���̃��[�V�����̂܂܂Ȃ̂ŁA�J�E���^��i�߂�
						_gChara[i].animcnt++;

						// ���[�V�����̍��̃t���[���͏I���������H
						if(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt <= _gChara[i].animcnt)
						{
							// ���̃t���[����
							_gChara[i].motcnt++;
							_gChara[i].animcnt = 0;

							// ���̃t���[���̓R�}���h���H
							// �R�}���h�������A���ŏ����ł���悤�ɁA���[�v�������Ă���
							int loop = 1;
							while(loop == 1)
							{
								// �R�}���h����
								switch(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId)
								{
								case CHARA_MOTION_CMD_LOOP:
								{	// ���[�V���������[�v����(frameCnt�Ƀ��[�V����index�w��)
									int motionIndex = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
									_gChara[i].motcnt = motionIndex;
									break;
								}
								case CHARA_MOTION_CMD_MOTION:
								{	// �ʂ̃��[�V������(frameCnt�̓��[�V����ID)
									int motionId = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
									CharaChangeMotion(i, motionId);
									loop = 0;	// ���[�v�I��
									break;
								}
								case CHARA_MOTION_CMD_PLAYSE:
								{	// ���ʉ��Đ�(frameCnt��SE_xxxx)
									int seId = tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
									PlaySoundMem(_se[seId], DX_PLAYTYPE_BACK, TRUE);
									_gChara[i].motcnt++;
									break;
								}
								case CHARA_MOTION_CMD_HPCHECK:
								{	// HP���`�F�b�N��0�ȉ��Ȃ玀�S
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
								// �R�}���h��ǉ�����ꍇ�́A�R�}���h������������motcnt++����
									_gChara[i].motcnt++;
									break;
								}
								*/
								default:
								{	// �R�}���h����Ȃ������̂Ń��[�v�I��
									loop = 0;
								}
								}
							}
						}
					}
					// ���[�V�����͕ύX����邩�H
					if(motChg != -1 && motChg != _gChara[i].motId)
					{
						// ���ƕʂ̃��[�V�����ɕύX
						CharaChangeMotion(i, motChg);
					}
				}
			}
		}

		// �J�����ʒu��CHARA_TYPE_PLAYER1�̈ʒu�ɂ���
		for(i = 0; i < CHARA_MAX; i++)
		{
			if(_gChara[i].type == CHARA_TYPE_PLAYER1) {
				_cam._pos = VGet(_gChara[i].x, _gChara[i].y, 0);
			}
		}

		// �J�����������Ă�
		_cam.Process();

		//�^�C�}�[�̏���
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

	// �J������View�s��ŁA��ʏ�̍��W���v�Z�iView���W�j
	MATRIX	mView = _cam.GetViewMatrix();

	// �w�i
	DrawGraphF(0.0f - BGMoveX(), -900.0f, _cgBg, TRUE);

	// �}�b�v�`��
	mapData->Draw(mView);

	//�|�[�Y
	if(pause == 1)
	{
		DrawGraph(0, 0, _cgPause, TRUE);
	}

	// �L�����`��
		// �܂���layer���Q�l�ɕ`�揇�����
	int drawCharaIndex[CHARA_MAX];
	for(i = 0; i < CHARA_MAX; i++)
	{
		drawCharaIndex[i] = i;
	}
	// layer���ɕ��ѕς�
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

				// �L�����̃��[�V�����t���[��������𓾂�
				int frameId = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);
				int cgId = tblFrame[frameId].cgId;
				// ���E���]���邩�H
				if(tblMotion[_gChara[i].motId].mirror_lr == 0)
				{
					// ���Ȃ�
					// �`��ʒu�́A��_�����炵���ꏊ
					x = _gChara[i].x - tblFrame[frameId].cx;
					y = _gChara[i].y - tblFrame[frameId].cy;
					// ������x,y��DrawGraph()�p�ɉ摜�̍���Ȃ̂ŁAMyDrawModiGraph()�̒��S�ʒu�ɂ͍���Ȃ�

					VECTOR world = VGet(x, y, 0);
					// �摜�̒��S��world���W�Ƃ���̂ŁA�T�C�Y/2�������炷
					world.x += tblFrame[frameId].w / 2;
					world.y += tblFrame[frameId].h / 2;
					
					//�L�����̕`��
					MyDrawModiGraph(mView, world, 1.f, tblFrame[frameId].angle, tblFrame[frameId].w, tblFrame[frameId].h, _cgChara[cgId]);
					//MyDrawModiGraph(/*�ꏊ*/ world, /*�p�x*/ tblFrame[frameId].angle,/*�n���h��*/ _cgChara[cgId]);
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
					// ����
					// �`��ʒu�́A���E���]���Ă����_�����炵���ꏊ
					x = _gChara[i].x - (tblFrame[frameId].w - tblFrame[frameId].cx);
					y = _gChara[i].y - tblFrame[frameId].cy;
					// ������x,y��DrawGraph()�p�ɉ摜�̍���Ȃ̂ŁAMyDrawModiGraph()�̒��S�ʒu�ɂ͍���Ȃ�

					VECTOR world = VGet(x, y, 0);
					// �摜�̒��S��world���W�Ƃ���̂ŁA�T�C�Y/2�������炷
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
				//�R�����g
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
				// �`��ʒu�́A��_�����炵���ꏊ
				x = _gChara[i].x - tblFrame[frameId].cx;
				y = _gChara[i].y - tblFrame[frameId].cy;
				// ������x,y��DrawGraph()�p�ɉ摜�̍���Ȃ̂ŁAMyDrawModiGraph()�̒��S�ʒu�ɂ͍���Ȃ�

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
				// �摜�̒��S��world���W�Ƃ���̂ŁA�T�C�Y/2�������炷
				world.x += tblFrame[frameId].w / 2;
				world.y += tblFrame[frameId].h / 2;

				
				//�F�𐶐�
				if (_gChara[i].type == CHARA_TYPE_ARM_R)
				{
					//�F�𐶐�
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
						float rad = DegToRad(120+rand()%30-15);		// �p�x��degree����radian�ɕϊ�
						vDir1.x = cos(rad);
						vDir1.y = sin(rad);
						// ������x�N�g�����u�P�ʃx�N�g���v�i�X�J����1�̃x�N�g���j�ɂ���
						VECTOR vUnit = VNorm(vDir1);
						// �P�ʃx�N�g���Ɉړ����x���������A�ړ��x�N�g�������
						VECTOR vMove = VScale(vUnit, 10);
						// �ړ��x�N�g�����ʒu�ɉ��Z����
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
						float rad = DegToRad(50 + rand() % 30 - 15);		// �p�x��degree����radian�ɕϊ�
						vDir1.x = cos(rad);
						vDir1.y = sin(rad);
						// ������x�N�g�����u�P�ʃx�N�g���v�i�X�J����1�̃x�N�g���j�ɂ���
						VECTOR vUnit = VNorm(vDir1);
						// �P�ʃx�N�g���Ɉړ����x���������A�ړ��x�N�g�������
						VECTOR vMove = VScale(vUnit, 10);
						// �ړ��x�N�g�����ʒu�ɉ��Z����
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
						float rad = DegToRad(rand() % 360);		// �p�x��degree����radian�ɕϊ�
						vDir1.x = cos(rad);
						vDir1.y = sin(rad);
						// ������x�N�g�����u�P�ʃx�N�g���v�i�X�J����1�̃x�N�g���j�ɂ���
						VECTOR vUnit = VNorm(vDir1);
						// �P�ʃx�N�g���Ɉړ����x���������A�ړ��x�N�g�������
						VECTOR vMove = VScale(vUnit, 10);
						// �ړ��x�N�g�����ʒu�ɉ��Z����
						pos = VAdd(pos, vMove);

						VECTOR v = VGet(pos.x, pos.y, 0);

						int w = rand() % 20 + 1; int h = rand() % 50 + 1;
						Particle* p = new Particle(_cgParticle, world.x, world.y, v.x, v.y, 15, w, w);
						p->SetColor(r, g, b, 300);
						_vParticles.push_back(p);

					}
				}
				// �p�[�e�B�N���̏���
				for(auto ite = _vParticles.begin(); ite != _vParticles.end();) {
					// �p�[�e�B�N��������
					if((*ite)->Process() == true) {
						// �܂��������Ă���
						ite++;
					}
					else {
						// �p�[�e�B�N���͏I������
						ite = _vParticles.erase(ite);
					}
				}

				// �p�[�e�B�N���̕`��
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

	//�G�t�F�N�g
	//�G�t�F�N�g����
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
		// �J���p�F�����蔻��`��(�n�`/�L������)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		// �������`��w��
		{
			for(i = 0; i < CHARA_MAX; i++)
			{
				if(_gChara[i].type != CHARA_TYPE_NONE)
				{
					// �L�����̓����蔻������o��
					MYRECT rc = GetHitRectFromChara(i);

					// ��`�`��
					MyDrawBox(mView, rc.x, rc.y, rc.x + rc.w, rc.y + rc.h, GetColor(0, 255, 0), TRUE);
				}
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��

		// �J���p�F�����蔻��`��(���[�V������)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		// �������`��w��
		{
			// �����蔻��F�e�[�u��
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
					// �L�����̃��[�V�����t���[��������𓾂�
					int frameId = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);
					// �����蔻��̐������[�v
					int ii;
					for(ii = 0; ii < CHARA_HITRECT_NUM; ii++)
					{
						int type = tblFrame[frameId].hit[ii].type;
						if(type != CHARA_HITRECT_TYPE_NONE)
						{
							// �����蔻���`�����o��
							MYRECT rc = GetHitRectFromFrame(frameId, ii, _gChara[i].x, _gChara[i].y, tblMotion[_gChara[i].motId].mirror_lr);

							// ��`�`��
							MyDrawBox(mView, rc.x, rc.y, rc.x + rc.w, rc.y + rc.h, tblColor[type], TRUE);
						}
					}
				}
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��


	}

	//���̕`��
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
