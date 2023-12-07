#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "DxLib.h"		// VECTORやMATRIXを定義として使うため、.hに入れておく
#include <vector>
#include <string>
#include "map.h"
namespace chip {
//エッフェクト画像
#define EF_NONE				0
#define EF_BLOCK_DARK		1
#define EF_BLOCK_ROCK		40
#define EF_SPARK_PURPLE		60
#define EF_SPARK_GREEN		80
#define EF_SPARK_WHITE		100
#define EF_SPARK_RED		120
#define EF_SPARK_YELLOW		140
#define _EF_ALL_ 200

//エフェクトタイプ
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
		int		_cg;		// 画像
		int		_w, _h;		// 画像サイズ
		int		_color_r, _color_g, _color_b, _color_a;		// 色

		float	_x, _y;		// 座標
		float	_vx, _vy;	// 移動方向
		int		_cnt;		// 動作カウンタ

	};
	class MapData {
	public:
		MapData();			// コンストラクタ
		virtual ~MapData();	// デストラクタ
		void SetBlockData(int chip_no);




		// 当たり判定関連
		int		CheckHitMapChip(int x, int y);	// 指定位置のチップが当たり判定ありか？
		//void	ChangeMapChip(int chip_no);	// 指定位置のチップが当たり判定ありか？
		int		CheckHitChip(int chip_no);		// 指定のチップIDが当たり判定ありか？
		int		HitChipDamage(int box_x, int box_y, int box_w, int box_h, int armPULv);
		int  	DeleteChip(int x, int y, int& data_type, int armPULLv);

		struct HITSLIDE {
			int	hit;				// 当たっていれば1、当たっていないければ0
			int	slide_x, slide_y;	// 当たっている場合、ずらすべき値
		};
		HITSLIDE IsHitBox(int box_x, int box_y, int box_w, int box_h, int move_x, int move_y);	// 指定のboxがmove_x,move_yに移動していた場合、マップチップに当たるか？
		//新しく追加したJSON用マップ関数
		void Draw(MATRIX mView);
		void Draw2(MATRIX mView);

		void SetMap(tiled::TiledMap* map) { _tiledMap = map; }
		bool LoadChip(const std::string path);
		int SetChip();

		void DrawStar(MATRIX mView);
		void DeleteStar();
		//エッフェクト関連
		int AddEffect(int x, int y, int type);
		void DrawEffect(MATRIX mView,int i);
		int EffectAnm(int i);
		void DeleteEffect(int i);
		void SearchEffect(int x, int y, int data_type,int armPULv);
		// マップチップ関連
#define	CHIPSIZE_W	(60)
#define	CHIPSIZE_H	(60)

#define CHIP_TYPE_NONE		0
#define CHIP_TYPE_GROUND	1
#define CHIP_TYPE_ROCK		2

// マップデータ
#define	MAPSIZE_W	(256)
#define	MAPSIZE_H	(39)

	// worldのサイズを取得(pixel単位)
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
			int cgStar;			//倒した時に出てくる星
			int direction;		//星を出す角度
			int checkStar;		//
			int star_use;		//
			int speed;			//星の速度
			int x, y;
			VECTOR pos;			//星の場所
		};
		struct Star		star[STAR_SPAWN_MAX][STAR_MAX];

		struct Effect
		{
			int x = 0;
			int y = 0;
			int arrow = 0;
			int type = 0;
			int time = 0;//一連の時間
			int useGraphNum = 0;//使う画像枚数
			int startGraphNum = 0;//エフェクトの初めの画像番号
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
		int chip_1_se;//鉄にはじかれたとき
		std::vector<int> _cgChip;		// チップ画像
		int _cgStar[5];		//星画像
		tiled::TiledMap* _tiledMap;//json関連
		int r; int g; int b;
		std::vector<Particle2*>	_vParticles;
		int		_cgParticle;
		int c_cnt;
	};
}
