#include "SceneGameMain.h"
#include "mydraw.h"
#include "camera.h"

int SceneGameMain::AddEffect(int i, int fx, int fy, int type)//fx,fy�͕\�����W������ׂ̂��́Btype�ŕ\���G�t�F�N�g���w��B
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

int  SceneGameMain::EffectAnm(int i)//�X�^�[�g��0�Ԃ���B�g�p���閇�����w��B��A�̃G�t�F�N�g�\���ɂ����鎞�ԁBtype�ɂ�LoadDivGraph�������Ă�Ƃ���B
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
		// �L�����̃��[�V�����t���[��������𓾂�
		int eftype = ef[i].type;

		// �`��ʒu�́A��_�����炵���ꏊ
		int x = ef[i].x;
		int y = ef[i].y;

		// ������x,y��DrawGraph()�p�ɉ摜�̍���Ȃ̂ŁAMyDrawModiGraph()�̒��S�ʒu�ɂ͍���Ȃ�
		VECTOR world = VGet(x, y, 0);

		// �摜�̒��S��world���W�Ƃ���̂ŁA�T�C�Y/2�������炷
		world.x += 60;
		world.y += 60;
		//������
		if (eftype == EFFECT_TYPE_BOMB_BLUE)
		{
			ef[i].cg = EF_EXPLOSION_BLUE + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//������
		if (eftype == EFFECT_TYPE_BOMB_CYAN)
		{
			ef[i].cg = EF_EXPLOSION_CYAN + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//������
		if (eftype == EFFECT_TYPE_BOMB_GREEN)
		{
			ef[i].cg = EF_EXPLOSION_GREEN + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//������
		if (eftype == EFFECT_TYPE_BOMB_PURPLE)
		{
			ef[i].cg = EF_EXPLOSION_PURPLE + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//������
		if (eftype == EFFECT_TYPE_BOMB_RED)
		{
			ef[i].cg = EF_EXPLOSION_RED + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		//������
		if (eftype == EFFECT_TYPE_BOMB_YELLOW)
		{
			ef[i].cg = EF_EXPLOSION_YELLOW + ef[i].startGraphNum;
			MyDrawModiGraph(mView, world, 3.0f, 0.0f, 120, 120, _cgef[ef[i].cg]);
		}
		EffectAnm(i);
	}
}