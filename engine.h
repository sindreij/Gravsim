#ifndef GUARD_ENGINE_H
#define GUARD_ENGINE_H

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


class GameState {
protected:
	int width, height;
public:
	virtual void handle_event(SDL_Event* event) = 0;
	virtual void logic(int timeDelta) = 0;
	virtual void render(SDL_Surface* screen) = 0;
	virtual int metersToPixelsX(double meters) = 0;
	virtual int metersToPixelsY(double meters) = 0;
	void setSize(int width, int height);
};

class Timer {
private:
	int lastTick;
public:
	Timer();
	void restart();
	Uint32 tick(Uint32 fps);
};

//Hovedklassen, som passer på hvilken state vi har
//og også initialiserer alt for oss.
class World { 
private:
	GameState* currentState;
	SDL_Surface* screen;
	int width, height;
	int screenWidth, screenHeight;
	int bpp;
	bool fullscreen;
	int fps;
	bool quit;
public:
	World(int width, int height, int bpp, std::string caption); //Må kalles først
	void changeState(GameState* newState);
	Timer timer;
	void gameloop();
	void handle_event(SDL_Event* event);
	void setVideoMode();
};

class Bilde {
private:
	SDL_Surface* surface;
public:
	Bilde(std::string filename);
	void applyTo(SDL_Surface* dest, int x, int y);
};

#endif