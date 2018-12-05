#include "StartScene.h"
#include "HelloWorldScene.h"
#include "CreditsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backgroundmusic.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backgroundmusic.mp3", true);
	//CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.01f);
	
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto mainlogo = Sprite::create("fireball.png");
	mainlogo->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));

	this->addChild(mainlogo, 0);


	auto maintitle = Sprite::create("spacesoccer.png");
	maintitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
								origin.y + visibleSize.height - maintitle->getContentSize().height/2));

	this->addChild(maintitle, 0);

	_ss = Sprite::create("power.png");
	_ss->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - _ss->getContentSize().height / 2));
	////ss->setPosition(Vec2(,);
	this->addChild(_ss, 1);

	cocos2d::log("INSIDE OF INIT N TIMES"); /*HARD_TESTING*/

	layer_menu();


								/*EVENTS OF MOUSE'S TOUCHES*/



	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [](cocos2d::Event* event) {
			EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
			mouseEvent->getMouseButton();

			cocos2d::log("ONMOUSEDOWN x = %f, y=%f",mouseEvent->getCursorX(), mouseEvent->getCursorY());
	};

	listener->onMouseMove = [](cocos2d::Event* event) {
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		mouseEvent->getMouseButton();
		cocos2d::log("ONMOUSEMOVE x = %f, y=%f", mouseEvent->getCursorX(), mouseEvent->getCursorY());

	};

	listener->onMouseScroll = [](cocos2d::Event* event) {
		cocos2d::log("ON MOUSE SCROLL");
	};

	listener->onMouseUp = [](cocos2d::Event* event) {
		cocos2d::log("ON MOUSE UP");
	};

	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	return true;
}

void StartScene::layer_menu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

		float x = origin.x + visibleSize.width/2;
		float y = origin.y + visibleSize.height*0.25;

	///////////////////////////////////////////////////////////
	//////////// START GAME ICON  //////////
	///////////////////////////////////////////////////////////

	auto start_item = MenuItemImage::create(
		"startoff_startscene.png",
		"starton_startscene.png",
		CC_CALLBACK_1(StartScene::Go_Game, this));

		start_item->setPosition(Vec2(x, y));

	////////////////////////////////////////////////////////
	//////////// EXIT GAME ICON  //////////
	////////////////////////////////////////////////////////

	auto exit_item = MenuItemImage::create(
		"exitoff_startscene.png",
		"exiton_startscene.png",
		CC_CALLBACK_1(StartScene::menuCloseCallback, this));

	
	y -= exit_item->getContentSize().height;
	exit_item->setPosition(Vec2(x, y));
	
		////////////////////////////////////////////////////////
		//////////// CREDITS GAME ICON  //////////
		////////////////////////////////////////////////////////

		auto credits_item = MenuItemImage::create(
			"creditsoff_startscene.png",
			"creditson_startscene.png",
			CC_CALLBACK_1(StartScene::Go_Credits_Scene, this));

		y -= credits_item->getContentSize().height;
		credits_item->setPosition(Vec2(x, y));

	/////////////////////////////////////////////////////
	///////////// CREANDO EL MENU DE OPCIONES  //////////
	/////////////////////////////////////////////////////
	auto menu = Menu::create(start_item, exit_item, credits_item, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);
}

void StartScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

void StartScene::Go_Game(cocos2d::Ref* pSender)
{
	const auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

void StartScene::Go_Credits_Scene(cocos2d::Ref* pSender)
{
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto diagonal_ball = Sprite::create("diagonalball.png");
	diagonal_ball->setPosition(Vec2(origin.x - diagonal_ball->getContentSize().width,
							   origin.y - diagonal_ball->getContentSize().height));

	this->addChild(diagonal_ball, 0);

	const auto action = MoveBy::create(1, Vec2(2320.0, 1480.0));
	diagonal_ball->runAction(action);

	const auto scene = CreditsScene::createScene();
	//Director::getInstance()->pushScene(scene); other form
	Director::getInstance()->replaceScene(TransitionFade::create(5, scene));

}

void StartScene::prueba()
{
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto scale_ball = Sprite::create("scaleball.png");
	scale_ball->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));

	this->addChild(scale_ball, 0);

	const auto action = ScaleBy::create(2500, 2500);
	scale_ball->runAction(action);
}

