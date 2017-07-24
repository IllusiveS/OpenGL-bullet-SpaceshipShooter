//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_GAME_H
#define STATEK_GAME_H


#include <statek/Graphics/Renderer.h>
#include <statek/Graphics/Window.h>
#include <Game/Camera.h>
#include <list>
#include <Physics/PhysicsEngine.h>

class IRenderable;
class Actor;
class ITickable;
class IPhysicsable;

class Game {
	//SINGLETON
public:
	static Game * GetGame();
	static void Prepare();
	static void Finish();
private:
	static Game * gameSingleton;
	Game();
	~Game();
	
public:
	Camera * camera;
    Window * window;
    Renderer * renderer;
	PhysicsEngine * engine;

public:
    void Begin();
    void Loop();
    void End();
	
	void RestartScene();

public://Zapisywanie się aktorów
	void SubscribeActor(Actor * actor);
	void SubscribeTick(ITickable * tick);
	void SubscribePhysics(IPhysicsable * phi);
	void SubscribeRender(IRenderable * render);
	
	void UnSubscribeActor(Actor * actor);
	void UnSubscribeTick(ITickable * tick);
	void UnSubscribePhysics(IPhysicsable * phi);
	void UnSubscribeRender(IRenderable * render);
	
private:
	void UpdateInput();
	void UpdateTick(float delta);
	void UpdatePhysics(float delta);
	void Render();
	
	void RemoveUnusedActors();

private:
	std::list<ITickable *> ticks;
	std::list<Actor *> actors;
	std::list<Actor *> actorsToBeRemoved;
	
	bool isStart = false;
};


#endif //STATEK_GAME_H
