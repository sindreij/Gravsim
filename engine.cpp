#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "engine.h"



using namespace std;

//World

World::World(int width, int height, int bpp, string caption) {
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);
	TTF_Init();
	SDL_WM_SetCaption(caption.c_str(), caption.c_str());
	this->screenWidth = width;
	this->screenHeight = height;
	this->bpp = bpp;
	fps = 100;
#ifdef skjermsparer
	fullscreen = true;
#else
	fullscreen = false;
#endif
	currentState = NULL;
	setVideoMode();
}

void World::changeState(GameState* newState) {
	currentState = newState;
	newState->setSize(width, height);
}

void World::gameloop() {
	SDL_Event* event;
	event = new SDL_Event();
	quit = false;
	timer.restart();
	while (quit == false) {
		while (SDL_PollEvent(event)) {
			this->handle_event(event);
			currentState->handle_event(event);
		}
		int timeDelta = timer.tick(fps);
		currentState->logic(timeDelta);
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
		currentState->render(screen);
		SDL_Flip(screen);
	}
}

void World::handle_event(SDL_Event* event) {
	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.sym){
			case SDLK_f:
				fullscreen = !fullscreen;
				setVideoMode();
				break;
			case SDLK_ESCAPE:
				quit = true;
				break;
		}
	}
	if (event->type == SDL_QUIT)
		quit = true;
}

void World::setVideoMode() {
	if (fullscreen){
		this->width = 1024;
		this->height = 768;
		screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE ^ SDL_FULLSCREEN);
	} else {
		this->width = screenWidth;
		this->height = screenHeight;
		screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);
	}
	if (currentState != NULL) currentState->setSize(width, height);
}

//Bilde
Bilde::Bilde(string filename) {
#ifdef skjermsparer
	filename = "C:\\Documents and Settings\\6715\\Mine dokumenter\\src\\c++\\gravsim\\Release\\data\\" + filename;
#else
	filename = "data\\" + filename;
#endif
	surface = SDL_DisplayFormatAlpha(IMG_Load(filename.c_str()));
}

void Bilde::applyTo(SDL_Surface* dest, int x, int y) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(this->surface, NULL, dest, &offset);
}

//GameState
void GameState::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

//Timer
Timer::Timer() {
	lastTick = SDL_GetTicks();
}

void Timer::restart() {
	lastTick = SDL_GetTicks();
}

Uint32 Timer::tick(Uint32 fps){
	if ((SDL_GetTicks() - lastTick) < (1000/fps))
		SDL_Delay((1000/fps)-(SDL_GetTicks() - lastTick));
	Uint32 delta = SDL_GetTicks() - lastTick; 
	lastTick = SDL_GetTicks();
	if (delta > 100) delta = 0; //For � slippe planeter som hopper hit og dit hvis det lagger
	return delta;
}