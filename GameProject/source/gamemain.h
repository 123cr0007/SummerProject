#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "scenebase.h"
#include "GamePad.h"

// 他のcppでも使いたいグローバル変数は、ヘッダファイルでextern宣言する

// ゲーム情報
extern GamePad	gPad;			// ゲームパッドの情報


void ChangeScene(SceneBase* scene);	// Sceneを変更する

void ChangeScene(SceneBase* scene);	// Sceneを変更する
void ColorMask(int colorR, int colorG, int colorB, int colorA);		// カラーマスクの指定

// 指定の色にフェードアウト（カラーマスク使用, alpha=255にする）
void ColorFadeOut(int colorR, int colorG, int colorB, int frames);

// 現在のカラーマスクからフェードイン（カラーマスク使用, alpha=0にする）
void ColorFadeIn(int frames);

// フェードインアウトは終了したか？
// 戻り値: 1 = フェード中, 0 = フェード終了(もしくは開始前)
int IsColorFade();

void GameMain();	// gamemain.cpp に実体を記述

