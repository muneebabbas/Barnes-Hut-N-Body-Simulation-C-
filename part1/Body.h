#include <cmath>
#include <iostream>
static const double G = 6.67300E-11;
class Body{
public:
	double px, py, vx, vy, fx, fy, mass;
	Body();
	void initBody(double px, double py, double vx, double vy, double mass);
	void update(double step);
	void calcForce(Body y);
	double distance(double x1, double y1, double x2, double y2);
	void Print(int);
};