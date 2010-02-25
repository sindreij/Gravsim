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
