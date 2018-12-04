#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
	//Event* mouseEvento;
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
};

#endif // STARTSCENE__
