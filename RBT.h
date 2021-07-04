#pragma once

#include<iostream>
#include<string>
using namespace std;

template<typename T>
class RBT
{
private:
	template<typename T>
	struct Node
	{
		Node<T> *Left, *Right, *Parent;
		int data, count;
		string Color;
		Node(int d = 0, Node<T> *L = nullptr, Node<T> *R = nullptr, Node<T> *P = nullptr, string C = "Red", int c = 0)
		{
			Left = L;
			Right = R;
			Parent = P;
			data = d;
			Color = C;
			count = c;
		}
		~Node()
		{

		}

	};

	/*    Insertion */
	void Insert_At_Tree(Node<T> *&N, Node<T>* &t)
	{
		if (t == nullptr)
		{
			t = N;
			return;
		}
		if (N->data < t->data)
		{
			N->Parent = t;
			Insert_At_Tree(N, t->Left);
		}
		else if (N->data == t->data)
		{
			t->count++;
			return;
		}
		else
		{
			N->Parent = t;
			Insert_At_Tree(N, t->Right);
		}
	}
	void Insert_Helper(const int &V)
	{
		Node<T> * N = new Node<T>(V);
		if (Root == nullptr)
		{
			Root = N;
			Root->Color = "Black";
		}
		else
		{
			Insert_At_Tree(N, Root);
			Fixed_Color(N);
		}
	}
	Node<T>* Uncle(Node<T>* N)
	{
		if (N->Parent == nullptr || N->Parent->Parent == nullptr)
		{
			return nullptr;
		}

		if (N->Parent == N->Parent->Parent->Left)
		{
			return N->Parent->Parent->Right;
		}
		else
		{
			return N->Parent->Parent->Left;
		}

	}
	void Fixed_Color(Node<T> *&N)
	{
		if (N == Root)
		{
			N->Color = "Black";
			return;
		}
		else if (N->Parent->Color == "Black")//Case 2
		{
			return;
		}
		else if (N->Parent->Color == "Red" && Uncle(N) != nullptr && Uncle(N)->Color == "Red")//Case 3
		{
			N->Parent->Parent->Color = "Red";
			N->Parent->Color = "Black";
			Uncle(N)->Color = "Black";
			Fixed_Color(N->Parent->Parent);
		}
		else if (N->Parent->Color == "Red" && Uncle(N) != nullptr && Uncle(N)->Color == "Black"//case 4
			|| N->Parent->Color == "Red" && Uncle(N) == nullptr)
		{
			if (N->Parent->Right == N && N->Parent == N->Parent->Parent->Left)
			{
				Case4_L_Rotation(N);
			}
			else if (N->Parent->Left == N && N->Parent == N->Parent->Parent->Right)
			{
				Case4_R_Rotation(N);
			}
			Case5(N);
		}

	}
	void Case4_R_Rotation(Node<T> *&N)
	{
		Node<T> * Temp = N->Right;
		N->Parent->Parent->Right = N;
		N->Right = N->Parent;
		N->Parent->Left = nullptr;
		N->Parent = N->Parent->Parent;
		N->Right->Parent = N;

		N = N->Right;
		if (Temp != nullptr)
		{
			N->Left = Temp;
			N->Left->Parent = N;
		}
	}
	void Case4_L_Rotation(Node<T> *&N)
	{
		Node<T> * Temp = N->Left;
		N->Parent->Parent->Left = N;
		N->Left = N->Parent;
		N->Parent->Right = nullptr;
		N->Parent = N->Parent->Parent;
		N->Left->Parent = N;

		N = N->Left;
		if (Temp != nullptr)
		{
			N->Right = Temp;
			N->Right->Parent = N;
		}

	}
	void Case5(Node<T> *& N)
	{
		if (N == N->Parent->Left)
		{
			L_Rotation(N);
		}
		else
		{
			R_Rotation(N);
		}
	}
	void L_Rotation(Node<T> *&N)
	{
		Node<T> * Temp = N->Parent->Right;
		N->Parent->Right = N->Parent->Parent;
		if (Root == N->Parent->Parent)
		{
			Root = N->Parent;
			Root->Parent = Root;
			N->Parent->Right->Parent = N->Parent;
			N->Parent->Right->Left = Temp;
			if (Temp != nullptr)
			{
				N->Parent->Right->Left->Parent = N->Parent->Right;
			}
			N->Parent->Color = "Black";
			N->Parent->Right->Color = "Red";
		}
		else
		{
			N->Parent->Parent = N->Parent->Right->Parent;
			N->Parent->Parent->Left = N->Parent;
			N->Parent->Right->Parent = N->Parent;
			N->Parent->Right->Left = Temp;
			if (Temp != nullptr)
			{
				N->Parent->Right->Left->Parent = N->Parent->Right;
			}
			N->Parent->Color = "Black";
			N->Parent->Right->Color = "Red";
		}
	}
	void R_Rotation(Node<T> *&N)
	{
		Node<T> * Temp = N->Parent->Left;
		N->Parent->Left = N->Parent->Parent;
		if (Root == N->Parent->Parent)
		{
			Root = N->Parent;
			Root->Parent = Root;
			N->Parent->Left->Parent = N->Parent;
			N->Parent->Left->Right = Temp;
			if (Temp != nullptr)
			{
				N->Parent->Left->Right->Parent = N->Parent->Left;
			}
			N->Parent->Color = "Black";
			N->Parent->Left->Color = "Red";
		}
		else
		{
			N->Parent->Parent = N->Parent->Left->Parent;
			N->Parent->Parent->Right = N->Parent;
			N->Parent->Left->Parent = N->Parent;
			N->Parent->Left->Right = Temp;
			if (Temp != nullptr)
			{
				N->Parent->Left->Right->Parent = N->Parent->Right;
			}
			N->Parent->Color = "Black";
			N->Parent->Left->Color = "Red";
		}
	}

	/*    Deletion   */
	void Delete_Helper(Node<T> *&N, int Value)
	{
		Node<T> * Temp = Search_Element(N, Value);
		if (Temp != nullptr)
		{
			string C = Temp->Color;
			Delete_Node(N, Value);
			if (C == "Black")
			{
				Fix_Colouring(N);
			}
		}
		else
		{
			cout << "\n***value does not exist***\n";
		}
	}
	Node<T>* Minimum_Value(Node<T>* Temp2)
	{
		while (Temp2->Left != nullptr)
		{
			Temp2 = Temp2->Left;
		}
		return Temp2;
	}
	void Search_Value(Node<T>* &Temp2, int Value, Node<T>* &Temp1)
	{
		while (Temp2 != nullptr && Temp2->data != Value)
		{
			Temp1 = Temp2;
			if (Value < Temp2->data)
			{
				Temp2 = Temp2->Left;
			}
			else
			{
				Temp2 = Temp2->Right;
			}
		}
	}
	bool Delete_Node(Node<T>*& R, int Value)
	{
		Node<T> *Temp1 = nullptr;
		Node<T>* Temp2 = R;
		Search_Value(Temp2, Value, Temp1);

		if (Temp2 == nullptr)
		{
			return false;
		}
		if (Temp2->Left == nullptr && Temp2->Right == nullptr && Temp2->Color=="Red")
		{
			if (Temp2 != R)
			{
				if (Temp1->Left == Temp2)
				{
					Temp1->Left = nullptr;
				}
				else
				{
					Temp1->Right = nullptr;
				}
			}
			else
			{
				R = nullptr;
			}
			delete(Temp2);
		}

		else if (Temp2->Left && Temp2->Right)
		{
			Node<T>* curr = Minimum_Value(Temp2->Right);

			int val = curr->data;
			Delete_Node(Root, curr->data);

			Temp2->data = val;
		}
		else if (Temp2->Color == "Red")
		{
			Node<T>* curr = (Temp2->Left) ? Temp2->Left : Temp2->Right;
			if (Temp2 != Root)
			{
				if (Temp2 == Temp1->Left)
				{
					Temp1->Left = curr;
				}
				else
				{
					Temp1->Right = curr;
				}
			}
			else
			{
				R = curr;
			}

			delete(Temp2);
		}
		return true;
	}

	void Fix_Colouring(Node<T> *x)
	{
		Node<T> *s;
		while (x != Root && x->Color == "Black")
		{
			if (x == x->Parent->Left)
			{
				s = x->Parent->Right;
				if (s->Color == "Red")
				{
					s->Color = "Black";
					x->Parent->Color = "Red";
					L_Rotation(x->Parent);
					s = x->Parent->Right;
				}

				if (s->Left->Color == "Black" && s->Right->Color == "Black")
				{
					s->Color = "Red";
					x = x->Parent;
				}
				else 
				{
					if (s->Right->Color == "Black")
					{
						s->Left->Color = "Black";
						s->Color = 1;
						R_Rotation(s);
						s = x->Parent->Right;
					}

					s->Color = x->Parent->Color;
					x->Parent->Color = "Black";
					s->Right->Color = "Black";
					L_Rotation(x->Parent);
					x = Root;
				}
			}
			else 
			{
				s = x->Parent->Left;
				if (s->Color == "Red") 
				{
					s->Color = "Black";
					x->Parent->Color = "Red";
					R_Rotation(x->Parent);
					s = x->Parent->Left;
				}

				if (s->Right->Color == "Black" && s->Right->Color == "Black")
				{
					s->Color = "Red";
					x = x->Parent;
				}
				else
				{
					if (s->Left->Color == "Black")
					{
						s->Right->Color = "Black";
						s->Color = "Red";
						L_Rotation(s);
						s = x->Parent->Left;
					}

					s->Color = x->Parent->Color;
					x->Parent->Color = "Black";
					s->Left->Color = "Black";
					R_Rotation(x->Parent);
					x = Root;
				}
			}
		}
		x->Color = "Black";
	}

	/*     Printing*/
	void Inorder(Node<T> *R)
	{
		if (R == nullptr)
		{
			return;
		}
		Inorder(R->Left);
		cout << R->data << ' ' << R->Color<<endl;
		Inorder(R->Right);
	}
	void Perorder(Node<T> * R)
	{
		if (R == nullptr)
		{
			return;
		}
		cout << R->data << " " << R->Color << endl;
		Perorder(R->Left);
		Perorder(R->Right);
	}
	void Postorder(Node<T> * R)
	{
		if (R == nullptr)
		{
			return;
		}
		Postorder(R->Left);
		Postorder(R->Right);
		cout << R->data << " "<<R->Color<<endl;
	}

	void Inorder2(Node<T> *R)
	{
		if (R == nullptr)
		{
			return;
		}
		Inorder2(R->Right);
		cout << R->data << ' ' << R->Color << endl;
		Inorder2(R->Left);
	}
	void Perorder2(Node<T> * R)
	{
		if (R == nullptr)
		{
			return;
		}
		cout << R->data << " " << R->Color << endl;
		Perorder2(R->Right);
		Perorder2(R->Left);
		
	}
	void Postorder2(Node<T> * R)
	{
		if (R == nullptr)
		{
			return;
		}
		Postorder2(R->Right);
		Postorder2(R->Left);
		cout << R->data << " " << R->Color << endl;
	}

	/*    Seaching*/
	Node<T>* Search_Element(Node<T> *N, int key)
	{
		if (N == nullptr || N->data == key)
		{
			return N;
		}
		if (N->data < key)
		{
			return Search_Element(N->Right, key);
		}
		return Search_Element(N->Left, key);
	}

	/*   Copying*/
	void Copy_Tree(Node<T> * &B1, const Node<T>* B2)
	{
		if (B2 == nullptr)
		{
			B1 = nullptr;
		}
		else
		{
			B1 = new Node<T>;
			B1->data = B2->data;
			B1->Color = B2->Color;
			Copy_Tree(B1->Left, B2->Left);
			Copy_Tree(B1->Right, B2->Right);
		}
	}

	/*   Destory tree*/
	Node<T>* Empty(Node<T>* t)
	{
		if (t == nullptr)
		{
			return nullptr;
		}
		else
		{
			Empty(t->Left);
			Empty(t->Right);
			delete t;
		}
		return nullptr;
	}
	Node<T> * Root;

public:
	RBT()
	{
		Root = nullptr;
	}
	void Insert(int V)
	{
		Insert_Helper(V);
	}
	RBT(const RBT<T> & B)
	{
		Copy_Tree(Root, B.Root);
	}
	void Copy()
	{
		RBT<int> B;
		Copy_Tree(B.Root, Root);
		cout << "\n\nCopy of tree is constructed\n";
	}
	void Destory()
	{
		Root = Empty(Root);
	}
	void Print(int Pos)
	{
		if (Root == nullptr)
		{
			cout << "\n\nFile not found !!..\n";
			return;
		}
		else if (Pos == 4)
		{
			this->Perorder(Root);
		}
		else if (Pos == 5)
		{
			this->Inorder(Root);
		}
		else if (Pos == 6)
		{
			this->Postorder(Root);
		}
		else if (Pos == 7)
		{
			this->Perorder2(Root);
		}
		else if (Pos == 8)
		{
			this->Inorder2(Root);
		}
		else if (Pos == 9)
		{
			this->Postorder2(Root);
		}

	}
	void Display_Parent()
	{
		Parent_Display(Root);
	}
	void Parent_Display(Node<T> * R)
	{
		if (R == nullptr)
		{
			return;
		}
		Parent_Display(R->Left);
		cout << R->Parent->data << " ";
		Parent_Display(R->Right);
	}
	void Delete(int V)
	{
		this->Delete_Helper(Root, V);
	}
	void Seaching(int V)
	{
		cout <<"\n\nValue for seaching in tree is :  "<< (this->Search_Element(Root, V))->data;
	}
	~RBT()
	{
		//Root = Empty(Root);
	}
};

