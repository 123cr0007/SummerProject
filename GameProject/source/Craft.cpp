#include"scenegamemain.h"
#include"scenegameresult.h"
#include"gamemain.h"
int SceneGameMain::ChangeArmType(int j)	
{
	

	arm[1].ArmPULv = arm[0].ArmPULv;

	ArmLv = arm[1].ArmPULv;
	return -1;
}