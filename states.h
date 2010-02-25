#ifndef GUARD_STATES_H
#define GUARD_STATES_H

#include "engine.h"
#include "objects.h"
#include <vector>

class PlanetState : public GameState {
private:
	std::vector<Planet*> planets;
	double metersPrPixel;
	double gravConst;	//Gravitasjonskonstanten
	int gmSecPrRlSec; //Hvor mange sekunder simulasjon pr sekund i virkeligheten
	int drawStartX, drawStartY;
	int drawEndX, drawEndY;
	bool drawing;
public:
	PlanetState();
	void addPlanet(Planet* planet);	
	void handle_event(SDL_Event* event);
	void logic(int timeDelta);
	void render(SDL_Surface* screen);
	int metersToPixelsX(double meters);
	int metersToPixelsY(double meters);
	double pixelsToMetersX(int pixels);
	double pixelsToMetersY(int pixels);
	Bilde* earthBilde;
	Bilde* mercuryBilde;
	Bilde* sunBilde;
	Bilde* venusBilde;
};

#endif