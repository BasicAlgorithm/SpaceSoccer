#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Powers.h"
#include "Jugador.h"
#include "cocos2d.h"
#include "Bombs.h"
#include "ArrayT.h"


class HelloWorld : public cocos2d::Scene
{
	Vector <Powers*>  _powers;
	Vector <Bombs*>   _bombs;
	//Jugador			  _player;
	Label*			  _scorelabel;
	Label*			  _gameover;
	MenuItemImage*	  _reloadItem;
	int				  _score;
	int				  _lifes;
	float			  _maxduration;
public:
    static cocos2d::Scene* createScene();

	bool init() override;
    
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuReloadCallback(cocos2d::Ref* pSender);

	//FUNCION PARA LOS TOUCH Y SONIDOS
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void update(float dt);

	void addbombs();

	void inicializarfisica(Sprite* sprite);

	void layermenu();
    
    // implement the "static create()" method manually
    //CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
