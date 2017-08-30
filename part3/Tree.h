#ifndef TREE_H
#define TREE_H
#include "BHTree.h"
#include "Body.h"

class Tree
{
private:
	BHTree *root;
public:
	Tree(){}
	Tree(double l){
		Pos mid;
		mid.x = 0;
		mid.y = 0;
		root=new BHTree(mid,l);
	}
	void insert(Body* body){
		root->insert(body);
	}
	void updateForce(Body *body)
	{
		body->resetF();
		root->updateForce(body);
	}
};

#endif