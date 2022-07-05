#include"Tree_Node.h"

template <class T>
Tree_Node<T>::Tree_Node(T Data_In) :Data(Data_In), Color_Tag(0), Left_Child(NULL),Right_Child(NULL), Parent_Node(NULL)
{
	Data = Data_In;
	Color_Tag = 1;
}
template <class T>
Tree_Node<T> ::~Tree_Node()
{
	cout << "Îö¹¹º¯Êý" << endl;
}