#pragma once


	//UI�p�萔
constexpr auto UI_MAX = 7;			//�ő�l

constexpr auto UI_BASE = 0;          //UI
constexpr auto UI_POS_X_BASE = 0;	//UI�u�����x���W
constexpr auto UI_POS_Y_BASE = 900;	//UI�u�����y���W

constexpr auto UI_HP = 1;			//HP�o�[
constexpr auto UI_POS_X_HP = 10;		//HP�o�[��x���W
constexpr auto UI_POS_Y_HP = 910;	//HP�o�[��y���W
constexpr auto UI_HP_MAX = 545;		//HP�o�[�ő�l

constexpr auto UI_EN = 2;			//�G�l���M�[�o�[
constexpr auto UI_POS_X_EN = 1310;	//�G�l���M�[�o�[��x���W
constexpr auto UI_POS_Y_EN = 910;	//�G�l���M�[�o�[��y���W

constexpr auto UI_START = 3;			//�X�^�[�g
constexpr auto UI_POS_X_START = 0;	//�X�^�[�g��x���W
constexpr auto UI_POS_Y_START = 0;	//�X�^�[�g��y���W

constexpr auto UI_CLEAR = 4;			//�N���A
constexpr auto UI_POS_X_CLEAR = 0;	//�N���A��x���W
constexpr auto UI_POS_Y_CLEAR= 0;	//�N���A��y���W

constexpr auto UI_OVER = 5;			//�Q�[���I�[�o�[
constexpr auto UI_POS_X_OVER = 0;	//�Q�[���I�[�o�[��x���W
constexpr auto UI_POS_Y_OVER = 0;	//�Q�[���I�[�o�[��y���W

constexpr auto UI_ISBREAK = 6;			//�ǂ̃u���b�N���j��\��
constexpr auto UI_POS_X_BREAK = 660;	//���x���W
constexpr auto UI_POS_Y_BREAK = 930;	//�����y���W


class UI
{
public:

		UI();			//�R���X�g���N�^�[
		virtual ~UI();	//�f�X�g���N�^�[

		int Process();

		void Draw(int pl_hp);

protected:
	//�ϐ�
	int _ui[UI_MAX];

	float hp;

	float ui_hp;
	
	int time ;
	int second;

	int _uiCover;
};
extern int overtime;

extern int cntBrokeBlock;
extern int cntDeadEnem;
extern int score;
extern int gtime;