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
	cout << argc << endl;
	for (int i = 0; i < argc; i++) {
		cout << "'" << argv[i] << "'" << endl;
	}
#ifdef skjermsparer
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