//Copyright 2010 Sindre Johansen
//
//This file is part of Gravsim.
//
//Gravsim is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//Gravsim is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with Gravsim.  If not, see <http://www.gnu.org/licenses/>.



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
