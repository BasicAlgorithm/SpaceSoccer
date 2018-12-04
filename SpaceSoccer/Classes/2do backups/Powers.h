//#pragma once
#include "cocos2d.h"

#ifndef POWERS_H_
#define POWERS_H_

USING_NS_CC;

class Powers : public Sprite
{
	float _duration;
	bool _remove;
public:
	static Powers *create();
	Powers();
	~Powers();
	void update(float);
	float getduration() { return _duration; }
	void marktoremove();
	bool istoremove() { return _remove; }
};


#endif