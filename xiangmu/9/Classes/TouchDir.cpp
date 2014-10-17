#include "TouchDir.h"

TouchDir * TouchDir::create(Vec2 beginPoint, Vec2 endPoint)
{
    TouchDir * touchDir = new TouchDir();
	if(touchDir && touchDir->init(beginPoint,endPoint))
	{
		touchDir->autorelease();
		return touchDir;
	}
	CC_SAFE_DELETE(touchDir);
	return nullptr;
}

bool TouchDir::init(Vec2 beginPoint, Vec2 endPoint)
{
   this->_beginPoint = beginPoint;
   this->_endPoint = endPoint;
   judgeDriection();
   return true;
}

Driection TouchDir::judgeDriection()
{
	float height = _beginPoint.y - _endPoint.y;
	float width = _beginPoint.x - _endPoint.x;
	float tanValue = height / width; 
	if(height < 0)
	{
	     if(tanValue > 1 || tanValue < -1)
		 {
			 return JUMP;
		 }
		 else if(tanValue < 1 && tanValue > 0)
		 {
			 return RIGHTFARSKILL;
		 }
		 else if(tanValue > -1 && tanValue < 0)
		 {
			 return LEFTFARSKILL;
		 }
	}
	else if(height >= 0)
	{
	     if(tanValue > 1 || tanValue < -1)
		 {
			 return NEARSKILL;
		 }
		 else if(tanValue < 1 && tanValue > 0)
		 {
			 return LEFTFARSKILL;
		 }
		 else if(tanValue > -1 && tanValue < 0)
		 {
			 return RIGHTFARSKILL;
		 }
	}
}