//#pragma once
#include "cocos2d.h"

#ifndef JUGADOR_H_
#define JUGADOR_H_

USING_NS_CC;

//bool islive(bool live, bool(*state)());
//bool state();

class Jugador : public Sprite
{
	bool _vivo;
	Jugador();
public:
	
	static Jugador* getinstance();
	static Jugador *create();
	bool init() override;
	void inittouch();
	void moverjugador(Touch*, Event*);
	//void islive(bool);

	//friend bool islive(bool live, bool(*state)());
	//friend bool state();
	
	~Jugador();
	void update(float);

};


#endif