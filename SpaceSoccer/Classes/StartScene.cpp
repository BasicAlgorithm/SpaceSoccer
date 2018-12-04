#include "StartScene.h"

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
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto mainlogo = Sprite::create("fireball.png");
	mainlogo->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));

	this->addChild(mainlogo, 0);


	auto maintitle = Sprite::create("spacesoccer.png");
	maintitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
								origin.y + visibleSize.height - maintitle->getContentSize().height/2));

	this->addChild(maintitle, 0);

	auto ss = Sprite::create("power.png");
	ss->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - ss->getContentSize().height / 2));
	//ss->setPosition(Vec2(,);
	this->addChild(ss, 1);

	cocos2d::log("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"); /*HARD_TESTING*/

	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [](cocos2d::Event* event) {

		
			EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
			mouseEvent->getMouseButton();
			cocos2d::log("ENTRO A DOWN"); /*HARD_TESTING*/
			/*std::stringstream message;
			message << "Mouse event: Button: " << mouseEvent->getMouseButton() << "pressed at point (" <<
				mouseEvent->getLocation().x << "," << mouseEvent->getLocation().y << ")";
			MessageBox(message.str().c_str(), "Mouse Event Details");*/

		
	};

	listener->onMouseMove = [](cocos2d::Event* event) {
		// Cast Event to EventMouse for position details like above
		cocos2d::log("Mouse moved event");
	};

	listener->onMouseScroll = [](cocos2d::Event* event) {
		cocos2d::log("Mouse wheel scrolled");
	};

	listener->onMouseUp = [](cocos2d::Event* event) {
		cocos2d::log("Mouse button released");
	};

	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	

	return true;
}