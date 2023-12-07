#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�


// �L�����N�^����e�[�u��
struct CHARA_MOTION_ITEM {
	int		frameId;	// �\���������t���[��ID
	int		frameCnt;	// ���t���[���\�����邩
	int		mx, my;		// �\�����A1�t���[��������ړ�����l
};

// �P���[�V����������A���[�V�����A�C�e���������܂ŏ����邩
#define	CHARA_MOTION_ITEM_MAX	64

// ���[�V�����A�C�e���p�R�}���h�BframeId �Ɏw�肵�Ďg���BframeId�Əd�����Ă͂����Ȃ�
// �R�}���h�̓t���[���I�����ɏ�������邽�߁A�ŏ��̃t���[���ɂ͎w��ł��Ȃ��d�l
#define	CHARA_MOTION_CMD_LOOP		1	// ���[�V���������[�v����(frameCnt�Ƀ��[�V����index�w��)
#define	CHARA_MOTION_CMD_MOTION		2	// �ʂ̃��[�V������(frameCnt�Ƀ��[�V�����ԍ��w��)
#define	CHARA_MOTION_CMD_PLAYSE		3	// ���ʉ��Đ�(frameCnt��SE_xxxx)
#define CHARA_MOTION_CMD_HPCHECK	4
#define CHARA_MOTION_CMD_DELET		5
#define CHARA_MOTION_CMD_EFFECT		6
struct CHARA_MOTION {
	int		mirror_lr;	// ���E���]����Ȃ�1, ���Ȃ��Ȃ�0
	CHARA_MOTION_ITEM	item[CHARA_MOTION_ITEM_MAX];
};

// ���[�V�����ԍ��B0�Ԃ���̒ʂ��ԍ��ł��邱��
#define	MOTION_R_STAND		0
#define	MOTION_L_STAND		1
#define	MOTION_R_RUN		2
#define	MOTION_L_RUN		3
#define MOTION_R_WALK	4
#define MOTION_L_WALK	5
#define	MOTION_R_DAMAGE		6
#define	MOTION_L_DAMAGE		7
#define	MOTION_R_JUMP_UP	8
#define	MOTION_L_JUMP_UP	9
#define	MOTION_R_JUMP_DOWN	10
#define	MOTION_L_JUMP_DOWN	11
#define MOTION_ATTACK_R	12
#define MOTION_ATTACK_L	13

//�r
#define MOTION_ARM_F_WAIT_R 20
#define MOTION_ARM_F_WAIT_L	21
#define MOTION_ARM_B_WAIT_R	22
#define MOTION_ARM_B_WAIT_L	23
#define	MOTION_ARM_F_ATTACK_R	24
#define	MOTION_ARM_F_ATTACK_L	25
#define	MOTION_ARM_B_ATTACK_R	26
#define	MOTION_ARM_B_ATTACK_L	27
#define MOTION_ARM_F_FALL_R		28
#define MOTION_ARM_F_FALL_L		29
#define MOTION_ARM_B_FALL_R		30
#define MOTION_ARM_B_FALL_L		31
#define MOTION_ARM_F_RIDE_R		32
#define MOTION_ARM_F_RIDE_L		33
#define MOTION_ARM_B_RIDE_R		34
#define MOTION_ARM_B_RIDE_L		35//�G
//�����W
#define MOTION_RENJI_L_STAND 40
#define MOTION_RENJI_R_STAND 41
#define MOTION_RENJI_ATTACK_R	42
#define MOTION_RENJI_ATTACK_L	43
#define MOTION_RENJI_BEAM_L		44
#define MOTION_RENJI_BEAM_R		45
#define MOTION_RENJI_L_DAMAGE	46
#define MOTION_RENJI_R_DAMAGE	47
#define MOTION_RENJI_CORE		48
//�①��
#define MOTION_FREEZE_STAND_R	50
#define MOTION_FREEZE_STAND_L	51
#define	MOTION_FREEZE_DAMAGE_R	52
#define	MOTION_FREEZE_DAMAGE_L	53
#define	MOTION_FREEZE_ATTACK_R	54
#define	MOTION_FREEZE_ATTACK_L	55
#define MOTION_FREEZE_BULLET	56
#define MOTION_FREEZE_CORE		57
//�e���r
#define MOTION_TV_STAND_R		60
#define MOTION_TV_STAND_L		61
#define	MOTION_TV_DAMAGE_R		62
#define	MOTION_TV_DAMAGE_L		63
#define	MOTION_TV_ATTACK_R		64
#define	MOTION_TV_ATTACK_L		65
#define MOTION_TV_BULLET		66
#define MOTION_TV_CORE			67
//����@
#define MOTION_WASH_STAND_R		70
#define MOTION_WASH_STAND_L		71
#define	MOTION_WASH_DAMAGE_R	72
#define	MOTION_WASH_DAMAGE_L	73
#define	MOTION_WASH_ATTACK_R	74
#define	MOTION_WASH_ATTACK_L	75
#define MOTION_WASH_BULLET		76
#define MOTION_WASH_CORE		77
//��@
#define MOTION_FUN_STAND_R		80
#define MOTION_FUN_STAND_L		81
#define	MOTION_FUN_DAMAGE_R		82
#define	MOTION_FUN_DAMAGE_L		83
#define	MOTION_FUN_ATTACK_R		84
#define	MOTION_FUN_ATTACK_L		85
#define MOTION_FUN_BULLET		86
#define MOTION_FUN_CORE			87
//�{�X
#define MOTION_BOSS_STAND_R		90
#define MOTION_BOSS_STAND_L		91
#define	MOTION_BOSS_DAMAGE_R	92
#define	MOTION_BOSS_DAMAGE_L	93
#define	MOTION_BOSS_ATTACK_R	94
#define	MOTION_BOSS_ATTACK_L	95
#define MOTION_BOSS_BULLET		96
#define MOTION_BOSS_CORE		97
//�I�u�W�F�N�g
#define MOTION_OBJECT_VENDING	100
#define MOTION_OBJECT_SIGNBORD1	101
#define MOTION_OBJECT_SIGNBORD2	102
#define MOTION_OBJECT_POD1		103
#define MOTION_OBJECT_POD2		104
#define MOTION_OBJECT_SIGNBORD_ARROW	105
#define MOTION_OBJECT_SIGN1	106
#define MOTION_OBJECT_SIGN2	107
#define MOTION_OBJECT_SIGN3	108
#define MOTION_OBJECT_PILLAR1	109
#define MOTION_OBJECT_PILLAR2	110
#define MOTION_OBJECT_PILLAR3	111
#define MOTION_OBJECT_TREE	112
//�v�C��
#define MOTION_OBJECT_BATTERY	113
#define MOTION_EFFECT_EXPLOSION	114

#define MOTION_OBJECT_DOOR		115

#define MOTION_FREEZE_OPEN_L	116
#define MOTION_FREEZE_OPEN_R	117
#define MOTION_FREEZE_CLOSE_L	118
#define MOTION_FREEZE_CLOSE_R	119


extern struct CHARA_MOTION tblMotion[];

//�R�s�y�p
//MOTION