#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "scenebase.h"
#include "GamePad.h"

// ����cpp�ł��g�������O���[�o���ϐ��́A�w�b�_�t�@�C����extern�錾����

// �Q�[�����
extern GamePad	gPad;			// �Q�[���p�b�h�̏��


void ChangeScene(SceneBase* scene);	// Scene��ύX����

void ChangeScene(SceneBase* scene);	// Scene��ύX����
void ColorMask(int colorR, int colorG, int colorB, int colorA);		// �J���[�}�X�N�̎w��

// �w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha=255�ɂ���j
void ColorFadeOut(int colorR, int colorG, int colorB, int frames);

// ���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha=0�ɂ���j
void ColorFadeIn(int frames);

// �t�F�[�h�C���A�E�g�͏I���������H
// �߂�l: 1 = �t�F�[�h��, 0 = �t�F�[�h�I��(�������͊J�n�O)
int IsColorFade();

void GameMain();	// gamemain.cpp �Ɏ��̂��L�q

