//#pragma once
#include "cocos2d.h"
#include "GeneralObjects.h"

#ifndef BOMBS_H_
#define BOMBS_H_

USING_NS_CC;

class Bombs : public GeneralObjects, public Sprite
{
	float _duration;
	bool _remove;
public:
	static Bombs *create();
	Bombs();
	~Bombs();
	void update(float);
	float getduration() override { return _duration; }
	void marktoremove();
	bool istoremove() { return _remove; }
	void behavior() override {}
};


#endif