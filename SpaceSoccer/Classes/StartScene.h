#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
	cocos2d::Event* mouseEvent; //DO NOTHING
	cocos2d::Sprite* _ss;
	static cocos2d::Scene* createScene();
	bool init() override;
	
	void layer_menu();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void Go_Game(cocos2d::Ref * pSender);
	void Go_Credits_Scene(cocos2d::Ref * pSender);
	void menuReloadCallback(cocos2d::Ref* pSender);

	void prueba();

	CREATE_FUNC(StartScene);
};

#endif // START SCENE__
