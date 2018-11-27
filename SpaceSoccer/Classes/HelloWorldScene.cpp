#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"

using namespace CocosDenshion;

USING_NS_CC;

//FABRICA DE ESCENAS
Scene* HelloWorld::createScene()
{
	HelloWorld* ret = new (std::nothrow) HelloWorld();
	if (ret) {
		ret->autorelease();
		ret->init();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
	//return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// AQUI SE INICIALIZA LA ESCENA
//SE AGREGAN TODOS LOS COMPONENTES GRAFICOS

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
	
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // CREANDO ICONO PARA CERRAR JUEGO

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

	//CREANDO ICONO PARA REINICIAR JUEGO

	_reloaditem = MenuItemImage::create(
		"restart.png",
		"restartselected.png",
		CC_CALLBACK_1(HelloWorld::menuReloadCallback, this));

	if (_reloaditem == nullptr ||
		_reloaditem->getContentSize().width <= 0 ||
		_reloaditem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - _reloaditem->getContentSize().width / 2 - _reloaditem->getContentSize().width;
		float y = origin.y + _reloaditem->getContentSize().height / 2;
		_reloaditem->setPosition(Vec2(x, y));
	}

    // CREANDO EL MENU DE OPCIONES 
    auto menu = Menu::create(closeItem, _reloaditem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
	//AñADIENDO IMAGEN BACKGROUND
	Sprite* Background = Sprite::create("background.png");
	Background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	float scale = visibleSize.width / Background->getContentSize().width;
	Background->setScale(scale);
	this->addChild(Background, 0);

    //CREANDO LABEL SCORE

    _scorelabel = Label::createWithTTF("SCORE", "fonts/Marker Felt.ttf", 24);
    if (_scorelabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
		_scorelabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - _scorelabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(_scorelabel, 1);
    }

	auto label1 = Label::createWithTTF("UCSP CCOMP1", "fonts/Marker Felt.ttf", 12);
	if (label1 == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label1->setPosition(Vec2(origin.x + visibleSize.width * 3/4,
			origin.y + visibleSize.height - (4*label1->getContentSize().height)));

		// add the label as a child to this layer
		this->addChild(label1, 1);
	}

    // CREANDO IMAGEN MEDIA
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}

	//CREAMOS SONIDO AL PRESIONAR UNA FIGURA
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

 }


//REINCIO DE JUEGO
void HelloWorld::menuReloadCallback(cocos2d::Ref* pSender)
{
	_score = 0;
	_lifes = 5;
}

//TOCAR Y SOUND 
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (_lifes <= 0) {
		return true;
	}
	for (Player* player : _players) {
		Size size = player->getContentSize();
		if ((player->getPositionX() - size.width / 2 <= touch->getLocation().x) && (touch->getLocation().x <= player->getPositionX() + size.width / 2) &&
			(player->getPositionY() - size.height / 2 <= touch->getLocation().y) && (touch->getLocation().y <= player->getPositionY() + size.height / 2)) {
			player->marktoremove();
			_score++;
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("qwe.mp3", false, 1.0f, 1.0f, 1.0f);
		}
	}
	return true;
}

void HelloWorld::update(float dt)
{
	Vector<Player*> toremove;
	Vector<Node*> list = getChildren();
	for (Player* player : _players) {
		if (player->getduration() > _maxduration&&_lifes > 0) {
			toremove.pushBack(player);
			_lifes--;
		}
		if (player->istoremove()){
			toremove.pushBack(player);
		}
	}
	for (Player* sprite : toremove) {
		sprite->removeFromParent();
		_players.eraseObject(sprite);
	}

	//_scorelabel->create();
	char txt[100];
	sprintf(txt, "Score %d - Lifes %d", _score, _lifes);
	_scorelabel->setString(txt);
	if (_lifes == 0) {
		_reloaditem->setVisible(true);
		return;
	}
	_maxduration -= 0.01f;
	if (_maxduration < 0.3f) {
		_maxduration = 0.3f;
	}
	if (RandomHelper::random_int(0, 100) == 1 || _players.size() == 0) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto player = Player::create();
		float x = RandomHelper::random_real(origin.x, visibleSize.width);
		float y = RandomHelper::random_real(origin.y, origin.y + (visibleSize.height*0.6f));
		player->setPosition(Vec2(x, y));
		addChild(player, 1);
		_players.pushBack(player);

	}
}
