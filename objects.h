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


#ifndef GUARD_OBJECTS_H
#define GUARD_OBJECTS_H

#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "engine.h"

struct Derivative { //Takk til http://gafferongames.com/game-physics/integration-basics/
	double dx;
	double dy;
	double dvx;
	double dvy;
};

struct State {
	double x;
	double y;
	double VelX;
	double VelY;
	double masse;
};

struct Vec {
	double x;
	double y;
};

class Planet {
private:
	//double x,y; //midtpunkt
	//double VelX, VelY; //Fart
	double aX, aY; //Akselerasjon
	int radius;
	Bilde* bilde;
public:
	State state;
	Planet(Bilde* bilde);
	void setPos(double x, double y);
	void setVel(double x, double y);
	void setMasse(double masse);
	void setRadius(int radius);
	//timeDelta er i Simulerings-sekunder
	void move(int timeDelta);
	void render(SDL_Surface* screen, GameState* state);
	bool pointIsIn(int x, int y, GameState* state);
	//Derivasjon for å få fart slik riktig
	/*void integrate(const std::vector<Planet*> planets, double gravConst, double dt);
	Derivative evaluate(double dt, const Derivative &d, const std::vector<Planet*> planets, double gravConst);
	Vec acceleration(double x, double y, double VelX, double VelY, const std::vector<Planet*> planets, double gravConst);*/
};

//Derivasjon
std::vector<Derivative> evaluate(const std::vector<State> &initial, double dt, const std::vector<Derivative> &d, double gravConst);
std::vector<Vec> acceleration(const std::vector<State> &state, double gravConst);
void integrate(const std::vector<Planet*> &planets, double gravConst, double dt);



#endif
