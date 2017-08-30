// g++ part3.cpp -o part3 

#include "BHTree.h"
#include "Tree.h"
#include <chrono>

double Random();
#define N 1000
#define INTERVAL 1e4
#define ITERATIONS 10000
#define ERR 0.5
#define RADIUS 1e18

int main()
{
    Body bodies[N];
    for(int i=0;i<N;++i)
    {
        bodies[i].v.x = 0;
        bodies[i].v.y = 0;
        bodies[i].p.x = Random();
        bodies[i].p.y = Random();
        bodies[i].mass = Random();
    }    
    
    std::chrono::steady_clock::time_point  start = std::chrono::steady_clock::now();
    
    for(int t=0;t<ITERATIONS;++t)
    {
        Tree tree(RADIUS);
        for(int i=0;i<N;++i)        {
            tree.insert(&bodies[i]);
        }
        
        for(int j=0;j<N;++j)
        {
            tree.updateForce(&bodies[j]);
            bodies[j].update(INTERVAL);
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i)
        bodies[i].print(i);

    std::cout << "Time taken for simulation is "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " milliseconds\n"; 
    return 0;
}

double Random()
{
    return 1e16*exp(-1.8)*(.5 - rand());
}

