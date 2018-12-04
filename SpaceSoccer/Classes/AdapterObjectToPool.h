//#pragma once
#include "cocos2d.h"
#include "GeneralObjects.h"

#ifndef ADAPTEROBJECTTOPOOL_H_
#define ADAPTEROBJECTTOPOOL_H_

USING_NS_CC;

//template<typename T>
class AdapterObjectToPool
{
public:
	AdapterObjectToPool(GeneralObjects* objrec)
		: framesLeft_(0)
	{}

	void init(double x, double y,
		double xVel, double yVel, int lifetime)
	{
		x_ = x; y_ = y;
		xVel_ = xVel; yVel_ = yVel;
		framesLeft_ = lifetime;
	}

	void animate()
	{
		if (!inUse()) return;

		framesLeft_--;
		x_ += xVel_;
		y_ += yVel_;
	}

	bool inUse() const { return framesLeft_ > 0; }

private:
	int framesLeft_;
	double x_, y_;
	double xVel_, yVel_;
};

#endif