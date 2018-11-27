//#pragma once
#include "cocos2d.h"

#ifndef PLAYER_H_
#define PLAYER_H_

USING_NS_CC;

class Player : public Sprite
{
	float _duration;
	bool _remove;
public:
	static Player *create();
	Player();
	~Player();
	void update(float);
	float getduration() { return _duration; }
	void marktoremove();
	bool istoremove() { return _remove; }
};


#endif