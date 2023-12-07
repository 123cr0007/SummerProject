#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "DxLib.h"		// VECTORやMATRIXを定義として使うため、.hに入れておく
#include "mymath.h"

class Camera {
public:
	Camera();
	~Camera();

	void	Process();
	MATRIX	GetViewMatrix() { return _mView; }

public:
	int _camControl;	// カメラ操作するなら1
	MATRIX	_mView;		// View行列
	VECTOR	_pos;		// カメラの位置。world座標で
	VECTOR	_lookat;	// カメラの注視点。画面のここを中心に、拡大/回転をする
	float	_scale;		// カメラの拡大率
	float	_rotate;	// カメラの回転（degree)

	MYRECT	_rcLimit;	// world座標でリミット設定


};
