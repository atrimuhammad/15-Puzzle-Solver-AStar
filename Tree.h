#ifndef TREE_H
#define TREE_H
#include <iostream>
using namespace std;

struct T_Node
{
	public:
		T_Node* up;
		T_Node* down;
		T_Node* left;
		T_Node* right;

		int **puzzle = new int*[4];

		int* children = new int[4];

		int G;
		int H;
		int F;

		T_Node()
		{
			for(int i = 0; i < 4; i++)
			{
				puzzle[i] = new int[4];

				children[i] = 1;
			}

			up = NULL;
			down = NULL;
			left = NULL;
			right = NULL;

			G = -1;
			H = -1;
			F = -1;
		}
};

class Tree
{
	private:
		T_Node* root;

	public:
		Tree();

		~Tree();

		void MakeRootNode(int** puzzle);

		void NodePuzzlePrinting(T_Node* node);

		T_Node* getRootNode();

		int* getChildrenArray(T_Node* node);
///
		void BlankTileRowandColumn(T_Node* node, int& blank_row, int& blank_col);
		void PossibleChildren(T_Node* node, int blank_row, int blank_col);
		void MakeTempPuzzle(int**& temp, T_Node* node);
		void ChildPuzzleSameAsCurrentParent(bool& flag1, int** temp, T_Node* parent_node);
		void MakeUpChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col);
		void MakeDownChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col);
		void MakeLeftChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col);
		void MakeRightChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col);
///
		void MakeChildren(T_Node* node, T_Node* parent_node, Tree T, int NoT);
///
		void UpChildHeuristicValue(T_Node* node, int G, int** goal);
		void DownChildHeuristicValue(T_Node* node, int G, int** goal);
		void LeftChildHeuristicValue(T_Node* node, int G, int** goal);
		void RightChildHeuristicValue(T_Node* node, int G, int** goal);
///
		void FindHeuristicValues(T_Node* node, int G, Tree T, int NoT);

		T_Node* FindPath(T_Node* node, int* children);

		bool GotGoal(T_Node* node);
};
#endif
