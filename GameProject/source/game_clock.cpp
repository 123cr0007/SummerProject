//#include "game_clock.h"
//
//
//
//G_SHOCK::G_SHOCK()
//{
//
//}
//
//G_SHOCK::~G_SHOCK()
//{
//
//}
//
////引数（TimeCounter* time・ゲームのフレーム数 ）
//int G_SHOCK::GameTimer_Main(TimeCounter* time,int fps,int mode)
//{
//	if(time->t_count == fps)
//	{
//		time->t_count = 0;//1秒になったので戻す０に戻す
//		time->game++;//内部タイマーを一秒経過させる
//		switch(mode)
//		{
//		case 0: 
//		{
//			DigitalClock(&digitalclock);//デジタル時計用の処理
//			break; 
//		}
//		case 1:
//		{
//			//enpty
//		}
//		}
//		
//	} 
//	time->t_count++;
//		
//	return 0;//正常終了
//	
//}
//
//int G_SHOCK::DigitalClock(DigitalTimeCounter* digitalclock)
//{
//	digitalclock->seconds++;//デジタル表記時計を一秒経過させる
//
//	if(digitalclock->seconds == 10)
//	{
//		digitalclock->seconds = 0;
//		digitalclock->ten_seconds++;
//	}
//	if(digitalclock->ten_seconds == 6)
//	{
//		digitalclock->ten_seconds = 0;
//		digitalclock->minutes++;//一分の経過を記録する
//	}
//	if(digitalclock->minutes == 10)
//	{
//		digitalclock->minutes = 0;
//		digitalclock->ten_minutes++;//一時間も経過を記録する
//	}
//	if(digitalclock->ten_minutes == 6)
//	{
//		digitalclock->ten_minutes = 0;
//		digitalclock->hours++;//一時間も経過を記録する
//	}
//	return 0;
//}
//		