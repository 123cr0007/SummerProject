#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "SceneGameTitle.h"
#include "SceneGameMain.h"
#include "scenegamelogo.h"


SceneGameLogo::SceneGameLogo() {
	_cgBg = LoadGraph("res/UI/amg_logo.png");
	_step = 0;
	_bgm = LoadSoundMem("res/push.mp3");

	ColorMask(0, 0, 0, 255);
	//ColorFadeIn(60);		// フェードインに変更
}

SceneGameLogo::~SceneGameLogo() {
	DeleteGraph(_cgBg);
}

void SceneGameLogo::Input() {
	// 何もしない
}

void SceneGameLogo::Process() {

	switch (_step) {
	case 0:
		// フェードイン開始
		ColorFadeIn(60);
		_step++;
		break;
	case 1:

		if (IsColorFade() == 0) {
			// フェードイン終了
			ColorFadeOut(0, 0, 0, 60);
			_step++;
		}
		break;
	case 2:

		if (IsColorFade() == 0) {
			// フェードアウト終了
			SceneBase* scene = new SceneGameTitle();
			ChangeScene(scene);
		}
		break;
	}

}

void SceneGameLogo::Draw() {
	DrawGraph(0, 0, _cgBg, FALSE);


}
