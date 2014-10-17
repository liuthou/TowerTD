#ifndef __GLOBALINFO_H_
#define __GLOBALINFO_H_
//Enemy相关
#define  SPEED 200
#define  STEP 64//敌人每移动一步的距离是地图块的边长
#define STEPTIME1 0.5
//HealthData相关
#define  DATASTEP 64//正常文件每移动一步的距离是地图块的边长
#define DATASTEPTIME 0.5//正常文件没走一步需要的时间
//攻击特效相关
struct attackEffect{
	int lowspeedtime;
	int frozentime;
	int firetime;
};

#endif