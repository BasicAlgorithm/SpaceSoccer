#include "CreditsScene.h"
#include "StartScene.h"

USING_NS_CC;

Scene* CreditsScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CreditsScene::create();
	scene->addChild(layer);

	return scene;
}

bool CreditsScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("creditsscene.png");
	background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

	this->addChild(background, 0);
	
	layer_menu();

	return true;
}

void CreditsScene::layer_menu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

		float x = origin.x + 48.0;
		float y = origin.y + visibleSize.height-30.00;


	auto return_item = MenuItemImage::create(
		"returnoff_creditsscene.png",
		"returnon_creditsscene.png",
		CC_CALLBACK_1(CreditsScene::Go_Start_Scene, this));

		return_item->setPosition(Vec2(x, y));

	auto exit_item = MenuItemImage::create(
			"exitoff_creditsscene.png",
			"exiton_creditsscene.png",
			CC_CALLBACK_1(CreditsScene::menuCloseCallback, this));


		y -= exit_item->getContentSize().height;
		exit_item->setPosition(Vec2(x, y));


	/////////////////////////////////////////////////////
	///////////// CREANDO EL MENU DE OPCIONES  //////////
	/////////////////////////////////////////////////////
	auto menu = Menu::create(return_item, exit_item, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);
}

void CreditsScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

void CreditsScene::Go_Start_Scene(cocos2d::Ref* pSender)
{
	const auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

