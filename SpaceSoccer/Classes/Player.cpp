#include "Player.h"



Player * Player::create()
{
	Player* ret = new (std::nothrow) Player;
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

Player::Player()
{
	_duration = 0.0f;
	_remove = false;
}


Player::~Player()
{
}

void Player::update(float dt)
{
	_duration += dt;
}

void Player::marktoremove()
{
	_remove = true;
}
