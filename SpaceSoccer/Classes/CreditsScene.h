#ifndef CREDITSSCENE_H
#define CREDITSSCENE_H

#include "cocos2d.h"

class CreditsScene : public cocos2d::Scene
{
public:
	cocos2d::Event* mouseEvent; //DO NOTHING
	//Sprite* _ss;
	static cocos2d::Scene* createScene();
	bool init() override;
	
	void layer_menu();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void Go_Start_Scene(cocos2d::Ref * pSender);

	CREATE_FUNC(CreditsScene);
};

#endif // START SCENE__
