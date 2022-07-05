#pragma once
#ifndef TREE_NODE
#define TREE_NODE
#include<iostream>
using namespace std;
template <class T>
class Tree_Node
{
public:
	Tree_Node(T Data_In);
	~Tree_Node();
	Tree_Node* Left_Child;
	Tree_Node* Right_Child;
	Tree_Node* Parent_Node;
public:
	T Data;
	int Color_Tag;
};

#endif // !TREE_NODE
