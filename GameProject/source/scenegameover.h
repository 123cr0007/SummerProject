#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"

class SceneGameOver : public SceneBase {
public:
	SceneGameOver();			// �R���X�g���N�^
	virtual ~SceneGameOver();	// �f�X�g���N�^

	void	Input() override;	// ����
	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
#define CG_BT_TITLE 2
#define CG_BT_NEXT	2

	int		select;
	int		_cgBg;		// �w�i�摜
	int     miss_cg;
	int		_cgNb[CG_BT_NEXT];		// NEXTSTAGE�{�^��
	int		_cgTb[CG_BT_TITLE];		// TITLE�{�^��
	int  _add_alpha;
	int count;
};

