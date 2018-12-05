#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
//#include "Powers.h"
//#include "Jugador.h"

using namespace CocosDenshion;

USING_NS_CC;


Scene* HelloWorld::createScene()
{
	HelloWorld* scene = new (std::nothrow) HelloWorld();
	if (scene) {
		//scene->getPhysicsBody()->setGravityEnable(true);
		//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		scene->autorelease();
		scene->init();
		return scene;
	}
	else
	{
		CC_SAFE_DELETE(scene);
		return nullptr;
	}
	//return HelloWorld::create();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////// FUNCION QUE AYUDA A UBICAR PROBLEMA
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BUCLE PRINCIPAL
bool HelloWorld::init()
{
  
    if ( !Scene::init() )
    {
        return false;
    }

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.mp3", true);

	//////////////////////////////////////////////////
	//////////// CREATING MAIN PLAYER     //////////
	//////////////////////////////////////////////////

	auto player_a = Jugador::create();
	const float xj = visibleSize.width - player_a->getContentSize().width;
	//float xj = visibleSize.width /2;
	const float yj = visibleSize.height / 2;
	player_a->setPosition(Vec2(xj,yj));
	//inicializarfisica(_JugadorA);
	this->addChild(player_a, 1);	
	
	////////////////////////////////////////////////////
	//////////// ADDING IMAGE BACKGROUND  //////////
	////////////////////////////////////////////////////

	Sprite* Background = Sprite::create("background.png");
	Background->setAnchorPoint(Vec2::ZERO);
	Background->setPosition(0, 0);
	this->addChild(Background, 0);

	//////USANDO METODO ESCALAR
	//Background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//float scale = visibleSize.width / Background->getContentSize().width;
	//Background->setScale(scale); antes de addchild

    
	//////////////////////////////////////////////////////
	//////////////// CREATING LABEL SCORE  ////////////////
	//////////////////////////////////////////////////////

    _scorelabel = Label::createWithTTF("SCORE", "fonts/Marker Felt.ttf", 50);
    if (_scorelabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
		_scorelabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - _scorelabel->getContentSize().height));

        this->addChild(_scorelabel, 1);
    }

	auto testing = Label::createWithSystemFont("TESTING", "Karmatic Arcade", 100);
	//testing->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	testing->setPosition(Vec2(500.0,500.0));
	this->addChild(testing, 1);

	

	//////////////////////////////////////////////////
	//////////// CREATING POWERS ON DISPLAY  //////////
	//////////////////////////////////////////////////
	auto power = Powers::create();
	const float x = RandomHelper::random_real(origin.x, visibleSize.width);
	const float y = RandomHelper::random_real(origin.y, origin.y + (visibleSize.height*0.6f));
	power->setPosition(Vec2(x, y));
	this->addChild(power, 1);
	_powers.pushBack(power);

	
	cocos2d::log("ENTER TO INIT"); /*HARD_TESTING*/
	

	
	///////////////////////////////////////////////////////////////
	//////////// CREAMOS SONIDO AL PRESIONAR UNA FIGURA  //////////
	///////////////////////////////////////////////////////////////

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	///////////////////////////////////////////////////////////////
	//////////// OTROS  //////////
	///////////////////////////////////////////////////////////////
	layermenu();

	player_a->inittouch();
	//schedule(schedule_selector(HelloWorld::addbombs), 5.0f);
	addbombs();
	this->scheduleUpdate();	
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////  OPCION DE MENU - CERRAR JUEGO
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////  OPCION DE MENU - REINICIAR JUEGO
void HelloWorld::menuReloadCallback(cocos2d::Ref* pSender)
{
	_score = 0;
	_lifes = 20;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////  TOCAR Y SOUND 
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (_lifes <= 0) {
		return true;
	}
	for (Powers* power : _powers) {
		Size size = power->getContentSize();
		if ((power->getPositionX() - size.width / 2 <= touch->getLocation().x) && (touch->getLocation().x <= power->getPositionX() + size.width / 2) &&
			(power->getPositionY() - size.height / 2 <= touch->getLocation().y) && (touch->getLocation().y <= power->getPositionY() + size.height / 2)) {
			power->marktoremove();
			_score++;
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("qwe.wav", false, 1.0f, 1.0f, 1.0f);
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////  METODO UPDATE PARA ELIMINAR OBJETOS
void HelloWorld::update(float dt)
{
	cocos2d::log("INSIDE OF UPDATE");/*HARD_TESTING*/
	
	Vector<Powers*> toremove;
	Vector<Node*> list = getChildren();
	for (Powers* power : _powers) {
		if (power->getduration() > _maxduration && _lifes > 0) {
			toremove.pushBack(power);
			_lifes--;
		}
		if (power->istoremove()){
			toremove.pushBack(power);
		}
	}
	for (Powers* sprite : toremove) {
		sprite->removeFromParent();
		_powers.eraseObject(sprite);
	}
	char txt[50];
	sprintf(txt, "PLAYER A (%d) - PLAYER B (%d)", _score, _lifes);
	_scorelabel->setString(txt);
	if (_lifes == 0) {
			_reloadItem->setVisible(true);
		return;
	}
	_maxduration -= 0.01f;
	if (_maxduration < 0.3f) {
		_maxduration = 0.3f;
	}
	if (RandomHelper::random_int(0, 100) == 1 || _powers.size() == 0) {
		const auto visibleSize = Director::getInstance()->getVisibleSize();
		const Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto power = Powers::create();
		const float x = RandomHelper::random_real(origin.x, visibleSize.width);
		const float y = RandomHelper::random_real(origin.y, origin.y + (visibleSize.height*0.6f));
		power->setPosition(Vec2(x, y));
		addChild(power, 1);
		_powers.pushBack(power);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ANADIR BOMBAS
void HelloWorld::addbombs()
{
	auto director = Director::getInstance();
	auto size = director->getWinSize();
	Bombs* bomb = nullptr;
	for (int i = 0; i < 3; i++) {
		bomb = Bombs::create();
		bomb->setAnchorPoint(Vec2::ZERO);
		bomb->setPosition(CCRANDOM_0_1()*size.width, CCRANDOM_0_1()*size.height);
		//inicializarfisica(bomb);
		//Vec2 velocity(0, (CCRANDOM_0_1() + 0.2f)*-250);
		//bomb->getPhysicsBody()->setVelocity(velocity);
		_bombs.pushBack(bomb);
		this->addChild(bomb, 1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////// INICIALIZAR PHYSICS ENGINE
void HelloWorld::inicializarfisica(Sprite* sprite)
{
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	sprite->setPhysicsBody(body);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////// LAYER MENU
void HelloWorld::layermenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	////////////////////////////////////////////////////////
	//////////// CREANDO ICONO PARA CERRAR JUEGO  //////////
	////////////////////////////////////////////////////////

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
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}


	///////////////////////////////////////////////////////////
	//////////// CREANDO ICONO PARA REINICIAR JUEGO  //////////
	///////////////////////////////////////////////////////////

	_reloadItem = MenuItemImage::create(
		"restart.png",
		"restartselected.png",
		CC_CALLBACK_1(HelloWorld::menuReloadCallback, this));

	if (_reloadItem == nullptr ||
		_reloadItem->getContentSize().width <= 0 ||
		_reloadItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - _reloadItem->getContentSize().width / 2 - closeItem->getContentSize().width;
		float y = origin.y + _reloadItem->getContentSize().height / 2;
		_reloadItem->setPosition(Vec2(x, y));
	}


	/////////////////////////////////////////////////////
	///////////// CREANDO EL MENU DE OPCIONES  //////////
	/////////////////////////////////////////////////////
	auto menu = Menu::create(closeItem, _reloadItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);
}
