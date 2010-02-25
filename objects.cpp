#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "objects.h"
#include "engine.h"
#include "states.h"

using namespace std;

//Planet
Planet::Planet(Bilde* bilde) {
	this->bilde = bilde;
	this->state.x = 0;
	this->state.y = 0;
	this->state.VelX = 0;
	this->state.VelY = 0;
	this->state.masse = 0;
	this->radius = 64;
}

void Planet::move(int timeDelta){
	state.VelX += aX*timeDelta/1000.0;
	state.VelY += aY*timeDelta/1000.0;
	state.x += state.VelX*timeDelta/1000.0;
	state.y += state.VelY*timeDelta/1000.0;
}

void Planet::render(SDL_Surface* screen, GameState* state) {
	this->bilde->applyTo(screen, state->metersToPixelsX(this->state.x)-radius/2,state->metersToPixelsY(this->state.y)-radius/2);
}

void Planet::setPos(double x, double y){
	this->state.x = x;
	this->state.y = y;
}

void Planet::setVel(double x, double y){
	this->state.VelX = x;
	this->state.VelY = y;
}

void Planet::setMasse(double masse){
	this->state.masse = masse;
}

void Planet::setRadius(int radius){
	this->radius = radius;
}

bool Planet::pointIsIn(int x, int y, GameState* state) {
	int pixlerX = state->metersToPixelsX(this->state.x);
	int pixlerY = state->metersToPixelsY(this->state.y);
	if ((x < pixlerX+radius/2) && (x > pixlerX-radius/2) && (y < pixlerY+radius/2) && (y > pixlerY-radius/2)){
		return true;
	}
	return false;
}

//Integrasjon for å mer nøyaktig enn Eulers finne fart og posisjon:

//Gamlemåten
/*void Planet::addForce(Planet* planet, double gravConst){
	double lenX = this->x-planet->x;
	double lenY = this->y-planet->y;
	double len = sqrt(pow(lenX,2.0)+pow(lenY,2.0));
	double a = (-gravConst * planet->masse/pow(len, 2.0));
	if (abs(a) < 0.1) {
		aX += a*lenX/len;
		aY += a*lenY/len;
	}
}*/

/*void Planet::integrate(const std::vector<Planet*> planets, double gravConst, double dt){
	Derivative a = evaluate(0.0f, Derivative(),planets, gravConst);
	Derivative b = evaluate(dt*0.5f, a,planets, gravConst);
	Derivative c = evaluate(dt*0.5f, b,planets, gravConst);
	Derivative d = evaluate(dt, c,planets, gravConst);

	const double dxdt  = 1.0f/6.0f * (a.dx  + 2.0f*(b.dx  + c.dx)  + d.dx);
	const double dydt  = 1.0f/6.0f * (a.dy  + 2.0f*(b.dy  + c.dy)  + d.dy);
	const double dvxdt = 1.0f/6.0f * (a.dvx + 2.0f*(b.dvx + c.dvx) + d.dvx);
	const double dvydt = 1.0f/6.0f * (a.dvy + 2.0f*(b.dvy + c.dvy) + d.dvy);

	this->state.x    += dxdt * dt;
	this->state.y    += dydt * dt;
	this->state.VelX += dvxdt * dt;
	this->state.VelY += dvydt * dt;
}

Derivative Planet::evaluate(double dt, const Derivative &d, const std::vector<Planet*> planets, double gravConst){
	state.x = this->state.x + d.dx*dt;
	state.y = this->state.y + d.dy*dt;
	state.VelX = this->state.VelX + d.dvx*dt;
	state.VelY = this->state.VelY + d.dvy*dt;

	Derivative output;
	output.dx = state.VelX;
	output.dy = state.VelY;
	//Vec a = acceleration(planets, gravConst); 
	//output.dvx = a.x;
	//output.dvy = a.y;
	return output;
}

Vec Planet::acceleration(double x, double y, double VelX, double VelY, const std::vector<Planet*> planets, double gravConst){
	Vec aVec;
	aVec.x = 0;
	aVec.y = 0;
	for (vector<Planet*>::const_iterator iter = planets.begin(); iter != planets.end(); ++iter) {
		Planet* planet = (*iter);
		if (planet != this) {
			double lenX = this->state.x-planet->state.x;
			double lenY = this->state.y-planet->state.y;
			double len = sqrt(pow(lenX,2.0)+pow(lenY,2.0));
			double a = (-gravConst * planet->state.masse/pow(len, 2.0));
			aVec.x += a*lenX/len;
			aVec.y += a*lenY/len;
		}
	}
	return aVec;
}*/

//Derivasjon, forsøk 2
vector<Derivative> evaluate(const vector<State> &initial, double dt, const std::vector<Derivative> &d, double gravConst){
	vector<State> state;
	state.resize(initial.size());
	for (vector<State>::size_type i = 0; i != initial.size(); ++i) {
		state[i].x = initial[i].x + d[i].dx*dt;
		state[i].y = initial[i].y + d[i].dy*dt;
		state[i].VelX = initial[i].VelX + d[i].dvx*dt;
		state[i].VelY = initial[i].VelY + d[i].dvy*dt;
		state[i].masse = initial[i].masse;
	}
	vector<Derivative> output;
	output.resize(initial.size());
	vector<Vec> a = acceleration(state, gravConst);
	for (vector<State>::size_type i = 0; i != initial.size(); ++i) {
		output[i].dx = state[i].VelX;
		output[i].dy = state[i].VelY;
		output[i].dvx = a[i].x;
		output[i].dvy = a[i].y;
	}
	return output;
}

vector<Vec> acceleration(const vector<State> &state, double gravConst){
	vector<Vec> out;
	out.resize(state.size());
	for (vector<State>::size_type i = 0; i != state.size(); ++i) {
		for (vector<State>::size_type j = 0; j != state.size(); ++j) {
			if (i != j) {
				double lenX = state[i].x-state[j].x;
				double lenY = state[i].y-state[j].y;
				double len = sqrt(pow(lenX,2.0)+pow(lenY,2.0));
				double a = (-gravConst * state[j].masse/pow(len, 2.0));
				out[i].x += a*lenX/len;
				out[i].y += a*lenY/len;
			}
		}
	}
	return out;
}

void integrate(const vector<Planet*> &planets, double gravConst, double dt){
	vector<State> state;
	state.resize(planets.size());
	vector<Derivative> empty;
	empty.resize(planets.size());
	for (vector<Planet*>::size_type i = 0; i != planets.size(); ++i) {
		state[i] = planets[i]->state;
		empty[i] = Derivative();
	}
	vector<Derivative> a = evaluate(state, 0.0f, empty, gravConst);
	vector<Derivative> b = evaluate(state, dt*0.5f, a, gravConst);
	vector<Derivative> c = evaluate(state, dt*0.5f, b, gravConst);
	vector<Derivative> d = evaluate(state, dt, c, gravConst);
	for (vector<Planet*>::size_type i = 0; i != planets.size(); ++i) {
		const double dxdt = 1.0f/6.0f * (a[i].dx + 2.0f*(b[i].dx + c[i].dx) + d[i].dx);
		const double dydt = 1.0f/6.0f * (a[i].dy + 2.0f*(b[i].dy + c[i].dy) + d[i].dy);
		const double dvxdt = 1.0f/6.0f * (a[i].dvx + 2.0f*(b[i].dvx + c[i].dvx) + d[i].dvx);
		const double dvydt = 1.0f/6.0f * (a[i].dvy + 2.0f*(b[i].dvy + c[i].dvy) + d[i].dvy);

		planets[i]->state.x = planets[i]->state.x + dxdt * dt;
		planets[i]->state.y = planets[i]->state.y + dydt * dt;
		planets[i]->state.VelX = planets[i]->state.VelX + dvxdt * dt;
		planets[i]->state.VelY = planets[i]->state.VelY + dvydt * dt;
	}
}