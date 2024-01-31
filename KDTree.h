#pragma once
#include "LinkedList.cpp"
#include "Store.h"
#include "Queue.cpp"`
#include "Neighborhood.h"
#include <math.h>
#include "Merge.cpp"
#include "Vector.cpp"
//node--------------------
class KDTree;
class TreeNode {
	friend class KDTree;
public:
	TreeNode(Node<Store>* data,int depth, TreeNode* parent = nullptr, TreeNode* left = nullptr, TreeNode* right = nullptr);


private:
	Node<Store>* data;
	int depth;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	
};


//tree--------------------
class KDTree {

public:
	KDTree();
	void push(Node<Store>* data);
	void BFSPrint();
	Node<Store>* deleteByCoo(int x, int y);
	void searchNeighborhood(Neighborhood neighborhood);
	Node<Store>* findTheClosestPoint( int x, int y);
	void printAllNodesInRange(int x, int y, float R);
	void construct(Node<Store>**,int size);
	void clear();
	
private:
	void _clear(TreeNode* node);
	TreeNode* _construct( int depth, Node<Store>**,int size);
	float distPower2(TreeNode* node1,int x,int y);
	void _printAllNodesInRange(TreeNode* curr, float R2, int x, int y);
	void _findTheClosestPoint(TreeNode* curr, Pair<TreeNode*, float>& target, int x, int y);
	void _searchNeighborhood(TreeNode* curr,Neighborhood neighborhood);
	TreeNode* minNode(TreeNode* node1,TreeNode* node2,int dim);//compares 2 nodes based on the given dim;
	TreeNode* minNode(TreeNode* node1, TreeNode* node2,TreeNode* node3, int dim);//compares  3nodes based on the given dim;
	TreeNode* findSmallest(TreeNode* curr, int dim/*0 for x and 1 for y*/);

	void deleteByAdr(TreeNode* node);
	TreeNode* find(TreeNode* curr,int x, int  y,int depth);
	TreeNode* root;
	void recursivePush(TreeNode* curr, Node<Store>* data, int depth);
	int size;

};