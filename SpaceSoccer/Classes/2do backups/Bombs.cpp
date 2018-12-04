#include "Bombs.h"



Bombs * Bombs::create()
{
	Bombs* ret = new (std::nothrow) Bombs;
	ret->initWithFile("bomba.png");
	//ret->setTag(TAG_DOG);
	ret->scheduleUpdate();
	if (ret) {
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

Bombs::Bombs()
{
	_duration = 0.0f;
	_remove = false;
}


Bombs::~Bombs()
{
}

void Bombs::update(float dt)
{
	_duration += dt;
}

void Bombs::marktoremove()
{
	_remove = true;
}
