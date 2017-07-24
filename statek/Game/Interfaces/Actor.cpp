//
// Created by wysocki on 24/07/2017.
//

#include <Game.h>
#include "Actor.h"

Actor::Actor() {
	Game::GetGame()->SubscribeActor(this);
}

void Actor::Destroy(){
	Game::GetGame()->UnSubscribeActor(this);
}

Actor::~Actor(){

}