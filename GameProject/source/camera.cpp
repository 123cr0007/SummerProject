#include "Camera.h"
#include "mymath.h"
#include "winmain.h"

Camera::Camera() {
	_pos = VGet(SCREEN_W / 2, SCREEN_H / 2, 0);
	_lookat = VGet(SCREEN_W / 2, SCREEN_H / 2, 0);
	_camControl = 0;
	_scale = 1.0f;
	_rotate = 0.0f;
}

Camera::~Camera() {
	// 何もしない
}

void	Camera::Process() {
	// 位置がリミットを超えないように（回転は加味せず）
	float left, top, right, bottom;
	left	= _rcLimit.x + _lookat.x / _scale;
	right	= (_rcLimit.x + _rcLimit.w) - _lookat.x / _scale;
	top		= _rcLimit.y + _lookat.y / _scale;
	bottom	= (_rcLimit.y + _rcLimit.h) - _lookat.y / _scale;
	_pos.x = Clamp(left, right, _pos.x);
	_pos.y = Clamp(top, bottom, _pos.y);


	// View行列の生成
	MATRIX m = MGetTranslate(VScale(_pos, -1));				// カメラ位置を*-1する
	m = MMult(m, MGetScale(VGet(_scale, _scale, 1)));		// Z方向の倍率は1のまま
	m = MMult(m, MGetRotZ(DegToRad(_rotate)));				// 2Dでx,yを回転させるには、3DならZ軸回転になる
	m = MMult(m, MGetTranslate(_lookat));					// 注視点分ずらす
	_mView = m;
}

