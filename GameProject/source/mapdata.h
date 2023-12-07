#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "DxLib.h"		// VECTOR��MATRIX���`�Ƃ��Ďg�����߁A.h�ɓ���Ă���
#include <vector>
#include <string>
#include "map.h"
namespace chip {
//�G�b�t�F�N�g�摜
#define EF_NONE				0
#define EF_BLOCK_DARK		1
#define EF_BLOCK_ROCK		40
#define EF_SPARK_PURPLE		60
#define EF_SPARK_GREEN		80
#define EF_SPARK_WHITE		100
#define EF_SPARK_RED		120
#define EF_SPARK_YELLOW		140
#define _EF_ALL_ 200

//�G�t�F�N�g�^�C�v
#define EF_TYPE_NONE	0
#define EF_TYPE_DARK	1
#define EF_TYPE_ROCK	2
#define EF_TYPE_PURPLE	3
#define EF_TYPE_GREEN	4
#define EF_TYPE_WHITE	5
#define EF_TYPE_RED		6
#define EF_TYPE_YELLOW	7
#define EFFECT_MAX	1000
	class Particle2
	{
	public:
		Particle2(int cg, float x, float y, float vx, float vy, int cnt, int w, int h);
		~Particle2();

		bool	Process();
		void	Draw(MATRIX mView);

		void	SetColor(int r, int g, int b, int a);

	public:
		int		_cg;		// �摜
		int		_w, _h;		// �摜�T�C�Y
		int		_color_r, _color_g, _color_b, _color_a;		// �F

		float	_x, _y;		// ���W
		float	_vx, _vy;	// �ړ�����
		int		_cnt;		// ����J�E���^

	};
	class MapData {
	public:
		MapData();			// �R���X�g���N�^
		virtual ~MapData();	// �f�X�g���N�^
		void SetBlockData(int chip_no);




		// �����蔻��֘A
		int		CheckHitMapChip(int x, int y);	// �w��ʒu�̃`�b�v�������蔻�肠�肩�H
		//void	ChangeMapChip(int chip_no);	// �w��ʒu�̃`�b�v�������蔻�肠�肩�H
		int		CheckHitChip(int chip_no);		// �w��̃`�b�vID�������蔻�肠�肩�H
		int		HitChipDamage(int box_x, int box_y, int box_w, int box_h, int armPULv);
		int  	DeleteChip(int x, int y, int& data_type, int armPULLv);

		struct HITSLIDE {
			int	hit;				// �������Ă����1�A�������Ă��Ȃ������0
			int	slide_x, slide_y;	// �������Ă���ꍇ�A���炷�ׂ��l
		};
		HITSLIDE IsHitBox(int box_x, int box_y, int box_w, int box_h, int move_x, int move_y);	// �w���box��move_x,move_y�Ɉړ����Ă����ꍇ�A�}�b�v�`�b�v�ɓ����邩�H
		//�V�����ǉ�����JSON�p�}�b�v�֐�
		void Draw(MATRIX mView);
		void Draw2(MATRIX mView);

		void SetMap(tiled::TiledMap* map) { _tiledMap = map; }
		bool LoadChip(const std::string path);
		int SetChip();

		void DrawStar(MATRIX mView);
		void DeleteStar();
		//�G�b�t�F�N�g�֘A
		int AddEffect(int x, int y, int type);
		void DrawEffect(MATRIX mView,int i);
		int EffectAnm(int i);
		void DeleteEffect(int i);
		void SearchEffect(int x, int y, int data_type,int armPULv);
		// �}�b�v�`�b�v�֘A
#define	CHIPSIZE_W	(60)
#define	CHIPSIZE_H	(60)

#define CHIP_TYPE_NONE		0
#define CHIP_TYPE_GROUND	1
#define CHIP_TYPE_ROCK		2

// �}�b�v�f�[�^
#define	MAPSIZE_W	(256)
#define	MAPSIZE_H	(39)

	// world�̃T�C�Y���擾(pixel�P��)
		int	GetWorldSizeW() { return 1920 * 8; }
		int	GetWorldSizeH() { return 2160 + 180; }


		struct Chip
		{
			int id;
			int hp;
			int type;
		};
		std::vector<Chip> data;

	protected:

		void	Process_Star(int i, int x, int y);
		int		checkblock = 0;

#define STAR_MAX 20
#define STAR_SPAWN_MAX 100
		int time[STAR_SPAWN_MAX] = { 0 };
		struct Star
		{
			int cgStar;			//�|�������ɏo�Ă��鐯
			int direction;		//�����o���p�x
			int checkStar;		//
			int star_use;		//
			int speed;			//���̑��x
			int x, y;
			VECTOR pos;			//���̏ꏊ
		};
		struct Star		star[STAR_SPAWN_MAX][STAR_MAX];

		struct Effect
		{
			int x = 0;
			int y = 0;
			int arrow = 0;
			int type = 0;
			int time = 0;//��A�̎���
			int useGraphNum = 0;//�g���摜����
			int startGraphNum = 0;//�G�t�F�N�g�̏��߂̉摜�ԍ�
			int cg = 0;
			int useEf = 0;
		};
		struct Effect ef[EFFECT_MAX];
		int _cgef[_EF_ALL_];
		int framecount;

		int star_se;
		int rock_se;
		int iron_se;
		int glass_se;
		int soil_se;
		int concrete_se;
		int kusa_se;
		int chip_se;
		int chip_1_se;//�S�ɂ͂����ꂽ�Ƃ�
		std::vector<int> _cgChip;		// �`�b�v�摜
		int _cgStar[5];		//���摜
		tiled::TiledMap* _tiledMap;//json�֘A
		int r; int g; int b;
		std::vector<Particle2*>	_vParticles;
		int		_cgParticle;
		int c_cnt;
	};
}
