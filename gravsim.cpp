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


#include <vector>
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "objects.h"
#include "states.h"
#include "engine.h"

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;

int main(int argc, char* argv[]) {
	cout
	<<"Gravsim  Copyright (C) 2010  Sindre Johansen" << endl
	<<"This program comes with ABSOLUTELY NO WARRANTY." << endl
	<<"This is free software, and you are welcome to redistribute it" << endl
	<<"under certain conditions." << endl;

#ifdef skjermsparer
	cout << "test" << endl;
	cout << argv[1];
	if (argc > 1 && !strcmp(argv[1], "/p"))
		return 0;  //Gidder ikke kjøre preview
#endif
	World* world = new World(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, "GravSim");
	PlanetState* planetState = new PlanetState();

	Planet* sun = new Planet(planetState->sunBilde);
	sun->setMasse(1.9891e30);
	planetState->addPlanet(sun);

	Planet* mercury = new Planet(planetState->mercuryBilde);
	mercury->setPos(0,69816900000);
	mercury->setVel(38878,0);
	mercury->setMasse(3.3e23);
	planetState->addPlanet(mercury);

	Planet* venus = new Planet(planetState->venusBilde);
	venus->setPos(0,108942109000);
	venus->setVel(34801,0);
	venus->setMasse(4.8685e24);
	planetState->addPlanet(venus);

	Planet* earth = new Planet(planetState->earthBilde);
	earth->setPos(0,152097701000);
	earth->setVel(29306,0);
	earth->setMasse(5.97e24);
	planetState->addPlanet(earth);

	world->changeState(planetState);
	world->gameloop();
	return 0;
}
