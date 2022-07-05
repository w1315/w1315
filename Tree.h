#pragma once
#ifndef TREE
#define TREE
#include"Tree_Node.h"
#include<iostream>
using namespace std;

template <class T>
class Tree
{
public:
	Tree(T Root_Data);
	~Tree();
	void  Left_Rotate(Tree_Node<T>* Current_Node);//左旋
	void  Right_Rotate(Tree_Node<T>* Current_Node);//右旋
	void  Insert_Node(T Insert_Data);//插入节点
	void Fix_Tree(Tree_Node<T>* Current_Node); //插入后调整树的结构
	int  Delete_Node(T Delete_Data);//删除节点
	void  Erase_Node(Tree_Node<T>* Node_Del); //清除该节点相关的所有信息
	
	Tree_Node<T>* Find_Success_Node(Tree_Node<T>* Current_Node);
	Tree_Node<T>* Root_Node;
};
#endif // TREE
