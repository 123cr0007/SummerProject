#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"

class SceneGameLogo : public SceneBase {
public:
	SceneGameLogo();			// �R���X�g���N�^
	virtual ~SceneGameLogo();	// �f�X�g���N�^

	void	Input() override;	// ����
	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
	int		_cgBg;		// �w�i�摜
	int		_step;		// �t�F�[�h�C���A�E�g�p�X�e�b�v
	int		_bgm;
};
