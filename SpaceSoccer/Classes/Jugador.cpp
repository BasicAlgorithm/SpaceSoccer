#include "Jugador.h"


static Jugador *instance = nullptr;

Jugador * Jugador::create()
{
	Jugador* ret = new (std::nothrow) Jugador;
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
	_vivo = false;
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

Jugador::~Jugador()
{
}

void Jugador::update(float dt)
{
	
}


