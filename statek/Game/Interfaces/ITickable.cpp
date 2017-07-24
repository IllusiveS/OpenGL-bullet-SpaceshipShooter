//
// Created by wysocki on 24/07/2017.
//

#include <Game.h>
#include "ITickable.h"

ITickable::ITickable() {
	Game::GetGame()->SubscribeTick(this);
}

ITickable::~ITickable() {
	Game::GetGame()->UnSubscribeTick(this);
}
