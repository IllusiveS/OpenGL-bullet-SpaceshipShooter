//
// Created by wysocki on 22/07/2017.
//

#include <cstdio>
#include <glm/detail/type_mat.hpp>
#include <thread>
#include <chrono>
#include "windows.h"
#include "Game.h"
#include <Game/Interfaces/Actor.h>
#include <Game/Interfaces/ITickable.h>
#include <Game/GameElements/PlayerShip.h>
#include <Game/GameElements/AsteroidGenerator.h>

Game * Game::gameSingleton = nullptr;

Game *Game::GetGame() {
	return gameSingleton;
}

void Game::Prepare() {
	gameSingleton = new Game();
}

void Game::Begin() {

}

void Game::Loop() {
	double timePerFrame = 1000.0 / 60.f; // I am so sorry totalbiscuit
	double lastTime = glfwGetTime();
	int nbFrames = 0;
    do{
	    if(isStart){
		    PlayerShip::CreateShip();
		    new AsteroidGenerator();
		    isStart = false;
	    }
	    
	    
        double currentTime = glfwGetTime();
        nbFrames++;
	    double timePassed = currentTime - lastTime;
        if (true){ // If last prinf() was more than 1sec ago
            // printf and reset
            nbFrames = 0;
	        lastTime = currentTime;
	        double timeLeft = timePerFrame - timePassed;
	        //printf("%f ms/frame\n", timeLeft);
	        Sleep(timeLeft);
        }
	
	    engine->ProcessPhysics(timePassed);
	
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
	    UpdateTick(timePassed);
	    
	    RemoveUnusedActors();
	    
	    renderer->RenderAll(window, camera);
	    
        glfwSwapBuffers(window->window);
        glfwPollEvents();
	   

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window->window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window->window) == 0 );
}

void Game::End() {

}

Game::Game() {
	window = new Window();
	camera = new Camera(window);
	renderer = new Renderer();
	engine = new PhysicsEngine();
}

Game::~Game() {
	for(auto itr = actors.begin(); itr != actors.end(); itr++) {
		Actor * actor = *itr;
		delete actor;
	}
	delete camera;
	delete window;
	delete renderer;
	delete engine;
}

void Game::SubscribeActor(Actor *actor) {
	actors.push_back(actor);
}

void Game::SubscribeTick(ITickable *tick) {
	ticks.push_back(tick);
}

void Game::SubscribePhysics(IPhysicsable *phi) {
	engine->AddObject(phi);
}

void Game::SubscribeRender(IRenderable *render) {
	renderer->AddRenderable(render);
}

void Game::UnSubscribeActor(Actor *actor) {
	actorsToBeRemoved.push_back(actor);
}

void Game::UnSubscribeTick(ITickable *tick) {
	ticks.remove(tick);
}

void Game::UnSubscribePhysics(IPhysicsable *phi) {
	engine->RemoveObject(phi);
}

void Game::UnSubscribeRender(IRenderable *render) {
	renderer->RemoveRenderable(render);
}

void Game::UpdateInput() {

}

void Game::UpdateTick(float delta) {
	auto begin = ticks.begin();
	auto end = ticks.end();
	
	for(auto itr = begin;
	    itr != end;
	    itr++) {
		(*itr)->Tick(delta);
	}
	
}

void Game::UpdatePhysics(float delta) {

}

void Game::Render() {

}

void Game::RemoveUnusedActors() {
	for(auto itr = actorsToBeRemoved.begin(); itr != actorsToBeRemoved.end(); itr++) {
		Actor * actorToRemove = *itr;
		actors.remove(actorToRemove);
		delete actorToRemove;
	}
	actorsToBeRemoved.clear();
}

void Game::Finish() {
	delete gameSingleton;
}

void Game::RestartScene() {
	for(auto itr = actors.begin(); itr != actors.end(); itr++) {
		Actor * actor = *itr;
		actor->Destroy();
	}
	isStart = true;
}
