// g++ Body.cpp part1.cpp -0 part1
// ./part1
#include "Body.h"
#include <chrono>

double myRandom();
#define N 1000
#define INTERVAL 1e11
#define ITERATIONS 1000
int main()
{
	// Initialzie N Body objects
	Body* Bodies = new Body[N];
	for (int i = 0; i < N; ++i)
	{
		double px = myRandom();
		double py = myRandom();
		double vx = myRandom();
		double vy = myRandom();
		double mass = myRandom();	
		Bodies[i].initBody(px, py, vx, vy, mass);

	}


	// Iterate the number times the simulation has to run
	std::chrono::steady_clock::time_point  start = std::chrono::steady_clock::now();

	for (int i = 0; i < ITERATIONS; ++i)
	{
		// Iterate all bodies
		for (int i = 0 ; i < N; ++i)
		{
			Bodies[i].fx = 0;
			Bodies[i].fy = 0;

			// For every ith body, interact with every body 
			for (int j = 0; j < N; ++j)
			{
				if (i != j)
				{
					Bodies[i].calcForce(Bodies[j]);
				}
			}
		}

		// Update positions after all the forces have been calculated
		for (int i = 0; i < N; ++i)
			Bodies[i].update(INTERVAL);
	}

	// print the x,y position of all bodies

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();


	for (int i = 0; i < N; ++i)
		Bodies[i].Print(i);
	
	std::cout << "simulation took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms.\n"; 	

	delete[] Bodies;

}




double myRandom()
{
	return 1e18*exp(-1.8)*(.5 - rand());
}