#include "Powers.h"



Powers * Powers::create()
{
	Powers* ret = new (std::nothrow) Powers;
	ret->initWithFile("max.png");
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

Powers::Powers()
{
	_duration = 0.0f;
	_remove = false;
}


Powers::~Powers()
{
}

void Powers::update(float dt)
{
	_duration += dt;
}

void Powers::marktoremove()
{
	_remove = true;
}
