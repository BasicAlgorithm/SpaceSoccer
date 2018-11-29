//#pragma once
#include "cocos2d.h"
#include "GeneralObjects.h"

#ifndef POWERS_H_
#define POWERS_H_

USING_NS_CC;

class Powers : public GeneralObjects, public Sprite
{
	float _duration;
	bool _remove;
public:
	static Powers *create();
	Powers();
	~Powers();
	void update(float);
	float getduration() override { return _duration; }
	void marktoremove();
	bool istoremove() { return _remove; }
	void behavior() override {}
};


#endif