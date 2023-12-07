#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�


// �����蔻��\����
struct CHARA_HITRECT {
	int		type;				// �����蔻��̎��
	int		hx, hy, hw, hh;		// ��_����̔����`
};

// �����蔻����
#define	CHARA_HITRECT_TYPE_NONE		0
#define	CHARA_HITRECT_TYPE_ATTACK	1
#define	CHARA_HITRECT_TYPE_DAMAGE	2
#define CHARA_HITRECT_TYPE_BREAK	3
#define CHARA_HITRECT_TYPE_PLAYER	4
#define CHARA_HITRECT_TYPE_CORE		5

#define	CHARA_HITRECT_NUM	10	

// �L�����N�^�t���[���\����
// 1���̃t���[���Ɋւ���ݒ�
struct CHARA_FRAME {
	int		frameId;	// �t���[��ID�B�ŗL�̔ԍ���U��
	int		cgId;		// �g�p�摜�ԍ� cgChara[]
	int		cx, cy;		// �摜�̊�_�B�������w��
	int		w, h;		// �摜�T�C�Y
	float   angle;		// �摜�̊p�x
	CHARA_HITRECT	hit[CHARA_HITRECT_NUM];		// �����蔻���`
};



extern struct CHARA_FRAME tblFrame[];
