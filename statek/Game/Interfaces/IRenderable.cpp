//
// Created by wysocki on 24/07/2017.
//

#include <Game.h>
#include "IRenderable.h"

IRenderable::IRenderable() {
	Game::GetGame()->SubscribeRender(this);
}

IRenderable::~IRenderable() {
	Game::GetGame()->UnSubscribeRender(this);
}