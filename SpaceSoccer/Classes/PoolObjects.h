//#pragma once
#include "cocos2d.h"

#ifndef POOLOBJECTS_H_
#define POOLOBJECTS_H_

USING_NS_CC;

template<typename T>
class PoolObjects
{
public:
	void create(double x, double y,
		double xVel, double yVel, int lifetime);

	void animate()
	{
		for (int i = 0; i < POOL_SIZE; i++)
		{
			particles_[i].animate();
		}
	}

private:
	static const int POOL_SIZE = 4;
	T particles_[POOL_SIZE];
};

template<typename T>
void PoolObjects<T>::create(double x, double y, double xVel, double yVel, int lifetime)
{
	// Find an available particle.
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!particles_[i].inUse())
		{
			particles_[i].init(x, y, xVel, yVel, lifetime);
			return;
		}
	}
}

#endif