#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "DxLib.h"		// VECTOR��MATRIX���`�Ƃ��Ďg�����߁A.h�ɓ���Ă���
#include "mymath.h"

class Camera {
public:
	Camera();
	~Camera();

	void	Process();
	MATRIX	GetViewMatrix() { return _mView; }

public:
	int _camControl;	// �J�������삷��Ȃ�1
	MATRIX	_mView;		// View�s��
	VECTOR	_pos;		// �J�����̈ʒu�Bworld���W��
	VECTOR	_lookat;	// �J�����̒����_�B��ʂ̂����𒆐S�ɁA�g��/��]������
	float	_scale;		// �J�����̊g�嗦
	float	_rotate;	// �J�����̉�]�idegree)

	MYRECT	_rcLimit;	// world���W�Ń��~�b�g�ݒ�


};
