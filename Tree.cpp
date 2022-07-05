#include"Tree.h"

template <class T>
Tree<T> ::Tree(T Root_Data) :Root_Node(NULL)
{
	if (Root_Node == NULL)//�ж��Ƿ���ڸ��ڵ�
	{
		//���û��  new һ�����ڵ�
		Root_Node = new Tree_Node<T>(Root_Data);
		Root_Node->Color_Tag = 0;//��ʼ�����ڵ���ɫΪ ��ɫ
	}
}

template <class T>
Tree<T> ::~Tree(){
}
/************************************************************************
�������ܣ��Ե�ǰ�ڵ������������                                     
��ڲ����������ĵ�ǰ�ڵ�
����ֵ����
************************************************************************/
template<class T>
void Tree<T>::Left_Rotate(Tree_Node<T>* Current_Node)
{
	Tree_Node<T>* Parent = Current_Node->Parent_Node;//��ȡ��ǰ�ڵ�ĸ��ڵ�
	Tree_Node<T>* Right_Child = Current_Node->Right_Child;//��ȡ��ǰ�ڵ���ҽڵ�
	Current_Node->Right_Child = Right_Child->Left_Child; // ��ǰ�ڵ���ҽڵ��µ���ڵ� ���ӵ� ��ǰ�ڵ���ҽڵ� 
	Right_Child->Parent_Node = Parent;//��ǰ�ڵ���ҽڵ㸸�ڵ� Ϊ ��ǰ�ڵ�ĸ��ڵ�
	//���һ�� ��ǰ�ڵ�ĸ��ڵ�Ϊ�� ���� �ҽڵ�Ϊ���ڵ�
	if (Parent == NULL)
	{
		Root_Node = Right_Child;
	}
	//���2�������ǰ�ڵ��������ڵ�����ӣ��򽫵�ǰ�ڵ���ҽڵ���Ϊ����ǰ�ڵ�ĸ��ڵ�����ӡ�
	if (Current_Node == Parent->Left_Child)
	{
		Parent->Left_Child = Right_Child;
	}
	else {  //���3��(��ǰ�ڵ��������ڵ���Һ���) ����ǰ�ڵ���ҽڵ���Ϊ����ǰ�ڵ�ĸ��ڵ���Һ��ӡ�
		Parent->Right_Child = Right_Child;
	}
	Right_Child->Left_Child = Current_Node;//�� ����ǰ�ڵ㡱 ��Ϊ ����ǰ�ڵ���ҽڵ�����ӡ�
	Current_Node->Parent_Node = Right_Child;//�� ����ǰ�ڵ�ĸ��ڵ㡱 ��Ϊ ����ǰ�ڵ���ҽڵ㡱
}
/************************************************************************
�������ܣ��Ե�ǰ�ڵ������������                                     
��ڲ����������ĵ�ǰ�ڵ�
����ֵ����
*************************************************************************/
template<class T>
void Tree<T>::Right_Rotate(Tree_Node<T>* Current_Node)
{
	Tree_Node<T>* Left_Child = Current_Node->Left_Child;//��ȡ��ǰ�ڵ����ڵ�
	Tree_Node<T>* Parent = Current_Node->Parent_Node;//��ȡ��ǰ�ڵ�ĸ��ڵ�
	Current_Node->Left_Child = Left_Child->Right_Child;//�� ����ǰ�ڵ����ڵ���Һ��ӡ� ��Ϊ ����ǰ�ڵ�����ӡ�
	Left_Child->Parent_Node = Current_Node;//�� ����ǰ�ڵ㡱 ��Ϊ ����ǰ�ڵ����ڵ���Һ��ӵĸ��ס�
	Left_Child->Parent_Node = Parent;//�� ����ǰ�ڵ�ĸ��ס� ��Ϊ ����ǰ�ڵ����ڵ�ĸ��ס�
	if (Current_Node == NULL)
	{
		Root_Node = Left_Child; // ���1����� ��y�ĸ��ס� �ǿս�㣬��x��Ϊ�����
	}
	if (Current_Node == Parent->Right_Child) 
	{
		Parent->Left_Child = Left_Child;// ���2����� y�����������Һ��ӣ���x��Ϊ��y�ĸ��������ӡ�
	}
	else{
		Parent->Right_Child = Left_Child;// ���3��(y��������������) ��x��Ϊ��y�ĸ��������ӡ�
	}
	Current_Node->Parent_Node = Left_Child;// �� ��y�� ��Ϊ ��x���Һ��ӡ�
	Left_Child->Parent_Node = Parent;// �� ��y�ĸ���㡱 ��Ϊ ��x��
}
/************************************************************************
�������ܣ��������в���һ���ڵ�                                     
��ڲ��������������
����ֵ����
*************************************************************************/
/*************************************************************************
����������Ϊʲô�Ǻ�ɫ�أ����ɺܼ򵥣���ɫ�ڸ���㣨������ڣ�Ϊ��ɫ���ʱ��
������ĺ�ɫƽ��û���ƻ�������Ҫ����ƽ�������������������Ǻ�ɫ����ô����λ
�����ڵ�������ɫ������Ƕ�1����������ƽ�⡣������������ܽ�Ϊ������Щ��
%%%%%%%%%%
�龰1��
�����Ϊ����
��򵥵�һ���龰��ֱ�ӰѲ�������Ϊ�������У���ע�⣬���ݺ��������2��������Ǻ�ɫ�����Ի���Ҫ�Ѳ�������Ϊ��ɫ��
����

�Ѳ�������Ϊ����㣬���ѽ������Ϊ��ɫ��

�龰2��
�������Key�Ѵ���
�������Key�Ѵ��ڣ���Ϊ������ܱ���ƽ�⣬�ڲ���ǰ������Ѿ���ƽ��ģ���ô�Ѳ���������Ϊ��Ҫ����Ľ����ɫ���ٰѽ���ֵ���¾���ɲ����ˡ�
����

��z��Ϊ��ǰ������ɫ��
���µ�ǰ����ֵΪ�������ֵ��

�龰3��
������ĸ����Ϊ�ڽ��
���ڲ���Ľ���Ǻ�ɫ�ģ�������Ӱ��������ƽ�⣬ֱ�Ӳ��뼴�ɣ���������ƽ�⡣
����

ֱ�Ӳ��롣
�龰4��
������ĸ����Ϊ����
�ٴλ����º����������2��������Ǻ�ɫ���������ĸ����Ϊ���㣬��ô�ø���㲻����Ϊ����㣬���Բ��������Ǵ����游��㡣������Ҫ����Ϊ��������ת������Ҫ�游���Ĳ��롣

�龰4.1��
��������ڲ���Ϊ����
�Ӻ��������4����ȷ�����游���Ϊ�ڽ�㣬��Ϊ������ͬʱ�������������ĺ��㡣��ô��ʱ�ò��������ĺ�ڲ���������ǣ��ں�졣��Ȼ��򵥵Ĵ���ʽ�ǰ����Ϊ����ں졣��ͼ5��ͼ6��ʾ��
����

��P��S����Ϊ��ɫ����ǰ������I��
��PP����Ϊ��ɫ
��PP����Ϊ��ǰ������

�龰4.2��
�����㲻���ڻ�Ϊ�ڽ�㣬���Ҳ�����ĸ��׽�����游�������ӽ��

�����Ӳ���ǰ������Ҳ�������龰4.1�Ե����ϴ���ʱ�������������Ǻ켴ΪҶ�ӽ��(Nil)����Ϊ���������Ϊ�ڽ�㣬�������Ϊ���㣬��ô���������ڵ������ĺ�ɫ���ͱȸ�������������Ķ��ˣ��ⲻ��������������5�������龰ͬ����ˣ����ٶ���˵���ˡ�

�龰4.2.1��
���������丸�������ӽ��
����

��P��Ϊ��ɫ
��PP��Ϊ��ɫ
��PP��������

**************************************************************************/
template<class T>
void Tree<T>::Insert_Node(T Insert_Data)
{
	Tree_Node<T>* Temp_Node = Root_Node;
	while (Temp_Node != NULL)
	{
		if (Insert_Data > Temp_Node->Data)//�������Ľڵ���ֵ���ڸ��ڵ��С ���Ҳ��� ����ƽ����
		{
			if (Temp_Node->Right_Child == NULL)//�ж��ҽڵ��Ƿ����
			{
				Temp_Node->Right_Child = new Tree_Node<T>(Insert_Data);//newһ���½ڵ�
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
			if (Temp_Node->Left_Child == NULL)//�ж��ҽڵ��Ƿ����
			{
				Temp_Node->Left_Child = new Tree_Node<T>(Insert_Data);//newһ���½ڵ�
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
			if (Father_Node == Grandfa_Node->Left_Child)//�жϸ��ڵ�Ϊүү�ڵ���ӽڵ�
			{
				Uncle_Node = Grandfa_Node->Right_Child;//����ڵ�
				if (Uncle_Node)//�������
				{
					//���1 ����Ϊ��ɫ  �����׽ڵ������ڵ�����Ϊ��ɫ 
					//�游�ڵ�����Ϊ��ɫ ���游�ڵ�����Ϊ��ǰ�ڵ�
					if (Uncle_Node->Color_Tag == 1)
					{
						Uncle_Node->Color_Tag = 0;
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Temp_Node = Grandfa_Node;
					}
					//���2�������Ǻ�ɫ �ҵ�ǰ�ڵ�Ϊ�Һ��� �����ڵ���Ϊ��ǰ�ڵ� �Ը��ڵ��������
					else if (Temp_Node == Father_Node->Right_Child)
					{
						Temp_Node = Temp_Node->Parent_Node;
						Left_Rotate(Temp_Node);
					}
					//���3�������Ǻ�ɫ �ҵ�ǰ�ڵ�Ϊ���� �����ڵ���Ϊ��ɫ 
					//�游�ڵ���Ϊ��ɫ ���游�ڵ�����
					else
					{
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Right_Rotate(Grandfa_Node);

					}
				}
				//û������ڵ�ʱ
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
					//���1 ����Ϊ��ɫ  �����׽ڵ������ڵ�����Ϊ��ɫ 
					//�游�ڵ�����Ϊ��ɫ ���游�ڵ�����Ϊ��ǰ�ڵ�
					if (Uncle_Node->Color_Tag == 1)
					{
						Uncle_Node->Color_Tag = 0;
						Father_Node->Color_Tag = 0;
						Grandfa_Node->Color_Tag = 1;
						Temp_Node = Grandfa_Node;
					}
					//���2�������Ǻ�ɫ �ҵ�ǰ�ڵ�Ϊ�Һ��� �����ڵ���Ϊ��ǰ�ڵ� �Ը��ڵ��������
					else if (Temp_Node == Father_Node->Left_Child)
					{
						Temp_Node = Temp_Node->Parent_Node;
						Right_Rotate(Temp_Node);
					}
					//���3�������Ǻ�ɫ �ҵ�ǰ�ڵ�Ϊ���� �����ڵ���Ϊ��ɫ �游�ڵ���Ϊ��ɫ ���游�ڵ�����
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
	//��򵥵�һ���龰��ֱ�ӰѲ�������Ϊ�������У�
	//��ע�⣬���ݺ��������2��������Ǻ�ɫ�����Ի���Ҫ�Ѳ�������Ϊ��ɫ��
	Root_Node->Color_Tag = 0;

}

/**********************************************************************
 �������ܣ��Ӻ��������ѰҪɾ�������ݽڵ�                           
 ��ڲ�����ɾ��������
 ����ֵ��1��ʾɾ���ɹ� -1��ʾɾ��ʧ��
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
		//�龰1����ɾ��������ӽ�㣬ֱ��ɾ��
		if (Temp_Node->Left_Child == NULL && Temp_Node->Right_Child == NULL)
		{
			delete Temp_Node;
		}
		//�龰2����ɾ�����ֻ��һ���ӽ�㣬���ӽ���滻ɾ�����
		//��ڵ�Ϊ��  �ҽڵ㲻Ϊ��
		else if(Temp_Node->Left_Child == NULL && Temp_Node->Right_Child != NULL)
		{
			if (Temp_Node != Root_Node)//��Ϊ���ڵ�
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
		//�ҽڵ�Ϊ��  ��ڵ㲻Ϊ��
		else if (Temp_Node->Left_Child != NULL && Temp_Node->Right_Child == NULL)
		{
			if (Temp_Node != Root_Node)
				//��Ϊ���ڵ�
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
			//������������Ϊ��
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
�������ܣ�����ýڵ���ص�������Ϣ
��ڲ�������ǰ�ڵ�
����ֵ����
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
�������ܣ���Ѱ��ǰ�ڵ�������̽ڵ�                                 
��ڲ�������ǰ�ڵ�
����ֵ����ǰ�ڵ�������̽ڵ�
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
