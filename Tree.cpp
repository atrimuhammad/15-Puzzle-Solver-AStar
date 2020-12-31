#include <iostream>
#include <fstream>
#include <pthread.h>
#include "Tree.h"
using namespace std;

pthread_t tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9, tid10, tid11, tid12, tid13, tid14, tid15, tid16, tid17, tid18, tid19, tid20, tid21, tid22, tid23, tid24, tid25, tid26, tid27, tid28, tid29, tid30, tid31, tid32, tid33, tid34, tid35, tid36;

Tree::Tree()
{
	root = new T_Node;
}
Tree::~Tree()
{

}
T_Node* Tree::getRootNode()
{
	return root;
}
int* Tree::getChildrenArray(T_Node* node)
{
	return node->children;
}
bool Tree::GotGoal(T_Node* node)
{
	int num = 0;

	bool flag = true;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			num++;

			if(node->puzzle[i][j] == num)
			{
				flag = true;
			}
			else
			{
				flag = false;

				break;
			}
		}

		if(flag == false)
		{
			break;
		}
	}

	return flag;
}
void Tree::MakeRootNode(int** puzzle)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			root->puzzle[i][j] = puzzle[i][j];
		}
	}
}
void Tree::NodePuzzlePrinting(T_Node* node)
{
	for(int i = 0; i < 4; i++)
	{
		cout << endl;

		for(int j = 0; j < 4; j++)
		{
			cout << node->puzzle[i][j] << " ";
		}
	}
}
void Tree::BlankTileRowandColumn(T_Node* node, int& blank_row, int& blank_col)
{
	bool flag = false;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(node->puzzle[i][j] == 16)
			{
				flag = true;

				blank_row = i;
				blank_col = j;

				break;
			}
		}
		if(flag == true)
		{
			break;
		}
	}
}
void Tree::PossibleChildren(T_Node* node, int blank_row, int blank_col)
{
	for(int i = 0; i < 4; i++)
	{
		cout << node->children[i] << " ";
	}
	
	cout << endl;

	if(blank_row == 0)
	{
		node->children[0] = 0;
	}
	if(blank_row == 3)
	{
		node->children[1] = 0;
	}
	if(blank_col == 0)
	{
		node->children[2] = 0;
	}
	if(blank_col == 3)
	{
		node->children[3] = 0;
	}

	for(int i = 0; i < 4; i++)
	{
		cout << node->children[i] << " ";
	}
}
void Tree::MakeTempPuzzle(int**& temp, T_Node* node)
{
	temp = new int*[4];
	
	for(int i = 0; i < 4; i++)
	{
		temp[i] = new int[4];
	}
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			temp[i][j] = node->puzzle[i][j];
		}
	}
}
void Tree::ChildPuzzleSameAsCurrentParent(bool& flag1, int** temp, T_Node* parent_node)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(temp[i][j] == parent_node->puzzle[i][j])
			{
				flag1 = true;
			}
			else
			{
				flag1 = false;

				break;
			}
		}

		if(flag1 == false)
		{
			break;
		}
	}
}
void Tree::MakeUpChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col)
{
	if(node->children[0] == 1)
	{
		bool flag1 = true;

		int** temp;

		int temp1 = -1;

		MakeTempPuzzle(temp, node);

		temp1 = temp[blank_row][blank_col];

		temp[blank_row][blank_col] = temp[blank_row - 1][blank_col];

		temp[blank_row - 1][blank_col] = temp1;

		ChildPuzzleSameAsCurrentParent(flag1, temp, parent_node);

		if(flag1 == true)
		{
			node->children[0] = 0;
		}
		if(flag1 == false)
		{
			node->up = new T_Node;
	
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					node->up->puzzle[i][j] = temp[i][j];
				}
			}
	
			cout << "\n\nUP";
	
			NodePuzzlePrinting(node->up);
		}
	}
}
void Tree::MakeDownChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col)
{
	if(node->children[1] == 1)
	{
		bool flag1 = true;

		int** temp;

		int temp1 = -1;

		MakeTempPuzzle(temp, node);

		temp1 = temp[blank_row][blank_col];

		temp[blank_row][blank_col] = temp[blank_row + 1][blank_col];

		temp[blank_row + 1][blank_col] = temp1;

		ChildPuzzleSameAsCurrentParent(flag1, temp, parent_node);

		if(flag1 == true)
		{
			node->children[1] = 0;
		}
		if(flag1 == false)
		{
			node->down = new T_Node;
	
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					node->down->puzzle[i][j] = temp[i][j];
				}
			}
	
			cout << "\n\nDOWN";
	
			NodePuzzlePrinting(node->down);
		}
	}
}
void Tree::MakeLeftChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col)
{
	if(node->children[2] == 1)
	{
		bool flag1 = true;
	
		int** temp;
	
		int temp1 = -1;
	
		MakeTempPuzzle(temp, node);
	
		temp1 = temp[blank_row][blank_col];
	
		temp[blank_row][blank_col] = temp[blank_row][blank_col - 1];
	
		temp[blank_row][blank_col - 1] = temp1;
	
		ChildPuzzleSameAsCurrentParent(flag1, temp, parent_node);
	
		if(flag1 == true)
		{
			node->children[2] = 0;
		}
		if(flag1 == false)
		{
			node->left = new T_Node;
	
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					node->left->puzzle[i][j] = temp[i][j];
				}
			}
	
			cout << "\n\nLEFT";
	
			NodePuzzlePrinting(node->left);
		}
	}
}
void Tree::MakeRightChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col)
{
	if(node->children[3] == 1)
	{
		bool flag1 = true;

		int** temp;

		int temp1 = -1;

		MakeTempPuzzle(temp, node);

		temp1 = temp[blank_row][blank_col];

		temp[blank_row][blank_col] = temp[blank_row][blank_col + 1];

		temp[blank_row][blank_col + 1] = temp1;

		ChildPuzzleSameAsCurrentParent(flag1, temp, parent_node);

		if(flag1 == true)
		{
			node->children[3] = 0;
		}
		if(flag1 == false)
		{
			node->right = new T_Node;

			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					node->right->puzzle[i][j] = temp[i][j];
				}
			}
	
			cout << "\n\nRIGHT";
	
			NodePuzzlePrinting(node->right);
		}
	}
}
struct Children
{
	T_Node* node;
	T_Node* parent_node;
	int blank_row;
	int blank_col;
	Tree T;
};
//------------------1---------------
void* UpChildThread_8(void* arg)
{
	Children* U = (Children*)arg;
	
	U->T.MakeUpChild(U->node, U->parent_node, U->blank_row, U->blank_col);
	
	return NULL;
}
void* DownChildThread_8(void* arg)
{
	Children* D = (Children*)arg;
	
	D->T.MakeDownChild(D->node, D->parent_node, D->blank_row, D->blank_col);
	
	return NULL;
}
void* LeftChildThread_8(void* arg)
{
	Children* L = (Children*)arg;
	
	L->T.MakeLeftChild(L->node, L->parent_node, L->blank_row, L->blank_col);
	
	return NULL;
}
void* RightChildThread_8(void* arg)
{
	Children* R = (Children*)arg;
	
	R->T.MakeRightChild(R->node, R->parent_node, R->blank_row, R->blank_col);
	
	return NULL;
}
//-------------2-------------
void* AllChildThread_2(void* arg)
{
	Children* A = (Children*)arg;
	
	A->T.MakeUpChild(A->node, A->parent_node, A->blank_row, A->blank_col);
	A->T.MakeDownChild(A->node, A->parent_node, A->blank_row, A->blank_col);
	A->T.MakeLeftChild(A->node, A->parent_node, A->blank_row, A->blank_col);
	A->T.MakeRightChild(A->node, A->parent_node, A->blank_row, A->blank_col);
	
	return NULL;
}
//-----------------3---------------
void* UpDownChildThread_3(void* arg)
{
	Children* UD = (Children*)arg;
	
	UD->T.MakeUpChild(UD->node, UD->parent_node, UD->blank_row, UD->blank_col);
	UD->T.MakeDownChild(UD->node, UD->parent_node, UD->blank_row, UD->blank_col);
	
	return NULL;
}
void* LeftRightChildThread_3(void* arg)
{
	Children* LR = (Children*)arg;
	
	LR->T.MakeLeftChild(LR->node, LR->parent_node, LR->blank_row, LR->blank_col);
	LR->T.MakeRightChild(LR->node, LR->parent_node, LR->blank_row, LR->blank_col);
	
	return NULL;
}
void Tree::MakeChildren(T_Node* node, T_Node* parent_node, Tree T, int NoT)
{
	int blank_row = -1, blank_col = -1;

	BlankTileRowandColumn(node, blank_row, blank_col);
	PossibleChildren(node, blank_row, blank_col);

	if(NoT == 8)
	{
		Children U;
		U.node = node;
		U.parent_node = parent_node;
		U.blank_row = blank_row;
		U.blank_col = blank_col;
		U.T = T;
		
		Children D;
		D.node = node;
		D.parent_node = parent_node;
		D.blank_row = blank_row;
		D.blank_col = blank_col;
		D.T = T;
		
		Children L;
		L.node = node;
		L.parent_node = parent_node;
		L.blank_row = blank_row;
		L.blank_col = blank_col;
		L.T = T;
			
		Children R;
		R.node = node;
		R.parent_node = parent_node;
		R.blank_row = blank_row;
		R.blank_col = blank_col;
		R.T = T;
	
		pthread_create(&tid2, NULL, UpChildThread_8, (void*)&U);
		pthread_create(&tid3, NULL, DownChildThread_8, (void*)&D);
		pthread_create(&tid4, NULL, LeftChildThread_8, (void*)&L);
		pthread_create(&tid5, NULL, RightChildThread_8, (void*)&R);
	
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		pthread_join(tid4, NULL);
		pthread_join(tid5, NULL);
	}
	if(NoT == 7)
	{
		Children U;
		U.node = node;
		U.parent_node = parent_node;
		U.blank_row = blank_row;
		U.blank_col = blank_col;
		U.T = T;
		
		Children D;
		D.node = node;
		D.parent_node = parent_node;
		D.blank_row = blank_row;
		D.blank_col = blank_col;
		D.T = T;
	
		Children LR;
		LR.node = node;
		LR.parent_node = parent_node;
		LR.blank_row = blank_row;
		LR.blank_col = blank_col;
		LR.T = T;
		
		pthread_create(&tid30, NULL, UpChildThread_8, (void*)&U);
		pthread_create(&tid31, NULL, DownChildThread_8, (void*)&D);
		pthread_create(&tid32, NULL, LeftRightChildThread_3, (void*)&LR);
		
		pthread_join(tid30, NULL);
		pthread_join(tid31, NULL);
		pthread_join(tid32, NULL);
	}
	if(NoT == 6)
	{
		Children U;
		U.node = node;
		U.parent_node = parent_node;
		U.blank_row = blank_row;
		U.blank_col = blank_col;
		U.T = T;
		
		Children D;
		D.node = node;
		D.parent_node = parent_node;
		D.blank_row = blank_row;
		D.blank_col = blank_col;
		D.T = T;
	
		Children LR;
		LR.node = node;
		LR.parent_node = parent_node;
		LR.blank_row = blank_row;
		LR.blank_col = blank_col;
		LR.T = T;
		
		pthread_create(&tid24, NULL, UpChildThread_8, (void*)&U);
		pthread_create(&tid25, NULL, DownChildThread_8, (void*)&D);
		pthread_create(&tid26, NULL, LeftRightChildThread_3, (void*)&LR);
		
		pthread_join(tid24, NULL);
		pthread_join(tid25, NULL);
		pthread_join(tid26, NULL);	
	}
	if(NoT == 5)
	{
		Children UD;
		UD.node = node;
		UD.parent_node = parent_node;
		UD.blank_row = blank_row;
		UD.blank_col = blank_col;
		UD.T = T;
			
		Children LR;
		LR.node = node;
		LR.parent_node = parent_node;
		LR.blank_row = blank_row;
		LR.blank_col = blank_col;
		LR.T = T;
		
		pthread_create(&tid19, NULL, UpDownChildThread_3, (void*)&UD);
		pthread_create(&tid20, NULL, LeftRightChildThread_3, (void*)&LR);
	
		pthread_join(tid19, NULL);
		pthread_join(tid20, NULL);
	}
	if(NoT == 4)
	{
		Children UD;
		UD.node = node;
		UD.parent_node = parent_node;
		UD.blank_row = blank_row;
		UD.blank_col = blank_col;
		UD.T = T;
			
		Children LR;
		LR.node = node;
		LR.parent_node = parent_node;
		LR.blank_row = blank_row;
		LR.blank_col = blank_col;
		LR.T = T;
		
		pthread_create(&tid15, NULL, UpDownChildThread_3, (void*)&UD);
		pthread_create(&tid16, NULL, LeftRightChildThread_3, (void*)&LR);
	
		pthread_join(tid15, NULL);
		pthread_join(tid16, NULL);
	}
	if(NoT == 3)
	{
		Children A;
		A.node = node;
		A.parent_node = parent_node;
		A.blank_row = blank_row;
		A.blank_col = blank_col;
		A.T = T;
	
		pthread_create(&tid12, NULL, AllChildThread_2, (void*)&A);
	
		pthread_join(tid12, NULL);
	}
	if(NoT == 2)
	{
		Children A;
		A.node = node;
		A.parent_node = parent_node;
		A.blank_row = blank_row;
		A.blank_col = blank_col;
		A.T = T;
	
		pthread_create(&tid10, NULL, AllChildThread_2, (void*)&A);
	
		pthread_join(tid10, NULL);
	}
}
void Tree::UpChildHeuristicValue(T_Node* node, int G, int** goal)
{
	if(node->up != NULL)
	{
		int goal_row = -1, goal_col = -1;

		int vertical_distance = -1;
		int horizontal_distance = -1;

		int node_value = -1;
		int sum_manhattan = 0;
		int sum;

		bool flag2 = false;

		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				node_value = node->up->puzzle[i][j];

				flag2 = false;

				for(int k = 0; k < 4; k++)
				{
					for(int l = 0; l < 4; l++)
					{
						if(node_value == goal[k][l])
						{
							flag2 = true;

							goal_row = k;
							goal_col = l;

							break;
						}
					}

					if(flag2 == true)
					{
						break;
					}
				}

				vertical_distance = goal_row - i;
				horizontal_distance = goal_col - j;

				if(vertical_distance < 0)
				{
					vertical_distance = vertical_distance * -1;
				}
				if(horizontal_distance < 0)
				{
					horizontal_distance = horizontal_distance * -1;
				}

				sum = vertical_distance + horizontal_distance;

				if(node_value != 16)
				{
					sum_manhattan+=sum;
				}
			}
		}

		node->up->H = sum_manhattan;
		node->up->G = G;
		node->up->F = node->up->H;
	}
}
void Tree::DownChildHeuristicValue(T_Node* node, int G, int** goal)
{
	if(node->down != NULL)
	{
		int goal_row = -1, goal_col = -1;

		int vertical_distance = -1;
		int horizontal_distance = -1;

		int node_value = -1;
		int sum_manhattan = 0;
		int sum;

		bool flag2 = false;

		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				node_value = node->down->puzzle[i][j];

				flag2 = false;

				for(int k = 0; k < 4; k++)
				{
					for(int l = 0; l < 4; l++)
					{
						if(node_value == goal[k][l])
						{
							flag2 = true;

							goal_row = k;
							goal_col = l;

							break;
						}
					}

					if(flag2 == true)
					{
						break;
					}
				}

				vertical_distance = goal_row - i;
				horizontal_distance = goal_col - j;

				if(vertical_distance < 0)
				{
					vertical_distance = vertical_distance * -1;
				}
				if(horizontal_distance < 0)
				{
					horizontal_distance = horizontal_distance * -1;
				}

				sum = vertical_distance + horizontal_distance;

				if(node_value != 16)
				{
					sum_manhattan+=sum;
				}
			}
		}

		node->down->H = sum_manhattan;
		node->down->G = G;
		node->down->F = node->down->H;
	}
}
void Tree::LeftChildHeuristicValue(T_Node* node, int G, int** goal)
{
	if(node->left != NULL)
	{
		int goal_row = -1, goal_col = -1;

		int vertical_distance = -1;
		int horizontal_distance = -1;

		int node_value = -1;
		int sum_manhattan = 0;
		int sum;

		bool flag2 = false;

		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				node_value = node->left->puzzle[i][j];

				flag2 = false;

				for(int k = 0; k < 4; k++)
				{
					for(int l = 0; l < 4; l++)
					{
						if(node_value == goal[k][l])
						{
							flag2 = true;

							goal_row = k;
							goal_col = l;

							break;
						}
					}

					if(flag2 == true)
					{
						break;
					}
				}

				vertical_distance = goal_row - i;
				horizontal_distance = goal_col - j;

				if(vertical_distance < 0)
				{
					vertical_distance = vertical_distance * -1;
				}
				if(horizontal_distance < 0)
				{
					horizontal_distance = horizontal_distance * -1;
				}

				sum = vertical_distance + horizontal_distance;

				if(node_value != 16)
				{
					sum_manhattan+=sum;
				}
			}
		}

		node->left->H = sum_manhattan;
		node->left->G = G;
		node->left->F = node->left->H;
	}
}
void Tree::RightChildHeuristicValue(T_Node* node, int G, int** goal)
{
	if(node->right != NULL)
	{
		int goal_row = -1, goal_col = -1;

		int vertical_distance = -1;

		int horizontal_distance = -1;

		int node_value = -1;
		int sum_manhattan = 0;
		int sum;

		bool flag2 = false;

		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				node_value = node->right->puzzle[i][j];

				flag2 = false;

				for(int k = 0; k < 4; k++)
				{
					for(int l = 0; l < 4; l++)
					{
						if(node_value == goal[k][l])
						{
							flag2 = true;

							goal_row = k;
							goal_col = l;

							break;
						}
					}

					if(flag2 == true)
					{
						break;
					}
				}

				vertical_distance = goal_row - i;
				horizontal_distance = goal_col - j;

				if(vertical_distance < 0)
				{
					vertical_distance = vertical_distance * -1;
				}
				if(horizontal_distance < 0)
				{
					horizontal_distance = horizontal_distance * -1;
				}

				sum = vertical_distance + horizontal_distance;

				if(node_value != 16)
				{
					sum_manhattan+=sum;
				}
			}
		}

		node->right->H = sum_manhattan;
		node->right->G = G;
		node->right->F = node->right->H;
	}
}
struct Heuristic
{
	T_Node* node;
	int G;
	int** goal;

	Tree T;
};
//----------------1------------
void* UpChildHeuristicThread_8(void* arg)
{
	Heuristic* U = (Heuristic*)arg;
	
	U->T.UpChildHeuristicValue(U->node, U->G, U->goal);
	
	return NULL;
}
void* DownChildHeuristicThread_8(void* arg)
{
	Heuristic* D = (Heuristic*)arg;
	
	D->T.DownChildHeuristicValue(D->node, D->G, D->goal);
	
	return NULL;
}
void* LeftChildHeuristicThread_8(void* arg)
{
	Heuristic* L = (Heuristic*)arg;
	
	L->T.LeftChildHeuristicValue(L->node, L->G, L->goal);
	
	return NULL;
}
void* RightChildHeuristicThread_8(void* arg)
{
	Heuristic* R = (Heuristic*)arg;
	
	R->T.RightChildHeuristicValue(R->node, R->G, R->goal);	
	
	return NULL;
}
//--------------2------------
void* AllChildHeuristicThread_2(void* arg)
{
	Heuristic* A = (Heuristic*)arg;
	
	A->T.UpChildHeuristicValue(A->node, A->G, A->goal);
	A->T.DownChildHeuristicValue(A->node, A->G, A->goal);
	A->T.LeftChildHeuristicValue(A->node, A->G, A->goal);
	A->T.RightChildHeuristicValue(A->node, A->G, A->goal);	
	
	return NULL;
}
//-------------3-------------
void* UpDownChildHeuristicThread_3(void* arg)
{
	Heuristic* UD = (Heuristic*)arg;
	
	UD->T.UpChildHeuristicValue(UD->node, UD->G, UD->goal);
	UD->T.DownChildHeuristicValue(UD->node, UD->G, UD->goal);
	
	return NULL;
}
void* LeftRightChildHeuristicThread_3(void* arg)
{
	Heuristic* LR = (Heuristic*)arg;
	
	LR->T.LeftChildHeuristicValue(LR->node, LR->G, LR->goal);
	LR->T.RightChildHeuristicValue(LR->node, LR->G, LR->goal);	
	
	return NULL;
}
void Tree::FindHeuristicValues(T_Node* node, int G, Tree T, int NoT)
{
	int** goal;

	goal = new int*[4];
	
	for(int i = 0; i < 4; i++)
	{
		goal[i] = new int[4];
	}
	
	int num = 0;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			num++;

			goal[i][j] = num;
		}
	}
	
	if(NoT == 8)
	{
		Heuristic U;
		U.node = node;
		U.G = G;
		U.goal = goal;
		U.T = T;
		
		Heuristic D;
		D.node = node;
		D.G = G;
		D.goal = goal;
		D.T = T;
		
		Heuristic L;
		L.node = node;
		L.G = G;
		L.goal = goal;
		L.T = T;
		
		Heuristic R;
		R.node = node;
		R.G = G;
		R.goal = goal;
		R.T = T;
	
		pthread_create(&tid6, NULL, UpChildHeuristicThread_8, (void*)&U);
		pthread_create(&tid7, NULL, DownChildHeuristicThread_8, (void*)&D);
		pthread_create(&tid8, NULL, LeftChildHeuristicThread_8, (void*)&L);
		pthread_create(&tid9, NULL, RightChildHeuristicThread_8, (void*)&R);
	
		pthread_join(tid6, NULL);
		pthread_join(tid7, NULL);
		pthread_join(tid8, NULL);
		pthread_join(tid9, NULL);
	}
	if(NoT == 7)
	{
		Heuristic U;
		U.node = node;
		U.G = G;
		U.goal = goal;
		U.T = T;
		
		Heuristic D;
		D.node = node;
		D.G = G;
		D.goal = goal;
		D.T = T;
		
		Heuristic L;
		L.node = node;
		L.G = G;
		L.goal = goal;
		L.T = T;
		
		Heuristic R;
		R.node = node;
		R.G = G;
		R.goal = goal;
		R.T = T;
	
		pthread_create(&tid33, NULL, UpChildHeuristicThread_8, (void*)&U);
		pthread_create(&tid34, NULL, DownChildHeuristicThread_8, (void*)&D);
		pthread_create(&tid35, NULL, LeftChildHeuristicThread_8, (void*)&L);
		pthread_create(&tid36, NULL, RightChildHeuristicThread_8, (void*)&R);
	
		pthread_join(tid33, NULL);
		pthread_join(tid34, NULL);
		pthread_join(tid35, NULL);
		pthread_join(tid36, NULL);
	}
	if(NoT == 6)
	{
		Heuristic U;
		U.node = node;
		U.G = G;
		U.goal = goal;
		U.T = T;
		
		Heuristic D;
		D.node = node;
		D.G = G;
		D.goal = goal;
		D.T = T;
		
		Heuristic LR;
		LR.node = node;
		LR.G = G;
		LR.goal = goal;
		LR.T = T;
		
		pthread_create(&tid27, NULL, UpChildHeuristicThread_8, (void*)&U);
		pthread_create(&tid28, NULL, DownChildHeuristicThread_8, (void*)&D);
		pthread_create(&tid29, NULL, LeftRightChildHeuristicThread_3, (void*)&LR);
	
		pthread_join(tid27, NULL);
		pthread_join(tid28, NULL);
		pthread_join(tid29, NULL);
	}
	if(NoT == 5)
	{
		Heuristic U;
		U.node = node;
		U.G = G;
		U.goal = goal;
		U.T = T;
		
		Heuristic D;
		D.node = node;
		D.G = G;
		D.goal = goal;
		D.T = T;
		
		Heuristic LR;
		LR.node = node;
		LR.G = G;
		LR.goal = goal;
		LR.T = T;
		
		pthread_create(&tid21, NULL, UpChildHeuristicThread_8, (void*)&U);
		pthread_create(&tid22, NULL, DownChildHeuristicThread_8, (void*)&D);
		pthread_create(&tid23, NULL, LeftRightChildHeuristicThread_3, (void*)&LR);
	
		pthread_join(tid21, NULL);
		pthread_join(tid22, NULL);
		pthread_join(tid23, NULL);
	}
	if(NoT == 4)
	{
		Heuristic UD;
		UD.node = node;
		UD.G = G;
		UD.goal = goal;
		UD.T = T;
		
		Heuristic LR;
		LR.node = node;
		LR.G = G;
		LR.goal = goal;
		LR.T = T;
		
		pthread_create(&tid17, NULL, UpDownChildHeuristicThread_3, (void*)&UD);
		pthread_create(&tid18, NULL, LeftRightChildHeuristicThread_3, (void*)&LR);
	
		pthread_join(tid17, NULL);
		pthread_join(tid18, NULL);
	}
	if(NoT == 3)
	{
		Heuristic UD;
		UD.node = node;
		UD.G = G;
		UD.goal = goal;
		UD.T = T;
		
		Heuristic LR;
		LR.node = node;
		LR.G = G;
		LR.goal = goal;
		LR.T = T;
		
		pthread_create(&tid13, NULL, UpDownChildHeuristicThread_3, (void*)&UD);
		pthread_create(&tid14, NULL, LeftRightChildHeuristicThread_3, (void*)&LR);
	
		pthread_join(tid13, NULL);
		pthread_join(tid14, NULL);
	}
	if(NoT == 2)
	{
		Heuristic A;
		A.node = node;
		A.G = G;
		A.goal = goal;
		A.T = T;
	
		pthread_create(&tid11, NULL, AllChildHeuristicThread_2, (void*)&A);
	
		pthread_join(tid11, NULL);
	}
}
T_Node* Tree::FindPath(T_Node* node, int* children)
{
	if(node->up != NULL)
	{
		cout << "\n\nUP\n";
		cout << "G : " << node->up->G << "\nH : " << node->up->H << "\nF : " << node->up->F;
	}
	if(node->down != NULL)
	{
		cout << "\n\nDOWN\n";
		cout << "G : " << node->down->G << "\nH : " << node->down->H << "\nF : " << node->down->F;
	}
	if(node->left != NULL)
	{
		cout << "\n\nLEFT\n";
		cout << "G : " << node->left->G << "\nH : " << node->left->H << "\nF : " << node->left->F;
	}
	if(node->right != NULL)
	{
		cout << "\n\nRIGHT\n";
		cout << "G : " << node->right->G << "\nH : " << node->right->H << "\nF : " << node->right->F;
	}

	//------------------------------------------------

	int F_Heuristics[4];

	for(int i = 0; i < 4; i++)
	{
		F_Heuristics[i] = 1000;
	}

	if(children[0] == 1)	//UP
	{
		F_Heuristics[0] = node->up->F;
	}
	if(children[1] == 1)	//DOWN
	{
		F_Heuristics[1] = node->down->F;
	}
	if(children[2] == 1)	//LEFT
	{
		F_Heuristics[2] = node->left->F;
	}
	if(children[3] == 1)	//RIGHT
	{
		F_Heuristics[3] = node->right->F;
	}

	cout << endl << "\nF Values of all Children : ";

	for(int i = 0; i < 4; i++)
	{
		cout << F_Heuristics[i] << " ";
	}

	int min = F_Heuristics[0];
	int min_index = 0;

	for(int i = 0; i < 4; i++)
	{
		if(F_Heuristics[i] < min)
		{
			min = F_Heuristics[i];
			min_index = i;
		}
	}

	T_Node* ret_node;
	
	if(min_index == 0)
	{
		cout << "\n\nGO TO UP CHILD";

		ret_node = node->up;
	}
	else if(min_index == 1)
	{
		cout << "\n\nGO TO DOWN CHILD";

		ret_node = node->down;
	}
	else if(min_index == 2)
	{
		cout << "\n\nGO TO LEFT CHILD";

		ret_node = node->left;
	}
	else if(min_index == 3)
	{
		cout << "\n\nGO TO RIGHT CHILD";

		ret_node = node->right;
	}
	
	return ret_node;
}
