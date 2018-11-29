//#pragma once
#include "cocos2d.h"

#ifndef GENERALOBJECTS_H_
#define GENERALOBJECTS_H_

USING_NS_CC;

class GeneralObjects
{
	float _duration;
	bool _remove;
public:
	
	GeneralObjects();
	~GeneralObjects();
	virtual float getduration() = 0;
	virtual void behavior() = 0;
};


#endif