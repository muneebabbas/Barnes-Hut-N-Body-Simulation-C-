#ifndef TREE_H
#define TREE_H
#include "BHTree.h"
#include "Body.h"
#include <vector>
#include <thread>
#include <shared_mutex>
#define THREADS 4
std::shared_timed_mutex writeL; 
class Tree
{
public:
	BHTree *root;
	double threshold, step;
public:
	Tree(){}
	Tree(double l){
		Pos mid;
		mid.x = 0;
		mid.y = 0;
		root=new BHTree(mid,l);
	}

	void initQuads()
	{
		// Initialize all quadrants as each thread will get one quadrant
		double len = root->length/2;
		root->NW = new BHTree(root->nw(), len);
		root->NE = new BHTree(root->ne(), len);
		root->SW = new BHTree(root->sw(), len);
		root->SE = new BHTree(root->se(), len);
	}
	void insert(std::vector<Body> &bodies){

		// std::thread takes its arguments by value. You can get reference semantics back by using std::reference_wrapper:
		//std::thread newThread(session, &sock, std::ref(logger));
		// http://stackoverflow.com/questions/21048906/stdthread-pass-by-reference-calls-copy-constructor


		std::thread nwThread(&Tree::threadInsert, this, root->NW, std::ref(bodies));
		std::thread neThread(&Tree::threadInsert, this, root->NE, std::ref(bodies));
		std::thread swThread(&Tree::threadInsert, this, root->SW, std::ref(bodies));
		std::thread seThread(&Tree::threadInsert, this, root->SE, std::ref(bodies));

		nwThread.join();
		neThread.join();
		swThread.join();
		seThread.join();

	}

	void threadInsert(BHTree* quad, std::vector<Body>& bodies)
	{
		// Each thread gets a quadrant and the complete vector of bodies
		// If a body falls into threads respective quadrant, it inserts the body

		int N = bodies.size();
		for (int i =0; i < N; ++i)
		{
			if (quad->in(bodies[i].p.x, bodies[i].p.y))
			{
				quad->insert(&bodies[i]);
			{
				std::lock_guard<std::shared_timed_mutex> WriteLock(writeL);
				root->xmid = (bodies[i].p.x * bodies[i].mass + root->xmid*root->mass)/(root->mass+bodies[i].mass);
				root->ymid = (bodies[i].p.y * bodies[i].mass + root->ymid*root->mass)/(root->mass+bodies[i].mass);
				root->mass += bodies[i].mass;
			}
		}
		
		}
	}

	void parallelForce(Body *body)
	{
		body->resetF();
		root->updateForce(body);
	}

	void parallelForce(std::vector<Body>& bodies)
	{
		int x = 0;
		int N = bodies.size() - 1;
		int work = N/THREADS;

		std::vector<std::thread> th (THREADS);
		for (int i = 0; i < THREADS -1 ; ++i)
		{	

			th[i] = std::thread(&Tree::threadForce, this, x, x + work, std::ref(bodies));
		}

		th[THREADS] = std::thread(&Tree::threadForce, this, x, N , std::ref(bodies));
		
		for (auto &t : th)
		{
			t.join();
		}
	}

	void threadForce(int low, int high, std::vector<Body>& bodies)
	{
		for (int i = low; i <= high; ++i)
		{
			root->updateForce(&bodies[i]);
			bodies[i].update(step);
		}
	}
};

#endif
