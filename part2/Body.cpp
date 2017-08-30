#include "Body.h"

//===============================================================
// Default constructor
//===============================================================

Body::Body()
{

}

void Body::initBody(double px, double py, double vx, double vy, double mass)
{
	this->px = px;
	this->py = py;
	this->vx = vx;
	this->vy = vy;
	this->mass = mass;
}

//===============================================================
// Update velocity, then update position using fx and fy
// Using a = F/m and v += a (Change velocity by amount equal to
// accelaration)
//===============================================================

void Body::update(double step)
{
	vx += step * (fx/mass);
	vy += step * (fy/mass);
	px += step * vx;
	py += step * vy;
}


//===============================================================
// May The Force be With You
// =========================
// Calculate the force acting between Body y and Body x(this)
// This calculates the interaction between two particles
// F = Gm1m2/r^2
//===============================================================

void Body::calcForce(Body y, double& fx, double&fy)
{
	double dx = px - y.px;
	double dy = py - y.py;
	double dist = sqrt(dx*dx + dy*dy);	
	double Force = - (G * mass * y.mass)/(dist*dist);
	fx = Force * dx/dist;
	fy = Force * dy/dist;
}

void Body::Print(int i)
{
	std::cout <<"Body:" << i <<   "   x:" << px << "   y:" << py << '\n';
}








