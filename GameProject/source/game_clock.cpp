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
////�����iTimeCounter* time�E�Q�[���̃t���[���� �j
//int G_SHOCK::GameTimer_Main(TimeCounter* time,int fps,int mode)
//{
//	if(time->t_count == fps)
//	{
//		time->t_count = 0;//1�b�ɂȂ����̂Ŗ߂��O�ɖ߂�
//		time->game++;//�����^�C�}�[����b�o�߂�����
//		switch(mode)
//		{
//		case 0: 
//		{
//			DigitalClock(&digitalclock);//�f�W�^�����v�p�̏���
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
//	return 0;//����I��
//	
//}
//
//int G_SHOCK::DigitalClock(DigitalTimeCounter* digitalclock)
//{
//	digitalclock->seconds++;//�f�W�^���\�L���v����b�o�߂�����
//
//	if(digitalclock->seconds == 10)
//	{
//		digitalclock->seconds = 0;
//		digitalclock->ten_seconds++;
//	}
//	if(digitalclock->ten_seconds == 6)
//	{
//		digitalclock->ten_seconds = 0;
//		digitalclock->minutes++;//�ꕪ�̌o�߂��L�^����
//	}
//	if(digitalclock->minutes == 10)
//	{
//		digitalclock->minutes = 0;
//		digitalclock->ten_minutes++;//�ꎞ�Ԃ��o�߂��L�^����
//	}
//	if(digitalclock->ten_minutes == 6)
//	{
//		digitalclock->ten_minutes = 0;
//		digitalclock->hours++;//�ꎞ�Ԃ��o�߂��L�^����
//	}
//	return 0;
//}
//		