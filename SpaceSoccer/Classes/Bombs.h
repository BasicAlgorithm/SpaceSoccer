//#pragma once
#include "cocos2d.h"

#ifndef BOMBS_H_
#define BOMBS_H_

USING_NS_CC;

class Bombs : public Sprite
{
	float _duration;
	bool _remove;
public:
	static Bombs *create();
	Bombs();
	~Bombs();
	void update(float);
	float getduration() { return _duration; }
	void marktoremove();
	bool istoremove() { return _remove; }
};


#endif