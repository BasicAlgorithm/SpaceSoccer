#include "Jugador.h"


static Jugador *instance = nullptr;

Jugador * Jugador::create()
{
	
	auto ret = new (std::nothrow) Jugador;
	ret->initWithFile("jugadorA.png");
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


Jugador::Jugador()
{
	_vivo = true;
}

Jugador* Jugador::getinstance()
{
	if (!instance) {
		instance = new (std::nothrow) Jugador;
		instance->init();	
	}
	return instance;
	
}

bool Jugador::init()
{
	
	_vivo = true;
	return true;
}

void Jugador::inittouch()
{
	/*
	auto escuchador = EventListenerTouchAllAtOnce::create();
	escuchador->onTouchesBegan = [](Touch*touchdejugador, Event*eventojugador) {return true; };
	escuchador->onTouchesMoved = CC_CALLBACK_2(Jugador::moverjugador, this);
	escuchador->onTouchesEnded = [=](Touch*touchdejugador, Event*eventojugador) {};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);
	*/
	
	auto escuchador = EventListenerTouchOneByOne::create();
	escuchador->onTouchBegan = [](Touch*touchdejugador, Event*eventojugador) {return true; };
	escuchador->onTouchMoved = CC_CALLBACK_2(Jugador::moverjugador, this);
	escuchador->onTouchEnded = [=](Touch*touchdejugador, Event*eventojugador) {};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);

	/*auto listener = EventListenerMouse::create();
	listener->onMouseDown = [](cocos2d::Event* event) {
		EventMouse* eventmouse = dynamic_cast<EventMouse*>(event);
		eventmouse->getMouseButton();

	}*/

}

void Jugador::moverjugador(Touch* touchdejugador, Event* eventojugador)
{
	auto posiciontouch = touchdejugador->getLocation();
	if (this->getBoundingBox().containsPoint(posiciontouch)) {
		this->setPositionX(posiciontouch.x);
		this->setPositionY(posiciontouch.y);
	}
}


Jugador::~Jugador()
{
}

void Jugador::update(float dt)
{
	_vivo = true;
}


