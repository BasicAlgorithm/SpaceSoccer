//#pragma once
#include "cocos2d.h"

#ifndef JUGADOR_H_
#define JUGADOR_H_

USING_NS_CC;


class Jugador : public Sprite
{
	bool _vivo;
public:
	//static Jugador *instance;
	Jugador();
	static Jugador* getinstance();
	static Jugador *create();
	bool init();
	
	~Jugador();
	void update(float);

};


#endif