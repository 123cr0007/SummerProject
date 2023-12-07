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

// �L�����̒n�`/�L���������蔻������o��
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

// �t���[��ID�ƁAhitrectIndex����A���E���]�ɉ����������蔻��RECT�𓾂�
// (cx,cy)�͊�_���W
MYRECT SceneGameMain::GetHitRectFromFrame(int frameId, int hitrectIndex, int cx, int cy, int mirror_lr)
{
	MYRECT rc = { 0, 0, 0, 0 };

	int type = tblFrame[frameId].hit[hitrectIndex].type;
	if (type != CHARA_HITRECT_TYPE_NONE)
	{
		// ��`�̑傫��
		int x, y, w, h;
		w = tblFrame[frameId].hit[hitrectIndex].hw;
		h = tblFrame[frameId].hit[hitrectIndex].hh;

		// ���E���]���邩�H
		if (mirror_lr == 0)
		{
			// ���Ȃ�
			// �`��ʒu�́A��_�����炵���ꏊ
			x = cx - tblFrame[frameId].cx;
			y = cy - tblFrame[frameId].cy;
			// (x,y)�͕`�悷�鍶��ʒu�B��`�����炷
			x = x + tblFrame[frameId].hit[hitrectIndex].hx;
			y = y + tblFrame[frameId].hit[hitrectIndex].hy;
		}
		else
		{
			// ����
			// �`��ʒu�́A���E���]���Ă����_�����炵���ꏊ
			x = cx - (tblFrame[frameId].w - tblFrame[frameId].cx);
			y = cy - tblFrame[frameId].cy;
			// (x,y)�͕`�悷�鍶��ʒu�B��`�����炷
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

// �L�������ړ��\���A�����蔻��
// mx, my �̓L�����̈ړ�����
// �����蔻��Ńq�b�g������1���A���Ă��Ȃ����0��Ԃ�
int SceneGameMain::CheckCharaMove(int charaIndex, int mx, int my)
{
	int hit = 0;
	int i = charaIndex;		// [i] �����L�����Ƃ���

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	chip::MapData::HITSLIDE hitSlide;
	MYRECT rc = GetHitRectFromChara(i);
	hitSlide = mapData->IsHitBox(rc.x, rc.y, rc.w, rc.h, mx, my);


	if (hitSlide.hit != 0)
	{
		if (_gChara[i].group != CHARA_GROUP_ARMS)
		{
			// ���������̂ŁA�ʒu�𓮂���
			_gChara[i].x += hitSlide.slide_x;
			_gChara[i].y += hitSlide.slide_y;
			hit = 1;
		}
	}

	//// �ʃL�����Ƃ̓����蔻����s��
	//int j;					// [j] ��ʃL�����Ƃ���

	//// �������ʂ̃L�����Əd�Ȃ��Ă��邩�H�i�d�Ȃ��Ă����牟���o�����j
	for (int j = 0; j < CHARA_MAX; j++)
	{
		// ���L��������Ȃ��A���L�����^�C�v������
		if (i != j && _gChara[j].type != CHARA_TYPE_NONE)
		{
			//�Ƃ�܂���
			//������O���[�v�ɂ����B
			if (i != CHARA_TYPE_PLAYER1 && _gChara[j].group != CHARA_GROUP_ARMS
				 && _gChara[j].group != CHARA_GROUP_OBJECT && _gChara[j].group != CHARA_GROUP_ENEMY)
			{
				// [i]��[j]�œ����蔻��
				MYRECT rc_i = GetHitRectFromChara(i);
				MYRECT rc_j = GetHitRectFromChara(j);

				// RECT�̓����蔻��
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
int SceneGameMain::HitChipFromFrame(int frameId, int charaIndex)//�t���[�����g�����
{

	int i = charaIndex;
	for (int ii = 0; ii < CHARA_HITRECT_NUM; ii++)
	{
		//frameId_i = SearchFrame(tblMotion[_gChara[i].motId].item[_gChara[i].motcnt].frameId);

		if (tblFrame[frameId].hit[ii].type == CHARA_HITRECT_TYPE_BREAK)
		{		// [i]�̃_���[�W����
				// ��̓����蔻���`�����o��
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


// tblFrame[] �̔z��ԍ����AframeId�Œ��ׂ�
int SceneGameMain::SearchFrame(int frameId)
{
	int n = 0;
	while (tblFrame[n].frameId != -1)
	{
		if (tblFrame[n].frameId == frameId)
		{
			// ���������B[n]���z��ԍ�
			return n;
		}
		n++;
	}
	// ������Ȃ������i�{�����Ă͂����Ȃ��j
	return -1;
}

// �L�����̃��[�V�����ύX�w��
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

