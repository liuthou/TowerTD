#include "BoundingBox.h"

bool BoundingBox::init()
{
  return true;
}

bool BoundingBox::conductBoundingBox(Vec2 spWordPoint, float spWith, Vec2 sp2WordPoint, float spWith2)
{
	if(sp2WordPoint.x > spWordPoint.x)
	{
	    if((sp2WordPoint.x - spWordPoint.x) <= (spWith + spWith2))
		{
		   return true;
		}
	}
	else
	{
	    if((-sp2WordPoint.x + spWordPoint.x) <= (spWith + spWith2))
		{
		   return true;
		}
	}
	return false;
}
