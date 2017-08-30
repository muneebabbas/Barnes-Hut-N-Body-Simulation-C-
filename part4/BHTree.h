#ifndef BHTREE_H
#define BHTREE_H
#include "Body.h"
#define ERR 0.5
#define NorthWest 0
#define NorthEast 1
#define SouthWest 2
#define SouthEast 3
class BHTree{
public:
	Body* body;
	BHTree* NW;
	BHTree* NE;
	BHTree* SW;
	BHTree* SE;	
	Pos mid;
	double xmid, ymid, mass, length;
	BHTree(){}
	BHTree(Pos m, double len)
	{
		NW = NULL;
		NE = NULL;
		SW = NULL;
		SE = NULL;
		body = NULL;
		mass = 0;
		mid = m;
		length = len;
	}

	bool isExternal(){
		if (this->NW==NULL && this->NE==NULL && this->SW==NULL && this->SE==NULL)
			return true;
		else
			return false;	
	}

	bool in(double x, double y)
	{
		bool lim1= (x <= mid.x+length/2 && x >= mid.y-length/2);
		bool lim2=(y <= mid.y+length/2 && y >= mid.y-length/2);
		return lim1 && lim2;
	}	

//===============================================================
// Return a NW Quadrant
//===============================================================
	Pos nw()
	{	
		Pos r;
		double sub = this->length/4.0;
		r.x = xmid - sub;
		r.y = ymid + sub;
		return r;
	}

//===============================================================
// Return a NE Quadrant
//===============================================================
	Pos ne()
	{	
		Pos r;
		double sub = this->length/4.0;
		r.x = xmid + sub;
		r.y = ymid + sub;
		return r;
	}

//===============================================================
// Return a SW Quadrant
//===============================================================

	Pos sw()
	{	
		Pos r;
		double sub = this->length/4.0;
		r.x = xmid + sub;
		r.y = ymid - sub;
		return r;
	}

//===============================================================
// Return a SE Quadrant
//===============================================================
	Pos se()
	{	
		Pos r;
		double sub = this->length/4.0;
		r.x = xmid - sub;
		r.y = ymid - sub;
		return r;
	}

	void insert(Body* b)
	{
		if (body == NULL)
		{
			body = b;
			mass = b->mass;
			xmid = b->p.x;
			ymid = b->p.y;
			return;
		}

		int quadrant;
	
		

		if (!isExternal())
		{

			if(NW->in(b->p.x,b->p.y))
				quadrant = NorthWest;
			else if(NE->in(b->p.x,b->p.y))
				quadrant = NorthEast;
			else if(SW->in(b->p.x,b->p.y))
				quadrant = SouthWest;
			else if(SE->in(b->p.x,b->p.y))
				quadrant = SouthEast;		
						
			xmid = (b->p.x* b->mass + xmid*mass)/(mass+b->mass);
			ymid = (b->p.y* b->mass+ ymid*mass)/(mass+b->mass);
			mass += b->mass;

			switch (quadrant){
				case NorthWest:
				NW->insert(b);
				break;

				case NorthEast:
				NE->insert(b);
				break;

				case SouthWest:
				SW->insert(b);
				break;

				case SouthEast:
				SW->insert(b);
				break;
			}
		}
		else if (isExternal())
		{
			// External means that none of the quadrants have a body and therefore all of them are NULL
			// We can allocate all of them and check which quadrant is the correct one to insert

			double len = length/2;
			NW = new BHTree(nw() , len);
			NE = new BHTree(ne() , len);
			SW = new BHTree(sw() , len);
			SE = new BHTree(se() , len);

			if(NW->in(body->p.x,body->p.y))
				quadrant = NorthWest;
			else if(NE->in(body->p.x,body->p.y))
				quadrant = NorthEast;
			else if(SW->in(body->p.x,body->p.y))
				quadrant = SouthWest;
			else if(SE->in(body->p.x,body->p.y))
				quadrant = SouthEast;


			switch (quadrant){
				case NorthWest:
				NW->insert(body);
				break;

				case NorthEast:
				NE->insert(body);
				break;

				case SouthWest:
				SW->insert(body);
				break;

				case SouthEast:
				SW->insert(body);
				break;
			}

			insert(b);			
		}


	}

	void updateForce(Body* b)
	{
		if (isExternal())
		{
			if (b!=body && body != NULL)
			{
				Force f = b->calcForce(b->p.x, b->p.y, body->p.x, body->p.y, b->mass,body->mass);
				b->addF(f);
			}
		}
		else
		{
			double dist = b->distance(b->p.x, b->p.y, xmid, ymid);
			if (length/dist < ERR)
			{
				Force f = b->calcForce(b->p.x, b->p.y, xmid, ymid, b->mass, mass);
				b->addF(f);				
			}
			else
			{
				NW->updateForce(b);
				NE->updateForce(b);
				SW->updateForce(b);
				SE->updateForce(b);				
			}
		}
	}
};

#endif