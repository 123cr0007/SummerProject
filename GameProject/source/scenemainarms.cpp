#include"scenegamemain.h"
#include"DxLib.h"
#include"gamemain.h"


	//�O���̘r
int SceneGameMain::CharaArmProcessF(int i, int j)
{
	// �g���L�[����
	int padNo = 0;
	switch(_gChara[i].group)
	{
	case CHARA_GROUP_ARMS:
		padNo = 0;
		break;
	}

	int motChg = -1;
	//
	//�ǂ̃��[�V�������g�����ԍ��Ő���
	// 1�A�E�U���E2�A���U���E3�A�󒆍U���E4�A���V
	//
	int motNo = 0;
	int atk = 0;
	_gChara[i].x = pl_x;
	_gChara[i].y = pl_y;
	_gChara[i].arrow = pl_arrow;

	//���V���[�V����
	if (gPad._key & PAD_INPUT_3)
	{
		if (pl_stand == 0) {
			motNo = 4;
		}
	}
	//�E�����p���`
	if (_gChara[i].arrow == 1) {
		if (gPad._trg & PAD_INPUT_8) {

			motNo = 1;
		}
	}
	//�������p���`
	if (_gChara[i].arrow == -1) {
		if (gPad._trg & PAD_INPUT_7) {

			motNo = 2;
		}
	}
	//�󒆍U��
	if (pl_stand == 0) {
		if (gPad._trg & PAD_INPUT_8 && gPad._key & PAD_INPUT_7) {

			motNo = 3;
		}
	}

	//��{�͑ҋ@���
	if (_gChara[i].motId == MOTION_ARM_F_WAIT_R 
		|| _gChara[i].motId == MOTION_ARM_F_WAIT_L) {

		if (_gChara[i].arrow == 1) {

			motChg = MOTION_ARM_F_WAIT_R;
		}
		else {

			motChg = MOTION_ARM_F_WAIT_L;
		}
	}
	
	switch (_gChara[i].motId)
	{
		//�ҋ@���&���V��Ԃ̎��̂ݍU����
		case MOTION_ARM_F_WAIT_R:
		case MOTION_ARM_F_WAIT_L:
		case MOTION_ARM_F_RIDE_R:
		case MOTION_ARM_F_RIDE_L: {
			switch (motNo)
			{
			case 4:
				if (_gChara[i].arrow == 1) {

					motChg = MOTION_ARM_F_RIDE_R;
				}
				else {

					motChg = MOTION_ARM_F_RIDE_L;
				}
				break;
			case 1:

				//�E�ʏ�U��
				motChg = MOTION_ARM_F_ATTACK_R;
				break;
			case 2:

				//���ʏ�U��
				motChg = MOTION_ARM_F_ATTACK_L;
				break;
			case 3:

				//�󒆍U��
				if (_gChara[i].arrow > 0)
				{
					motChg = MOTION_ARM_F_FALL_R;
				}
				// ������
				if (_gChara[i].arrow < 0)
				{
					motChg = MOTION_ARM_F_FALL_L;
				}
				break;
			case 0:
				if (_gChara[i].arrow == 1) {

					motChg = MOTION_ARM_F_WAIT_R;
				}
				else {

					motChg = MOTION_ARM_F_WAIT_L;
				}
				break;
			}
		}
	}
	return motChg;
}


//��둤�̘r
int SceneGameMain::CharaArmProcessB(int i, int j)
{
	// �g���L�[����
	int padNo = 0;
	switch(_gChara[i].group)
	{
	case CHARA_GROUP_ARMS:
		padNo = 0;
		break;
	}

	int motChg = -1;
	//
	//�ǂ̃��[�V�������g�����ԍ��Ő���
	// 1�A�E�U���E2�A���U���E3�A�󒆍U���E4�A���V
	//
	int motNo = 0;
	int atk = 0;
	_gChara[i].x = pl_x;
	_gChara[i].y = pl_y;
	_gChara[i].arrow = pl_arrow;

	if (_gChara[i].motId == MOTION_ARM_B_WAIT_R
		|| _gChara[i].motId == MOTION_ARM_B_WAIT_L) {
		if (_gChara[i].arrow == 1) {

			motChg = MOTION_ARM_B_WAIT_R;
		}
		else {

			motChg = MOTION_ARM_B_WAIT_L;
		}
	}

	//���V���[�V����
	if (gPad._key & PAD_INPUT_3)
	{
		if (pl_stand == 0) {
			motNo = 4;
		}
	}
	//�E�����p���`
	if (_gChara[i].arrow == 1) {
		if (gPad._trg & PAD_INPUT_7) {

			motNo = 1;
		}
	}
	//�������p���`
	if (_gChara[i].arrow == -1) {
		if (gPad._trg & PAD_INPUT_8) {

			motNo = 2;
		}
	}
	//�󒆍U��
	if (pl_stand == 0) {
		if (gPad._trg & PAD_INPUT_8 && gPad._key & PAD_INPUT_7) {

			motNo = 3;
		}
	}

	switch (_gChara[i].motId)
	{

		case MOTION_ARM_B_WAIT_R:
		case MOTION_ARM_B_WAIT_L:
		case MOTION_ARM_B_RIDE_R:
		case MOTION_ARM_B_RIDE_L: {
			switch (motNo)
			{
			case 4:
				if (_gChara[i].arrow == 1) {

					motChg = MOTION_ARM_B_RIDE_R;
				}
				else {

					motChg = MOTION_ARM_B_RIDE_L;
				}
				break;
			case 1:
				//�E�ʏ�U��
				motChg = MOTION_ARM_B_ATTACK_R;
				break;
			case 2:
				//���ʏ�U��
				motChg = MOTION_ARM_B_ATTACK_L;
				break;
			case 3:
				//�󒆍U��
				if (_gChara[i].arrow > 0)
				{
					motChg = MOTION_ARM_B_FALL_R;
				}
				// ������
				if (_gChara[i].arrow < 0)
				{
					motChg = MOTION_ARM_B_FALL_L;
				}
				break;
			case 0:
				if (_gChara[i].arrow == 1) {

					motChg = MOTION_ARM_B_WAIT_R;
				}
				else {

					motChg = MOTION_ARM_B_WAIT_L;
				}
				break;
			}
		}
	}
	return motChg;
}
