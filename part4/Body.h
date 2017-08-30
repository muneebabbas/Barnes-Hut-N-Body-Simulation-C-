#ifndef BODY_H
#define BODY_H
#include <iostream>
#include <cmath>
static const double G = 6.67300E-11;

class Force{
public:
	double x;
	double y;
};

class Pos{
public:
	double x;
	double y;
};

class Vel{
public:
	double x;
	double y;
};

class Body{
public:
	Force f;
	Pos p;
	Vel v;
	double mass;

	Body(){}
	void setF(double x, double y){
		f.x = x; f.y = y;
	}	
	void update(double step)
	{
		v.x += step * (f.x/mass);
		v.y += step * (f.y/mass);
		p.x += step * v.x;
		p.y += step * v.y;		
	}
	Force calcForce(double xa, double ya, double xb, double yb, double ma, double mb)
	{
		double dx = xa - xb;
		double dy = ya - yb;
		double dist = sqrt(dx*dx + dy*dy);
		double F = - (G * ma * mb)/(dist*dist);
		Force retval;
		retval.x = F * dx/dist;
		retval.y = F * dy/dist;
		return retval;	
	}

	void resetF(){
		f.x = 0; f.y = 0;
	}
	void addF(Force F){
		f.x += F.x;
		f.y += F.y;
	}
	double distance (double x1,double y1,double x2,double y2)
	{
		double x=(x1-x2);
		double y=(y1-y2);
		return sqrt(x*x + y*y);
	}
	void print(int i)
	{
		std::cout<<"Body:" << i << "  x:"<<p.x<<"  y:"<<p.y<<'\n';
	}	

};

#endif