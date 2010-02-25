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


#include <iostream>
#include <vector>
#include <cmath>
#include "states.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//#include "SDL_draw.h"
#include "SDL/SDL_gfxPrimitives.h"

using namespace std;

//PlanetState
PlanetState::PlanetState() {
	this->gravConst = 6.67e-11;
	this->metersPrPixel = 434564860;
	this->gmSecPrRlSec = 5000000;
	this->drawing = false;
	sunBilde = new Bilde("sun.jpg");
	mercuryBilde = new Bilde("mercury.jpg");
	venusBilde = new Bilde("venus.jpg");
	earthBilde = new Bilde("earth.png");
}

void PlanetState::addPlanet(Planet* planet) {
	planets.push_back(planet);
}

void PlanetState::handle_event(SDL_Event* event) {
	if ((event->type == SDL_MOUSEBUTTONDOWN) && (event->button.button == SDL_BUTTON_RIGHT)) {
		for (vector<Planet*>::iterator iter = planets.begin(); iter != planets.end(); ++iter) {
			Planet* planet = (*iter);
			if (planet->pointIsIn(event->button.x, event->button.y, this)) {
				delete planet;
				planets.erase(iter);
				break;
			}
		}
	}
	if ((event->type == SDL_MOUSEBUTTONDOWN) && (event->button.button == SDL_BUTTON_LEFT)) {
		drawStartX = event->button.x;
		drawStartY = event->button.y;
		drawEndX = drawStartX+1;
		drawEndY = drawStartY+1;
		drawing = true;
	}
	if ((event->type == SDL_MOUSEMOTION) && drawing){
		drawEndX = event->motion.x;
		drawEndY = event->motion.y;
	}
	if ((event->type == SDL_MOUSEBUTTONUP) && (event->button.button == SDL_BUTTON_LEFT)) {
		drawEndX = event->button.x;
		drawEndY = event->button.y;
		drawing = false;
		Planet* planet = new Planet(earthBilde);
		planet->setPos(pixelsToMetersX(drawStartX),pixelsToMetersY(drawStartY));
		planet->setVel((drawEndX-drawStartX)*100,(drawEndY-drawStartY)*100);
		planet->setMasse(5.97e24);
		this->addPlanet(planet);
	}
	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.sym){
			case SDLK_c: {
				for (vector<Planet*>::iterator iter = planets.begin(); iter != planets.end(); ++iter) {
					delete (*iter);
				}
				planets.clear();
			}
		}
	}
}

void PlanetState::logic(int timeDelta) {
	timeDelta = timeDelta * this->gmSecPrRlSec;
	integrate(planets, gravConst, (double)(timeDelta/1000.0));
}

void PlanetState::render(SDL_Surface* screen){
	for (vector<Planet*>::iterator iter = planets.begin(); iter != planets.end(); ++iter) {
		(*iter)->render(screen, this);
	}
	Uint32 c_white = SDL_MapRGB(screen->format, 255,255,255);
	if (drawing) {
		aalineColor(screen, drawStartX, drawStartY,drawEndX,drawEndY,c_white);
		earthBilde->applyTo(screen, drawStartX-32, drawStartY-32);
	}
}

//Denne konverterer mellom meter og pixels, og gjør også slik at 0,0 blir midt på skjermen.
int PlanetState::metersToPixelsX(double meters) {
	return (int)(((meters/metersPrPixel) + width/2)+0.5);
}

int PlanetState::metersToPixelsY(double meters) {
	return (int)(((meters/metersPrPixel) + height/2)+0.5);
}

double PlanetState::pixelsToMetersX(int pixels) {
	return (pixels-width/2)*this->metersPrPixel;
}

double PlanetState::pixelsToMetersY(int pixels){
	return (pixels-height/2)*this->metersPrPixel;
}
