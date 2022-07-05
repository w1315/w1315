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
	void  Left_Rotate(Tree_Node<T>* Current_Node);//����
	void  Right_Rotate(Tree_Node<T>* Current_Node);//����
	void  Insert_Node(T Insert_Data);//����ڵ�
	void Fix_Tree(Tree_Node<T>* Current_Node); //�����������Ľṹ
	int  Delete_Node(T Delete_Data);//ɾ���ڵ�
	void  Erase_Node(Tree_Node<T>* Node_Del); //����ýڵ���ص�������Ϣ
	
	Tree_Node<T>* Find_Success_Node(Tree_Node<T>* Current_Node);
	Tree_Node<T>* Root_Node;
};
#endif // TREE
