#include"Tree.h"

template <class T>
Tree<T> ::Tree(T Root_Data) :Root_Node(NULL)
{
	if (Root_Node == NULL)//判断是否存在根节点
	{
		//如果没有  new 一个根节点
		Root_Node = new Tree_Node<T>(Root_Data);
		Root_Node->Color_Tag = 0;//初始化根节点颜色为 黑色
	}
}

template <class T>
Tree<T> ::~Tree(){
}
/************************************************************************
函数功能：对当前节点进行左旋操作                                     
入口参数：左旋的当前节点
返回值：无
************************************************************************/
template<class T>
void Tree<T>::Left_Rotate(Tree_Node<T>* Current_Node)
{
	Tree_Node<T>* Parent = Current_Node->Parent_Node;//获取当前节点的父节点
	Tree_Node<T>* Right_Child = Current_Node->Right_Child;//获取当前节点的右节点
	Current_Node->Right_Child = Right_Child->Left_Child; // 当前节点的右节点下的左节点 连接到 当前节点的右节点 
	Right_Child->Parent_Node = Parent;//当前节点的右节点父节点 为 当前节点的父节点
	//情况一： 当前节点的父节点为空 设置 右节点为父节点
	if (Parent == NULL)
	{
		Root_Node = Right_Child;
	}
	//情况2：如果当前节点是它父节点的左孩子，则将当前节点的右节点设为“当前节点的父节点的左孩子”
	if (Current_Node == Parent->Left_Child)
	{
		Parent->Left_Child = Right_Child;
	}
	else {  //情况3：(当前节点是它父节点的右孩子) 将当前节点的右节点设为“当前节点的父节点的右孩子”
		Parent->Right_Child = Right_Child;
	}
	Right_Child->Left_Child = Current_Node;//将 “当前节点” 设为 “当前节点的右节点的左孩子”
	Current_Node->Parent_Node = Right_Child;//将 “当前节点的父节点” 设为 “当前节点的右节点”
}
/************************************************************************
函数功能：对当前节点进行右旋操作                                     
入口参数：右旋的当前节点
返回值：无
*************************************************************************/
template<class T>
void Tree<T>::Right_Rotate(Tree_Node<T>* Current_Node)
{
	Tree_Node<T>* Left_Child = Current_Node->Left_Child;//获取当前节点的左节点
	Tree_Node<T>* Parent = Current_Node->Parent_Node;//获取当前节点的父节点
	Current_Node->Left_Child = Left_Child->Right_Child;//将 “当前节点的左节点的右孩子” 设为 “当前节点的左孩子”
	Left_Child->Parent_Node = Current_Node;//将 “当前节点” 设为 “当前节点的左节点的右孩子的父亲”
	Left_Child->Parent_Node = Parent;//将 “当前节点的父亲” 设为 “当前节点的左节点的父亲”
	if (Current_Node == NULL)
	{
		Root_Node = Left_Child; // 情况1：如果 “y的父亲” 是空结点，则将x设为根结点
	}
	if (Current_Node == Parent->Right_Child) 
	{
		Parent->Left_Child = Left_Child;// 情况2：如果 y是它父结点的右孩子，则将x设为“y的父结点的左孩子”
	}
	else{
		Parent->Right_Child = Left_Child;// 情况3：(y是它父结点的左孩子) 将x设为“y的父结点的左孩子”
	}
	Current_Node->Parent_Node = Left_Child;// 将 “y” 设为 “x的右孩子”
	Left_Child->Parent_Node = Parent;// 将 “y的父结点” 设为 “x”
}
/************************************************************************
函数功能：向红黑树中插入一个节点                                     
入口参数：插入的数据
返回值：无
*************************************************************************/
/*************************************************************************
但插入结点是为什么是红色呢？理由很简单，红色在父结点（如果存在）为黑色结点时，
红黑树的黑色平衡没被破坏，不需要做自平衡操作。但如果插入结点是黑色，那么插入位
置所在的子树黑色结点总是多1，必须做自平衡。插入情况可以总结为下面这些：
%%%%%%%%%%
情景1：
红黑树为空树
最简单的一种情景，直接把插入结点作为根结点就行，但注意，根据红黑树性质2：根结点是黑色。所以还需要把插入结点设为黑色。
处理：

把插入结点作为根结点，并把结点设置为黑色。

情景2：
插入结点的Key已存在
插入结点的Key已存在，因为红黑树总保持平衡，在插入前红黑树已经是平衡的，那么把插入结点设置为将要替代的结点颜色，再把结点的值更新就完成插入了。
处理：

把z设为当前结点的颜色。
更新当前结点的值为插入结点的值。

情景3：
插入结点的父结点为黑结点
由于插入的结点是红色的，并不会影响红黑树的平衡，直接插入即可，无需做自平衡。
处理：

直接插入。
情景4：
插入结点的父结点为红结点
再次回想下红黑树的性质2：根结点是黑色。如果插入的父结点为红结点，那么该父结点不可能为根结点，所以插入结点总是存在祖父结点。这点很重要，因为后续的旋转操作需要祖父结点的参与。

情景4.1：
叔叔结点存在并且为红结点
从红黑树性质4可以确定，祖父结点为黑结点，因为不可以同时存在两个相连的红结点。那么此时该插入子树的红黑层数的情况是：黑红红。显然最简单的处理方式是把其改为：红黑红。如图5和图6所示。
处理：

将P和S设置为黑色（当前插入结点I）
将PP设置为红色
把PP设置为当前插入结点

情景4.2：
叔叔结点不存在或为黑结点，并且插入结点的父亲结点是祖父结点的左子结点

单纯从插入前来看，也即不算情景4.1自底向上处理时的情况，叔叔结点非红即为叶子结点(Nil)。因为如果叔叔结点为黑结点，而父结点为红结点，那么叔叔结点所在的子树的黑色结点就比父结点所在子树的多了，这不满足红黑树的性质5。后续情景同样如此，不再多做说明了。

情景4.2.1：
插入结点是其父结点的左子结点
处理：

将P设为黑色
将PP设为红色
对PP进行右旋

**************************************************************************/
template<class T>
void Tree<T>::Insert_Node(T Insert_Data)
{
	Tree_Node<T>* Temp_Node = Root_Node;
	while (Temp_Node != NULL)
	{
		if (Insert_Data > Temp_Node->Data)//如果插入的节点数值大于根节点大小 向右插入 二叉平衡树
		{
			if (Temp_Node->Right_Child == NULL)//判断右节点是否存在
			{
				Temp_Node->Right_Child = new Tree_Node<T>(Insert_Data);//new一个新节点
				Temp_Node->Right_Child->Color_Tag = 1;
				Temp_Node->Right_Child->Parent_Node = Temp_Node;
				if (Temp_Node->Color_Tag == 1)
				{
					Fix_Tree(Temp_Node->Right_Child);
				}
				break;
			}
			else
			{
				Temp_Node = Temp_Node->Right_Child;
			}
		}
		else 
		{
			if (Temp_Node->Left_Child == NULL)//判断右节点是否存在
			{
				Temp_Node->Left_Child = new Tree_Node<T>(Insert_Data);//new一个新节点
				Temp_Node->Left_Child->Color_Tag = 1;
				Temp_Node->Left_Child->Parent_Node = Temp_Node;
				if (Temp_Node->Color_Tag == 1)
				{
					Fix_Tree(Temp_Node->Left_Child);
				}
				break;
			}
			else
			{
				Temp_Node = Temp_Node->Left_Child;
			}
		}
	}
}
template<class T>
void Tree<T>::Fix_Tree(Tree_Node<T>* Current_Node)
{
	Tree_Node<T>* Temp_Node = Current_Node;
	Tree_Node<T>* Uncle_Node;
	while (Temp_Node != NULL)
	{
		if (Temp_Node->Parent_Node == NULL)
		{
			break;
		}
		if (Temp_Node->Parent_Node->Color_Tag != 1)
		{
			break;
		}
		Tree_Node<T>* Father_Node = Temp_Node->Parent_Node;
		Tree_Node<T>* Grandfa_Node = Father_Node->Parent_Node;
		if (Grandfa_Node)
		{
			if (Father_Node == Grandfa_Node->Left_Child)//判断父节点为爷爷节点的子节点
			{
				Uncle_Node = Grandfa_Node->Right_Child;//叔叔节点
				if (Uncle_Node)//叔叔存在
				{
					//情况1 叔叔为红色  将父亲节点和叔叔节点设置为黑色 
					//祖父节点设置为红色 将祖父节点设置为当前节点
					if (Uncle_Node->Color_Tag == 1)
					{
						Uncle_Node->Color_Tag = 0;
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Temp_Node = Grandfa_Node;
					}
					//情况2：叔叔是黑色 且当前节点为右孩子 将父节点作为当前节点 对父节点进行左旋
					else if (Temp_Node == Father_Node->Right_Child)
					{
						Temp_Node = Temp_Node->Parent_Node;
						Left_Rotate(Temp_Node);
					}
					//情况3：叔叔是黑色 且当前节点为左孩子 将父节点设为黑色 
					//祖父节点设为红色 对祖父节点右旋
					else
					{
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Right_Rotate(Grandfa_Node);

					}
				}
				//没有叔叔节点时
				else
				{
					if (Temp_Node == Father_Node->Right_Child)
					{
						Temp_Node = Temp_Node->Parent_Node;
						Left_Rotate(Temp_Node);
					}
					else
					{
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Right_Rotate(Grandfa_Node);
					}
				}
			}
			else
			{
				Uncle_Node = Grandfa_Node->Left_Child;
				if (Uncle_Node)
				{
					//情况1 叔叔为红色  将父亲节点和叔叔节点设置为黑色 
					//祖父节点设置为红色 将祖父节点设置为当前节点
					if (Uncle_Node->Color_Tag == 1)
					{
						Uncle_Node->Color_Tag = 0;
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Temp_Node = Grandfa_Node;
					}
					//情况2：叔叔是黑色 且当前节点为右孩子 将父节点作为当前节点 对父节点进行左旋
					else if (Temp_Node == Father_Node->Left_Child)
					{
						Temp_Node = Temp_Node->Parent_Node;
						Right_Rotate(Temp_Node);
					}
					//情况3：叔叔是黑色 且当前节点为左孩子 将父节点设为黑色 祖父节点设为红色 对祖父节点右旋
					else
					{
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Left_Rotate(Grandfa_Node);
					}
				}
				else
				{
					if (Temp_Node == Father_Node->Left_Child)
					{
						Temp_Node = Temp_Node->Parent_Node;
						Right_Rotate(Temp_Node);
					}
					else
					{
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Left_Rotate(Grandfa_Node);
					}
				}
			}
		}

	}
	//最简单的一种情景，直接把插入结点作为根结点就行，
	//但注意，根据红黑树性质2：根结点是黑色。所以还需要把插入结点设为黑色。
	Root_Node->Color_Tag = 0;

}

/**********************************************************************
 函数功能：从红黑树中搜寻要删除的数据节点                           
 入口参数：删除的数据
 返回值：1表示删除成功 -1表示删除失败
***********************************************************************/
template<class T>
int Tree<T>::Delete_Node(T Delete_Data)
{
	Tree_Node<T>* Temp_Node = Root_Node;
	while (Temp_Node->Data != Delete_Data && Temp_Node != NULL )
	{
		if (Delete_Data > Temp_Node->Data)
		{
			Temp_Node = Temp_Node->Right_Child;
		}
		else
		{
			Temp_Node = Temp_Node->Left_Child;
		}
	}
	if (Temp_Node)
	{
		int Color_Tag = Temp_Node->Color_Tag;
		//情景1：若删除结点无子结点，直接删除
		if (Temp_Node->Left_Child == NULL && Temp_Node->Right_Child == NULL)
		{
			delete Temp_Node;
		}
		//情景2：若删除结点只有一个子结点，用子结点替换删除结点
		//左节点为空  右节点不为空
		else if(Temp_Node->Left_Child == NULL && Temp_Node->Right_Child != NULL)
		{
			if (Temp_Node != Root_Node)//不为根节点
			{
				if (Temp_Node->Parent_Node->Left_child == Temp_Node)
				{
					Temp_Node->Parent_Node->Left_child = Temp_Node->Right_child;
					Temp_Node->Right_child->Parent_Node = Temp_Node->Parent_Node;

				}
				else
				{
					Temp_Node->Parent_Node->Right_child = Temp_Node->Right_child;
					Temp_Node->Right_child->Parent_Node = Temp_Node->Parent_Node;

				}
			}
			else
			{
				Root_Node = Temp_Node->Right_Child;
				Temp_Node->Right_Child->Parent_Node = Root_Node;
			}
		}
		//右节点为空  左节点不为空
		else if (Temp_Node->Left_Child != NULL && Temp_Node->Right_Child == NULL)
		{
			if (Temp_Node != Root_Node)
				//不为根节点
			{
				if (Temp_Node->Parent_Node->Left_Child == Temp_Node)
				{
					Temp_Node->Parent_Node->Left_Child = Temp_Node->Left_Child;
					Temp_Node->Left_Child->Parent_Node = Temp_Node->Parent_Node;

				}
				else
				{
					Temp_Node->Parent_Node->Right_Child = Temp_Node->Left_Child;
					Temp_Node->Left_Child->Parent_Node = Temp_Node->Parent_Node;

				}
			}
			else
			{
				Root_Node = Temp_Node->Left_Child;
				Temp_Node->Parent_Node->Parent_Node = Root_Node;
			}
		}
		else if(Temp_Node->Left_child != NULL && Temp_Node->Right_child != NULL)
			//左右子树都不为空
		{
			Tree_Node<T>* Successor_Node = Find_Successor_Node(Temp_Node);
			if (Temp_Node == Temp_Node->Parent_Node->Left_Child)
			{
				Temp_Node->Parent_Node->Left_Child = Successor_Node;
				Successor_Node->Right_Child = Temp_Node->Right_Child;
				Successor_Node->Left_Child = Temp_Node->Left_Child;
				Successor_Node->Parent_Node = Temp_Node->Parent_Node;
				Successor_Node->Color_Tag = Temp_Node->Color_Tag;
				if (Successor_Node->Right_Child)
				{
					Successor_Node->Parent_Node->Left_Child = Successor_Node->Right_Child;
					Successor_Node->Right_Child->Parent_Node = Successor_Node->Parent_Node;
				}

			}
			else
			{
				Temp_Node->Parent_Node->Right_Child = Successor_Node;
				Successor_Node->Right_Child = Temp_Node->Right_Child;
				Successor_Node->Left_Child = Temp_Node->Left_Child;
				Successor_Node->Parent_Node = Temp_Node->Parent_Node;
				Successor_Node->Color_Tag = Temp_Node->Color_Tag;
				if (Successor_Node->Right_Child)
				{
					Successor_Node->Parent_Node->Left_Child = Successor_Node->Right_Child;
					Successor_Node->Right_Child->Parent_Node = Successor_Node->Parent_Node;
				}
			}

		}
		if (Color_Tag == 0)
		{
			Erase_Node(Temp_Node);
		}
	}
	else
	{
		return -1;
	}
	return 1;
}
/************************************************************************
函数功能：清除该节点相关的所有信息
入口参数：当前节点
返回值：无
*************************************************************************/
template<class T>
void Tree<T>::Erase_Node(Tree_Node<T>* Node_Del)
{
	if (Node_Del->Father_Node)
	{
		Node_Del->Father_Node = NULL;
	}
	Node_Del->Color_Tag = NULL;
	Node_Del->Parent_Node = NULL;
	Node_Del->Left_child = NULL;
	Node_Del->Right_child = NULL;
	Node_Del->Data = NULL;
	delete Node_Del;

}
/************************************************************************
函数功能：找寻当前节点的中序后继节点                                 
入口参数：当前节点
返回值：当前节点的中序后继节点
*************************************************************************/
template<class T>
Tree_Node<T>* Tree<T>::Find_Success_Node(Tree_Node<T>* Current_Node)
{
	Tree_Node<T>* Temp_Node = Current_Node->Right_Child;
	while (Temp_Node->Left_child != NULL)
	{
		Temp_Node = Temp_Node->Left_child;
	}
	return Temp_Node;

}
